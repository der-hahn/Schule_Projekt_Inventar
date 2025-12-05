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

// ... (bestehender Code: Konstruktor, Destruktor, FillVecGegenstaende, etc.) ...

bool cMANAGER_InventurVERWALTUNG::ExecuteSomeSQL(QString strSQL)
{
    QSqlQuery query(m_db);
    query.prepare(strSQL);
    query.exec();
    if(query.lastError().isValid())
    {
        QMessageBox msg;
        msg.setWindowTitle("Fehler in cMANAGER_InventurVERWALTUNG::ExecuteSomeSQL");
        msg.setText(query.lastError().text());
        msg.exec();
        return false;
    }

    return true;
}

// ------------------------------------
// 2. INSERT und UPDATE Methoden
// ------------------------------------

// --- Gegenstaende ---

bool cMANAGER_InventurVERWALTUNG::UpdateGegenstand(structGegenstand& gegenstand)
{
    QString strsql = "update Gegenstaende set ... (SQL-Platzhalter) where ID = " + QString::number(gegenstand.iID);
    return ExecuteSomeSQL(strsql);
}

bool cMANAGER_InventurVERWALTUNG::InsertGegenstand(structGegenstand& gegenstand)
{
    QString strsql = "insert into Gegenstaende values() (SQL-Platzhalter)";
    return ExecuteSomeSQL(strsql);
}


// --- Person ---

bool cMANAGER_InventurVERWALTUNG::UpdatePerson(structPerson& person)
{
    QString strsql = "update Person set ... (SQL-Platzhalter) where ID = " + QString::number(person.iID);
    return ExecuteSomeSQL(strsql);
}

bool cMANAGER_InventurVERWALTUNG::InsertPerson(structPerson& person)
{
    QString strsql = "insert into Person values() (SQL-Platzhalter)";
    return ExecuteSomeSQL(strsql);
}


// --- Rolle ---

bool cMANAGER_InventurVERWALTUNG::UpdateRolle(structRolle& rolle)
{
    QString strsql = "update Rolle set ... (SQL-Platzhalter) where ID = " + QString::number(rolle.iID);
    return ExecuteSomeSQL(strsql);
}

bool cMANAGER_InventurVERWALTUNG::InsertRolle(structRolle& rolle)
{
    QString strsql = "insert into Rolle values() (SQL-Platzhalter)";
    return ExecuteSomeSQL(strsql);
}


// --- Gruppe ---

bool cMANAGER_InventurVERWALTUNG::UpdateGruppe(structGruppe& gruppe)
{
    QString strsql = "update Gruppe set ... (SQL-Platzhalter) where ID = " + QString::number(gruppe.iID);
    return ExecuteSomeSQL(strsql);
}

bool cMANAGER_InventurVERWALTUNG::InsertGruppe(structGruppe& gruppe)
{
    QString strsql = "insert into Gruppe values() (SQL-Platzhalter)";
    return ExecuteSomeSQL(strsql);
}


// --- Status ---

bool cMANAGER_InventurVERWALTUNG::UpdateStatus(structStatus& status)
{
    QString strsql = "update Status set ... (SQL-Platzhalter) where ID = " + QString::number(status.iID);
    return ExecuteSomeSQL(strsql);
}

bool cMANAGER_InventurVERWALTUNG::InsertStatus(structStatus& status)
{
    QString strsql = "insert into Status values() (SQL-Platzhalter)";
    return ExecuteSomeSQL(strsql);
}


// --- Fach ---

bool cMANAGER_InventurVERWALTUNG::UpdateFach(structFach& fach)
{
    QString strsql = "update Fach set ... (SQL-Platzhalter) where ID = " + QString::number(fach.iID);
    return ExecuteSomeSQL(strsql);
}

bool cMANAGER_InventurVERWALTUNG::InsertFach(structFach& fach)
{
    QString strsql = "insert into Fach values() (SQL-Platzhalter)";
    return ExecuteSomeSQL(strsql);
}


// --- Eigenschaft ---

bool cMANAGER_InventurVERWALTUNG::UpdateEigenschaft(structEigenschaft& eigenschaft)
{
    QString strsql = "update Eigenschaft set ... (SQL-Platzhalter) where ID = " + QString::number(eigenschaft.iID);
    return ExecuteSomeSQL(strsql);
}

bool cMANAGER_InventurVERWALTUNG::InsertEigenschaft(structEigenschaft& eigenschaft)
{
    QString strsql = "insert into Eigenschaft values() (SQL-Platzhalter)";
    return ExecuteSomeSQL(strsql);
}


// --- Abteilung ---

bool cMANAGER_InventurVERWALTUNG::UpdateAbteilung(structAbteilung& abteilung)
{
    QString strsql = "update Abteilung set ... (SQL-Platzhalter) where ID = " + QString::number(abteilung.iID);
    return ExecuteSomeSQL(strsql);
}

bool cMANAGER_InventurVERWALTUNG::InsertAbteilung(structAbteilung& abteilung)
{
    QString strsql = "insert into Abteilung values() (SQL-Platzhalter)";
    return ExecuteSomeSQL(strsql);
}


// --- Standort ---

bool cMANAGER_InventurVERWALTUNG::UpdateStandort(structStandort& standort)
{
    // Hier verwenden wir iSTANDORT_ID, wie in der Struktur definiert.
    QString strsql = "update Standort set ... (SQL-Platzhalter) where STANDORT_ID = " + QString::number(standort.iSTANDORT_ID);
    return ExecuteSomeSQL(strsql);
}

bool cMANAGER_InventurVERWALTUNG::InsertStandort(structStandort& standort)
{
    QString strsql = "insert into Standort values() (SQL-Platzhalter)";
    return ExecuteSomeSQL(strsql);
}

bool cMANAGER_InventurVERWALTUNG::Anmelden(QString strbenutzername, QString strPasswort)
{

    QString strsql = "select TRIM(VORNAME) + '.' + TRIM(NAME) benname, PASSWORT from PERSONEN where benname = :benname and PASSWORT = HASHBYTES('SHA2_256', :passwd)";
    QSqlQuery query(m_db);
    query.prepare(strsql);

    query.bindValue(":benname", strbenutzername);
    query.bindValue(":passwd", strPasswort);

    query.exec();
    if(query.lastError().isValid())
    {
        QMessageBox msg;
        msg.setWindowTitle("Fehler in cMANAGER_InventurVERWALTUNG::Anmelden");
        msg.setText(query.lastError().text());
        msg.exec();
        return false;
    }

    m_vecStandort.clear();

    if(query.next())
    {
        return true;
    }

    return false;
}
