#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qsqltablemodel.h>
#include <QTableView>
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
private:
    Ui::MainWindow *ui;
    QStringList statusList;
    QList<QSqlTableModel*> tableModels;
    QList<QTableView*> tableViews;

};

#endif // MAINWINDOW_H
