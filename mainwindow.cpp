#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QFileDialog>
#include <QTextStream>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupTopbar();
    setupTabs();  // nur einmal aufrufen!
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ────────────── CSV Export ──────────────
void MainWindow::onExportCsv()
{
    int tab = ui->tabWidget_Gegenstandsanzeige->currentIndex();
    if (tab < 0) return;

    auto *proxy = proxyModels[tab];
    auto *model = proxy->sourceModel();

    QString file = QFileDialog::getSaveFileName(this, "CSV exportieren", "", "CSV (*.csv)");
    if (file.isEmpty()) return;

    QFile f(file);
    if (!f.open(QIODevice::WriteOnly)) return;

    QTextStream out(&f);

    // Header
    for (int c = 0; c < model->columnCount(); c++)
        out << model->headerData(c, Qt::Horizontal).toString()
            << (c+1 == model->columnCount() ? "\n" : ";");

    // Zeilen
    for (int r = 0; r < model->rowCount(); r++)
    {
        for (int c = 0; c < model->columnCount(); c++)
        {
            out << model->index(r, c).data().toString()
            << (c+1 == model->columnCount() ? "\n" : ";");
        }
    }
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

        // ProxyModel für Live-Suche
        QSortFilterProxyModel *proxy = new QSortFilterProxyModel(this);
        proxy->setSourceModel(model);
        proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
        proxy->setFilterKeyColumn(-1); // alle Spalten

        view->setModel(proxy);

        // speichern
        tableViews.append(view);
        tableModels.append(model);
        proxyModels.append(proxy);

        view->resizeColumnsToContents();
    }
}

// ────────────── Topbar / Suchfeld ──────────────
void MainWindow::setupTopbar()
{
    QToolBar *topBar = ui->toolBar;
    topBar->setMovable(false);
    topBar->setIconSize(QSize(24,24));

    QLineEdit *searchField = new QLineEdit(this);
    searchField->setPlaceholderText("Inventar durchsuchen...");
    searchField->setMaximumWidth(250);
    topBar->insertWidget(ui->actionNeues_Inventar, searchField);

    connect(searchField, &QLineEdit::textChanged, this, &MainWindow::onSearchChanged);
}
