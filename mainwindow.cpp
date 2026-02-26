#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filterproxymodel.h"
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QFileDialog>
#include <QTextStream>
#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupTopbar();
    setupTabs();  // nur einmal aufrufen!

    connect(ui->actionCSVexport,
            &QAction::triggered,
            this,
            &MainWindow::onExportCsv);


    connect(ui->Abteilung_Edit_comboBox, &QComboBox::currentIndexChanged,
            this, &MainWindow::applyFilters);

    connect(ui->Gruppierung_comboBox, &QComboBox::currentIndexChanged,
            this, &MainWindow::applyFilters);

    connect(ui->Verantwortlicher_comboBox, &QComboBox::currentIndexChanged,
            this, &MainWindow::applyFilters);

    connect(ui->Lagerort_comboBox, &QComboBox::currentIndexChanged,
            this, &MainWindow::applyFilters);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ────────────── CSV Export ──────────────
void MainWindow::onExportCsv()
{
    int tab = ui->tabWidget_Gegenstandsanzeige->currentIndex();

    if (tab < 0 || tab >= proxyModels.size())
        return;

    QSortFilterProxyModel* proxy = proxyModels[tab];
    if (!proxy)
        return;

    QAbstractItemModel* model = proxy;

    QString file = QFileDialog::getSaveFileName(this,
                                                "CSV exportieren",
                                                "",
                                                "CSV (*.csv)");
    if (file.isEmpty()) return;

    QFile f(file);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&f);
    out.setEncoding(QStringConverter::Utf8);   // wichtig für Umlaute

    // Header
    for (int c = 0; c < model->columnCount(); ++c)
    {
        out << model->headerData(c, Qt::Horizontal).toString();
        if (c < model->columnCount()-1)
            out << ";";
    }
    out << "\n";

    // Daten
    for (int r = 0; r < model->rowCount(); ++r)
    {
        for (int c = 0; c < model->columnCount(); ++c)
        {
            QString value = model->index(r, c).data().toString();
            value.replace(";", ","); // CSV-Schutz
            out << value;

            if (c < model->columnCount()-1)
                out << ";";
        }
        out << "\n";
    }

    f.close();
}

// ────────────── Live-Suche ──────────────
void MainWindow::onSearchChanged(const QString &text)
{
    for (auto proxy : proxyModels)
        proxy->setFilterFixedString(text);
}

// ────────────── Tabs erstellen ──────────────
void MainWindow::setupTabs()
{
    // alte Views / Models löschen
    for (auto v : tableViews) delete v;
    for (auto m : tableModels) delete m;
    for (auto p : proxyModels) delete p;

    tableViews.clear();
    tableModels.clear();
    proxyModels.clear();
    ui->tabWidget_Gegenstandsanzeige->clear();


    // Daten vom Manager füllen
    m_manager.FillVecZustaende();
    m_manager.FillVecAbteilungen();
    m_manager.FillVecGruppen();
    m_manager.FillVecStandorte();
    m_manager.FillVecGegenstaende();
    m_manager.FillVecPersonen();

    // Lookup-Maps für Namen
    QMap<int, QString> mapAbteilung, mapGruppe, mapStandort;
    for (auto &a : *m_manager.GetvecAbteilungen()) mapAbteilung[a.iABTEILUNG_ID] = a.strBESCHREIBUNG;
    for (auto &g : *m_manager.GetvecGruppen()) mapGruppe[g.iGRUPPE_ID] = g.strBESCHREIBUNG;
    for (auto &s : *m_manager.GetvecStandorte()) mapStandort[s.iSTANDORT_ID] = s.strBESCHREIBUNG;

    // Für jeden Zustand einen Tab erstellen
    for (const auto &zustand : *m_manager.GetvecZustaende())
    {
        QWidget *tab = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(tab);

        QTableView *view = new QTableView(tab);
        view->setSelectionBehavior(QAbstractItemView::SelectRows);
        view->setSelectionMode(QAbstractItemView::SingleSelection);
        view->setAlternatingRowColors(true);
        view->setEditTriggers(QAbstractItemView::NoEditTriggers); // read-only

        layout->addWidget(view);
        tab->setLayout(layout);
        ui->tabWidget_Gegenstandsanzeige->addTab(tab, zustand.strBESCHREIBUNG);

        // Model erstellen
        QStandardItemModel *model = new QStandardItemModel(this);
        QStringList headers = {
            "ID", "Bezeichnung", "Seriennummer",
            "Abteilung", "Gruppe", "Standort",
            "Anschaffung (€)", "Aktuell (€)",
            "Angeschafft am", "Notiz"
        };
        model->setHorizontalHeaderLabels(headers);

        // Daten einfügen
        int row = 0;
        for (auto &g : *m_manager.GetvecGegenstaende())
        {
            if (g.ZUSTAND_ID != zustand.iZUSTAND_ID) continue;

            model->insertRow(row);
            model->setData(model->index(row, 0), g.iGEGENSTAENDE_ID);
            model->setData(model->index(row, 1), g.strBEZEICHNUNG);
            model->setData(model->index(row, 2), g.strSERIENNUMMER);
            model->setData(model->index(row, 3), mapAbteilung[g.ABTEILUNG_ID]);
            model->setData(model->index(row, 4), mapGruppe[g.GRUPPE_ID]);
            model->setData(model->index(row, 5), mapStandort[g.STANDORT_ID]);
            model->setData(model->index(row, 6), g.WERT_ANSCHAFFUNG);
            model->setData(model->index(row, 7), g.WERT_AKTUELL);
            model->setData(model->index(row, 8), g.ANGESCHAFFT_AM.toString("dd.MM.yyyy"));
            model->setData(model->index(row, 9), g.NOTIZ);

            row++;
        }
        qDebug() << "Tab:" << zustand.strBESCHREIBUNG
                 << "Zeilen:" << model->rowCount();


        // ProxyModel für Live-Suche
        //QSortFilterProxyModel *proxy = new QSortFilterProxyModel(this);
        //proxy->setSourceModel(model);
        //proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
        //proxy->setFilterKeyColumn(-1); // alle Spalten

        FilterProxyModel *proxy = new FilterProxyModel();
        proxy->setSourceModel(model);

        view->setModel(proxy);

        // speichern
        tableViews.append(view);
        tableModels.append(model);
        proxyModels.append(proxy);

        view->resizeColumnsToContents();
    }

    ui->Abteilung_Edit_comboBox->clear();
    ui->Abteilung_Edit_comboBox->addItem("Alle", 0);

    for (auto &a : *m_manager.GetvecAbteilungen())
    {
        ui->Abteilung_Edit_comboBox->addItem(a.strBESCHREIBUNG,
                                    a.iABTEILUNG_ID);
    }

    ui->Gruppierung_comboBox->clear();
    ui->Gruppierung_comboBox->addItem("Alle", 0);

    for (auto &g : *m_manager.GetvecGruppen())
    {
        ui->Gruppierung_comboBox->addItem(g.strBESCHREIBUNG,
                                 g.iGRUPPE_ID);
    }


    ui->Verantwortlicher_comboBox->clear();
    ui->Verantwortlicher_comboBox->addItem("Alle", 0);

    for (auto &p : *m_manager.GetvecPersonen())
    {
        QString name = p.NAME + " " + p.VORNAME;
        ui->Verantwortlicher_comboBox->addItem(name,
                                           p.iPERSONEN_ID);
    }

    ui->Lagerort_comboBox->clear();
    ui->Lagerort_comboBox->addItem("Alle", -1);

    for (auto &s : *m_manager.GetvecStandorte())
    {
        ui->Lagerort_comboBox->addItem(s.strBESCHREIBUNG,
                                       s.iSTANDORT_ID);
    }
}

void MainWindow::on_actionCSVexport_triggered()
{
    onExportCsv();
}



// ────────────── Topbar / Suchfeld ──────────────
void MainWindow::setupTopbar()
{
    QToolBar *topBar = ui->toolBar;
    topBar->setMovable(false);
    topBar->setIconSize(QSize(24,24));

    //QLineEdit *searchField = new QLineEdit(this);
    //searchField->setPlaceholderText("Inventar durchsuchen...");
    //searchField->setMaximumWidth(250);
    //topBar->insertWidget(ui->actionNeues_Inventar, searchField);

    //connect(searchField, &QLineEdit::textChanged, this, &MainWindow::onSearchChanged);
}




void MainWindow::applyFilters()
{
    QString abt = ui->Abteilung_Edit_comboBox->currentText();
    QString grp = ui->Gruppierung_comboBox->currentText();
    QString ver = ui->Verantwortlicher_comboBox->currentText();

    for (auto proxy : proxyModels)
        proxy->setFilterValues(abt, grp, ver);
}








