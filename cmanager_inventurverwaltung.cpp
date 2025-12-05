#include "cmanager_inventurverwaltung.h"
#include <QtSql/QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

cMANAGER_InventurVERWALTUNG::cMANAGER_InventurVERWALTUNG()
{
    m_db = QSqlDatabase::addDatabase("QODBC");
    m_db.setDatabaseName("Driver={SQL Server};Server=herteltlaptop;database=kisdb_demo_20230808;username=dba;password=sqlosk");
    if(!m_db.open())
    {
        QMessageBox msg;
        msg.setWindowTitle("Fehler in cMANAGER_InventurVERWALTUNG::cMANAGER_InventurVERWALTUNG");
        msg.setText(m_db.lastError().text());
        msg.exec();
    }
}

cMANAGER_InventurVERWALTUNG::~cMANAGER_InventurVERWALTUNG()
{
    if(m_db.isOpen())
    {
        m_db.close();
    }
}

// --- Gegenstaende ---

void cMANAGER_InventurVERWALTUNG::FillVecGegenstaende()
{
    QString strsql = ""; // SQL-Statement einfügen
    QSqlQuery query(m_db);
    query.prepare(strsql);
    query.exec();
    if(query.lastError().isValid())
    {
        QMessageBox msg;
        msg.setWindowTitle("Fehler in cMANAGER_InventurVERWALTUNG::FillVecGegenstaende");
        msg.setText(query.lastError().text());
        msg.exec();
        return;
    }

    m_vecGegenstaende.clear(); // Vektor vor dem Befüllen leeren

    while(query.next())
    {
        // Auslesen der Daten und Hinzufügen zum Vektor
    }
}

// --- Person (NEU) ---

void cMANAGER_InventurVERWALTUNG::FillVecPerson()
{
    QString strsql = ""; // SQL-Statement einfügen
    QSqlQuery query(m_db);
    query.prepare(strsql);
    query.exec();
    if(query.lastError().isValid())
    {
        QMessageBox msg;
        msg.setWindowTitle("Fehler in cMANAGER_InventurVERWALTUNG::FillVecPerson");
        msg.setText(query.lastError().text());
        msg.exec();
        return;
    }

    m_vecPerson.clear();

    while(query.next())
    {
        // Auslesen der Daten und Hinzufügen zum Vektor
    }
}

// --- Rolle (NEU) ---

void cMANAGER_InventurVERWALTUNG::FillVecRolle()
{
    QString strsql = ""; // SQL-Statement einfügen
    QSqlQuery query(m_db);
    query.prepare(strsql);
    query.exec();
    if(query.lastError().isValid())
    {
        QMessageBox msg;
        msg.setWindowTitle("Fehler in cMANAGER_InventurVERWALTUNG::FillVecRolle");
        msg.setText(query.lastError().text());
        msg.exec();
        return;
    }

    m_vecRolle.clear();

    while(query.next())
    {
        // Auslesen der Daten und Hinzufügen zum Vektor
    }
}

// --- Gruppe (NEU) ---

void cMANAGER_InventurVERWALTUNG::FillVecGruppe()
{
    QString strsql = ""; // SQL-Statement einfügen
    QSqlQuery query(m_db);
    query.prepare(strsql);
    query.exec();
    if(query.lastError().isValid())
    {
        QMessageBox msg;
        msg.setWindowTitle("Fehler in cMANAGER_InventurVERWALTUNG::FillVecGruppe");
        msg.setText(query.lastError().text());
        msg.exec();
        return;
    }

    m_vecGruppe.clear();

    while(query.next())
    {
        // Auslesen der Daten und Hinzufügen zum Vektor
    }
}

// --- Status (NEU) ---

void cMANAGER_InventurVERWALTUNG::FillVecStatus()
{
    QString strsql = ""; // SQL-Statement einfügen
    QSqlQuery query(m_db);
    query.prepare(strsql);
    query.exec();
    if(query.lastError().isValid())
    {
        QMessageBox msg;
        msg.setWindowTitle("Fehler in cMANAGER_InventurVERWALTUNG::FillVecStatus");
        msg.setText(query.lastError().text());
        msg.exec();
        return;
    }

    m_vecStatus.clear();

    while(query.next())
    {
        // Auslesen der Daten und Hinzufügen zum Vektor
    }
}

// --- Fach (NEU) ---

void cMANAGER_InventurVERWALTUNG::FillVecFach()
{
    QString strsql = ""; // SQL-Statement einfügen
    QSqlQuery query(m_db);
    query.prepare(strsql);
    query.exec();
    if(query.lastError().isValid())
    {
        QMessageBox msg;
        msg.setWindowTitle("Fehler in cMANAGER_InventurVERWALTUNG::FillVecFach");
        msg.setText(query.lastError().text());
        msg.exec();
        return;
    }

    m_vecFach.clear();

    while(query.next())
    {
        // Auslesen der Daten und Hinzufügen zum Vektor
    }
}

// --- Eigenschaft (NEU) ---

void cMANAGER_InventurVERWALTUNG::FillVecEigenschaft()
{
    QString strsql = ""; // SQL-Statement einfügen
    QSqlQuery query(m_db);
    query.prepare(strsql);
    query.exec();
    if(query.lastError().isValid())
    {
        QMessageBox msg;
        msg.setWindowTitle("Fehler in cMANAGER_InventurVERWALTUNG::FillVecEigenschaft");
        msg.setText(query.lastError().text());
        msg.exec();
        return;
    }

    m_vecEigenschaft.clear();

    while(query.next())
    {
        // Auslesen der Daten und Hinzufügen zum Vektor
    }
}

// --- Abteilung (NEU) ---

void cMANAGER_InventurVERWALTUNG::FillVecAbteilung()
{
    QString strsql = ""; // SQL-Statement einfügen
    QSqlQuery query(m_db);
    query.prepare(strsql);
    query.exec();
    if(query.lastError().isValid())
    {
        QMessageBox msg;
        msg.setWindowTitle("Fehler in cMANAGER_InventurVERWALTUNG::FillVecAbteilung");
        msg.setText(query.lastError().text());
        msg.exec();
        return;
    }

    m_vecAbteilung.clear();

    while(query.next())
    {
        // Auslesen der Daten und Hinzufügen zum Vektor
    }
}

// --- Standort (NEU) ---

void cMANAGER_InventurVERWALTUNG::FillVecStandort()
{
    QString strsql = "select * from STANDORT";
    QSqlQuery query(m_db);
    query.prepare(strsql);
    query.exec();
    if(query.lastError().isValid())
    {
        QMessageBox msg;
        msg.setWindowTitle("Fehler in cMANAGER_InventurVERWALTUNG::FillVecStandort");
        msg.setText(query.lastError().text());
        msg.exec();
        return;
    }

    m_vecStandort.clear();

    structStandort standort;

    while(query.next())
    {
        standort.iSTANDORT_ID = query.value("STANDORT_ID").toInt();
        standort.strBESCHREIBUNG = query.value("BESCHREIBUNG").toString();
        standort.strBUNDESLAND = query.value("BUNDESLAND").toString();
        standort.strPLZ = query.value("PLZ").toString();
        standort.strSTRASSE = query.value("STRASSE").toString();
        standort.iHAUS_NR = query.value("HAUS_NR").toInt();
        standort.strORT = query.value("ORT").toString();
        standort.strHAUSZUSATZ = query.value("HAUSZUSATZ").toString();

        m_vecStandort.push_back(standort);
    }
}
