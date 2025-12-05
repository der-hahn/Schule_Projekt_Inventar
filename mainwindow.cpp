#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlTableModel>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupTopbar();



    QStringList statusList = {
        "Projektiert",
        "Angefordert",
        "Bestellt",
        "Geliefert",
        "Eingesetzt",
        "Ausgeliehen",
        "Reparatur",
        "Ausgemustert"
    };



    ui->tabWidget_Gegenstandsanzeige->clear();

    for (const QString &status : statusList)
    {
        // Neuen Tab erzeugen
        QWidget *tab = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(tab);

        // TableView erzeugen
        QTableView *view = new QTableView(tab);
        view->setObjectName("tableView");

        layout->addWidget(view);
        tab->setLayout(layout);

        // Tab benennen
        ui->tabWidget_Gegenstandsanzeige->addTab(tab, status);

        // Modell erstellen
        QSqlTableModel *model = new QSqlTableModel(this);
        model->setTable("inventar");
        model->setEditStrategy(QSqlTableModel::OnFieldChange);
        model->setFilter("status = '" + status + "'");
        model->select();

        view->setModel(model);
        view->resizeColumnsToContents();

        // speichern
        tableModels.append(model);
        tableViews.append(view);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onResetFilter() {}

void MainWindow::onAddInventory() {}

void MainWindow::onExportCsv() {}

void MainWindow::onSearchChanged(const QString &text) {}






void MainWindow::setupTopbar()
{
    // deine bestehende Toolbar aus dem Designer
    QToolBar *topBar = ui->toolBar;
    topBar->setMovable(false);
    topBar->setIconSize(QSize(24, 24));

    // ───────────────────────────────
    // 🔍 Suchfeld
    // ───────────────────────────────
    QLineEdit *searchField = new QLineEdit(this);
    searchField->setPlaceholderText("Inventar durchsuchen...");
    searchField->setMaximumWidth(250);
    //topBar->addWidget(searchField);
    topBar->insertWidget(ui->actionNeues_Inventar, searchField);




    topBar->addSeparator();




    // ───────────────────────────────
    // Signals verbinden
    // ───────────────────────────────
    connect(searchField, &QLineEdit::textChanged, this, &MainWindow::onSearchChanged);

}



