#include "cmyapplication.cpp"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filterproxymodel.h"
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QFileDialog>
#include <QTextStream>
#include <QVBoxLayout>
#include <QDebug>


#include "cdia_neuanlage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pmanager = ((CMyApplication*)qApp)->GetpManagerInventurV();
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
    m_pmanager->FillVecZustaende();
    m_pmanager->FillVecAbteilungen();
    m_pmanager->FillVecGruppen();
    m_pmanager->FillVecStandorte();
    m_pmanager->FillVecGegenstaende();
    m_pmanager->FillVecPersonen();

    // Lookup-Maps für Namen
    QMap<int, QString> mapAbteilung, mapGruppe, mapStandort, mapVerantwortlicher;
    for (auto &a : *(m_pmanager->GetvecAbteilungen())) mapAbteilung[a.iABTEILUNG_ID] = a.strBESCHREIBUNG;
    for (auto &g : *(m_pmanager->GetvecGruppen())) mapGruppe[g.iGRUPPE_ID] = g.strBESCHREIBUNG;
    for (auto &s : *(m_pmanager->GetvecStandorte())) mapStandort[s.iSTANDORT_ID] = s.strBESCHREIBUNG;
    for (auto &p : *(m_pmanager->GetvecPersonen()))
        mapVerantwortlicher[p.iPERSONEN_ID] = p.NAME + " " + p.VORNAME;
    // Für jeden Zustand einen Tab erstellen
    for (const auto &zustand : *(m_pmanager->GetvecZustaende()))
    {
        QWidget *tab = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(tab);

        QTableView *view = new QTableView(tab);

        connect(view, &QTableView::doubleClicked, this, &MainWindow::on_actionBearbeiten_triggered);

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
            "Abteilung", "Gruppe","Verantwortlicher", "Standort",
            "Anschaffung (€)", "Aktuell (€)",
            "Angeschafft am", "Notiz"
        };
        model->setHorizontalHeaderLabels(headers);

        // Daten einfügen
        int row = 0;
        for (auto &g : *(m_pmanager->GetvecGegenstaende()))
        {
            if (g.ZUSTAND_ID != zustand.iZUSTAND_ID) continue;

            model->insertRow(row);
            model->setData(model->index(row, 0), g.iGEGENSTAENDE_ID);
            model->setData(model->index(row, 1), g.strBEZEICHNUNG);
            model->setData(model->index(row, 2), g.strSERIENNUMMER);
            model->setData(model->index(row, 3), mapAbteilung[g.ABTEILUNG_ID]);
            model->setData(model->index(row, 4), mapGruppe[g.GRUPPE_ID]);
            model->setData(model->index(row, 5), mapVerantwortlicher[g.iVerantwortlicher_ID]);
            model->setData(model->index(row, 6), mapStandort[g.STANDORT_ID]);
            model->setData(model->index(row, 7), g.WERT_ANSCHAFFUNG);
            model->setData(model->index(row, 8), g.WERT_AKTUELL);
            model->setData(model->index(row, 9), g.ANGESCHAFFT_AM.toString("dd.MM.yyyy"));
            model->setData(model->index(row, 10), g.NOTIZ);


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

    // Filter-Comboboxen initial auf „Alle“ setzen
    ui->Abteilung_Edit_comboBox->clear();
    ui->Abteilung_Edit_comboBox->addItem("Alle", 0);
    for (auto &a : *m_pmanager->GetvecAbteilungen())
        ui->Abteilung_Edit_comboBox->addItem(a.strBESCHREIBUNG, a.iABTEILUNG_ID);
    ui->Abteilung_Edit_comboBox->setCurrentIndex(0);

    ui->Gruppierung_comboBox->clear();
    ui->Gruppierung_comboBox->addItem("Alle", 0);
    for (auto &g : *m_pmanager->GetvecGruppen())
        ui->Gruppierung_comboBox->addItem(g.strBESCHREIBUNG, g.iGRUPPE_ID);
    ui->Gruppierung_comboBox->setCurrentIndex(0);

    ui->Verantwortlicher_comboBox->clear();
    ui->Verantwortlicher_comboBox->addItem("Alle", 0);
    for (auto &p : *m_pmanager->GetvecPersonen())
        ui->Verantwortlicher_comboBox->addItem(p.NAME + " " + p.VORNAME, p.iPERSONEN_ID);
    ui->Verantwortlicher_comboBox->setCurrentIndex(0);

    ui->Lagerort_comboBox->clear();
    ui->Lagerort_comboBox->addItem("Alle", -1);
    for (auto &s : *m_pmanager->GetvecStandorte())
        ui->Lagerort_comboBox->addItem(s.strBESCHREIBUNG, s.iSTANDORT_ID);
    ui->Lagerort_comboBox->setCurrentIndex(0);

    applyFilters();

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
    QString lag = ui->Lagerort_comboBox->currentText();


    for (auto proxy : proxyModels)
        proxy->setFilterValues(abt, grp, ver, lag);
}









void MainWindow::on_actionNeues_Inventar_triggered()
{
    CDIA_NEUANLAGE dlg;
    dlg.exec();
}


void MainWindow::on_actionBearbeiten_triggered()
{
    int currentTabIndex = ui->tabWidget_Gegenstandsanzeige->currentIndex();
    if (currentTabIndex < 0 || currentTabIndex >= tableViews.size()) return;

    // 1. Die View des aktuellen Tabs holen
    QTableView *view = tableViews[currentTabIndex];
    QModelIndex proxyIndex = view->currentIndex();

    if (!proxyIndex.isValid()) {
        qDebug() << "Keine Zeile ausgewählt!";
        return;
    }

    // 2. Den Proxy-Index auf das Quell-Model (QStandardItemModel) mappen
    FilterProxyModel *proxy = proxyModels[currentTabIndex];
    QModelIndex sourceIndex = proxy->mapToSource(proxyIndex);

    // 3. ID aus der ersten Spalte (Index 0) der gemappten Zeile holen
    int gegenstandID = proxy->sourceModel()->index(sourceIndex.row(), 0).data().toInt();

    // 4. Dialog öffnen und ID übergeben
    CDIA_NEUANLAGE dlg;
    dlg.SetGegenstaendeID(gegenstandID);
    dlg.exec();
}

