#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qsqltablemodel.h>
#include <QTableView>
#include <qstandarditemmodel.h>
#include <qsortfilterproxymodel.h>
#include "cmanager_inventurverwaltung.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupTopbar();
    void onResetFilter();
    void onAddInventory();
    void onExportCsv();
    void onSearchChanged(const QString &text);
    void setupTabs();

    void refreshTables();
private:
    Ui::MainWindow *ui;
    QStringList statusList;
    cMANAGER_InventurVERWALTUNG* m_pmanager;
    QVector<QStandardItemModel*> tableModels;
    QVector<QTableView*> tableViews;
    QVector<QSortFilterProxyModel*> proxyModels;

};

#endif // MAINWINDOW_H
