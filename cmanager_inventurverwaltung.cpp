#include "cmanager_inventurverwaltung.h"
#include <QtSql/QSqlDatabase>
#include <QMessagebox>
#include <QSqlError>

cMANAGER_INVENTURVERWALTUNG::cMANAGER_INVENTURVERWALTUNG()
{
    m_db = QSqlDatabase::addDatabase("QODBC");
    m_db.setDatabaseName("Driver={SQL Server};Server=hertelt;database=Inventurverwaltung;username=dba;password=sqlosk");
    if(!m_db.open())
    {
        QMessageBox msg;
        msg.setWindowTitle("Fehler in cMANAGER_INVENTURVERWALTUNG::cMANAGER_INVENTURVERWALTUNG");
        msg.setText(m_db.lastError().text());
        msg.exec();
    }
}

cMANAGER_INVENTURVERWALTUNG::~cMANAGER_INVENTURVERWALTUNG()
{
    if(m_db.isOpen())
    {
        m_db.close();
    }
}
