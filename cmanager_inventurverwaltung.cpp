#include "cmanager_inventurverwaltung.h"
#include <QtSql/QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

cMANAGER_InventurVERWALTUNG::cMANAGER_InventurVERWALTUNG()
{
    m_db = QSqlDatabase::addDatabase("QODBC");
    m_db.setDatabaseName("Driver={SQL Server};Server=herteltlaptop;database=kisdb_demo_20230808;uid=dba;pwd=sqlosk");
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

// ------------------------------------
// HILFSFUNKTION (BLEIBT UNVERÄNDERT)
// ------------------------------------

bool cMANAGER_InventurVERWALTUNG::ExecuteSomeSQL(const QSqlQuery& query)
{
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
// 1. DATEN FÜLLEN (FillVec...) (BLEIBEN UNVERÄNDERT)
// ------------------------------------

void cMANAGER_InventurVERWALTUNG::FillVecGegenstaende(int izustandid/*=0*/)
{
    QString strsql = "select * from GEGENSTAENDE where 1=1";

    if(izustandid > 0)
        strsql += " and ZUSTAND_ID = :zuid";


    QSqlQuery query(m_db);
    query.prepare(strsql);

    query.bindValue(":zuid", izustandid);

    query.exec();
    if(query.lastError().isValid())
    {
        QMessageBox msg;
        msg.setWindowTitle("Fehler in cMANAGER_InventurVERWALTUNG::FillVecGegenstaende");
        msg.setText(query.lastError().text());
        msg.exec();
        return;
    }
    m_vecGegenstaende.clear();
    while(query.next())
    {
        structGegenstand gegenstand;
        gegenstand.iGEGENSTAENDE_ID = query.value("GEGENSTAENDE_ID").toInt();
        gegenstand.strBEZEICHNUNG = query.value("BEZEICHNUNG").toString();
        gegenstand.strSERIENNUMMER = query.value("SERIENNUMMER").toString();
        gegenstand.ABTEILUNG_ID = query.value("ABTEILUNG_ID").toInt();
        gegenstand.GRUPPE_ID = query.value("GRUPPE_ID").toInt();
        gegenstand.STANDORT_ID = query.value("STANDORT_ID").toInt();
        gegenstand.WERT_ANSCHAFFUNG = query.value("WERT_ANSCHAFFUNG").toDouble();
        gegenstand.WERT_AKTUELL = query.value("WERT_AKTUELL").toDouble();
        gegenstand.ANGESCHAFFT_AM = query.value("ANGESCHAFFT_AM").toDate();
        gegenstand.NOTIZ = query.value("NOTIZ").toString();
        gegenstand.ZUSTAND_ID = query.value("ZUSTAND_ID").toInt();
        m_vecGegenstaende.push_back(gegenstand);
    }
}

void cMANAGER_InventurVERWALTUNG::FillVecPersonen()
{
    QString strsql = "select * from PERSONEN";
    QSqlQuery query(m_db);
    query.prepare(strsql);
    query.exec();
    if(query.lastError().isValid())
    {
        QMessageBox msg;
        msg.setWindowTitle("Fehler in cMANAGER_InventurVERWALTUNG::FillVecPersonen");
        msg.setText(query.lastError().text());
        msg.exec();
        return;
    }
    m_vecPersonen.clear();
    while(query.next())
    {
        structPerson person;
        person.iPERSONEN_ID = query.value("PERSONEN_ID").toInt();
        person.NAME = query.value("NAME").toString();
        person.VORNAME = query.value("VORNAME").toString();
        person.BENUTZERNAME = query.value("BENUTZERNAME").toString();
        person.PASSWORT = query.value("PASSWORT").toString();
        person.BEREICH_ID = query.value("BEREICH_ID").toInt();
        person.iZUSTAND_ID = query.value("ZUSTAND_ID").toInt();
        m_vecPersonen.push_back(person);
    }
}

void cMANAGER_InventurVERWALTUNG::FillVecRollen()
{
    QString strsql = "select * from ROLLE";
    QSqlQuery query(m_db);
    query.prepare(strsql);
    query.exec();
    if(query.lastError().isValid())
    {
        QMessageBox msg;
        msg.setWindowTitle("Fehler in cMANAGER_InventurVERWALTUNG::FillVecRollen");
        msg.setText(query.lastError().text());
        msg.exec();
        return;
    }
    m_vecRollen.clear();
    while(query.next())
    {
        structRolle rolle;
        rolle.iID = query.value("ID").toInt();
        rolle.strBez = query.value("Bez").toString();
        m_vecRollen.push_back(rolle);
    }
}

void cMANAGER_InventurVERWALTUNG::FillVecGruppen()
{
    QString strsql = "select * from GRUPPE";
    QSqlQuery query(m_db);
    query.prepare(strsql);
    query.exec();
    if(query.lastError().isValid())
    {
        QMessageBox msg;
        msg.setWindowTitle("Fehler in cMANAGER_InventurVERWALTUNG::FillVecGruppen");
        msg.setText(query.lastError().text());
        msg.exec();
        return;
    }
    m_vecGruppen.clear();
    while(query.next())
    {
        structGruppe gruppe;
        gruppe.iGRUPPE_ID = query.value("GRUPPE_ID").toInt();
        gruppe.strBESCHREIBUNG = query.value("BESCHREIBUNG").toString();
        m_vecGruppen.push_back(gruppe);
    }
}

void cMANAGER_InventurVERWALTUNG::FillVecZustaende()
{
    QString strsql = "select * from ZUSTAND";
    QSqlQuery query(m_db);
    query.prepare(strsql);
    query.exec();
    if(query.lastError().isValid())
    {
        QMessageBox msg;
        msg.setWindowTitle("Fehler in cMANAGER_InventurVERWALTUNG::FillVecZustaende");
        msg.setText(query.lastError().text());
        msg.exec();
        return;
    }
    m_vecZustaende.clear();
    while(query.next())
    {
        structZustand zustand;
        zustand.iZUSTAND_ID = query.value("ZUSTAND_ID").toInt();
        zustand.strBESCHREIBUNG = query.value("BESCHREIBUNG").toString();
        m_vecZustaende.push_back(zustand);
    }
}

void cMANAGER_InventurVERWALTUNG::FillVecAbteilungen()
{
    QString strsql = "select * from ABTEILUNG";
    QSqlQuery query(m_db);
    query.prepare(strsql);
    query.exec();
    if(query.lastError().isValid())
    {
        QMessageBox msg;
        msg.setWindowTitle("Fehler in cMANAGER_InventurVERWALTUNG::FillVecAbteilungen");
        msg.setText(query.lastError().text());
        msg.exec();
        return;
    }
    m_vecAbteilungen.clear();
    while(query.next())
    {
        structAbteilung abteilung;
        abteilung.iABTEILUNG_ID = query.value("ABTEILUNG_ID").toInt();
        abteilung.strBESCHREIBUNG = query.value("BESCHREIBUNG").toString();
        abteilung.dateANGELEGT_AM = query.value("ANGELEGT_AM").toDate();
        m_vecAbteilungen.push_back(abteilung);
    }
}

void cMANAGER_InventurVERWALTUNG::FillVecStandorte()
{
    QString strsql = "select * from STANDORT";
    QSqlQuery query(m_db);
    query.prepare(strsql);
    query.exec();
    if(query.lastError().isValid())
    {
        QMessageBox msg;
        msg.setWindowTitle("Fehler in cMANAGER_InventurVERWALTUNG::FillVecStandorte");
        msg.setText(query.lastError().text());
        msg.exec();
        return;
    }
    m_vecStandorte.clear();
    while(query.next())
    {
        structStandort standort;
        standort.iSTANDORT_ID = query.value("STANDORT_ID").toInt();
        standort.strBESCHREIBUNG = query.value("BESCHREIBUNG").toString();
        standort.strBUNDESLAND = query.value("BUNDESLAND").toString();
        standort.strPLZ = query.value("PLZ").toString();
        standort.strSTRASSE = query.value("STRASSE").toString();
        standort.iHAUS_NR = query.value("HAUS_NR").toInt();
        standort.strORT = query.value("ORT").toString();
        standort.strHAUSZUSATZ = query.value("HAUSZUSATZ").toString();
        m_vecStandorte.push_back(standort);
    }
}

void cMANAGER_InventurVERWALTUNG::FillVecBereiche()
{
    QString strsql = "select * from BEREICH";
    QSqlQuery query(m_db);
    query.prepare(strsql);
    query.exec();
    if(query.lastError().isValid())
    {
        QMessageBox msg;
        msg.setWindowTitle("Fehler in cMANAGER_InventurVERWALTUNG::FillVecBereiche");
        msg.setText(query.lastError().text());
        msg.exec();
        return;
    }
    m_vecBereiche.clear();
    while(query.next())
    {
        structBereich bereich;
        bereich.iBEREICH_ID = query.value("BEREICH_ID").toInt();
        bereich.strBESCHREIBUNG = query.value("BESCHREIBUNG").toString();
        m_vecBereiche.push_back(bereich);
    }
}


// ------------------------------------
// 2. SPEICHERN (Speicher...) (NEUE LOGIK)
// ------------------------------------

// --- Gegenstaende ---

bool cMANAGER_InventurVERWALTUNG::SpeicherGegenstand(structGegenstand& gegenstand)
{
    QString strSQL = "";
    if(gegenstand.iGEGENSTAENDE_ID <= 0) // Annahme: ID <= 0 bedeutet INSERT
        strSQL = "insert into GEGENSTAENDE (GEGENSTAENDE_ID, BEZEICHNUNG, SERIENNUMMER, ABTEILUNG_ID, GRUPPE_ID, STANDORT_ID, WERT_ANSCHAFFUNG, WERT_AKTUELL, ANGESCHAFFT_AM, NOTIZ, ZUSTAND_ID) values (:gid, :bez, :snr, :abtid, :gpid, :stid, :wa, :wak, :aa, :notiz, :zid)";
    else
        strSQL = "update GEGENSTAENDE set BEZEICHNUNG=:bez, SERIENNUMMER=:snr, ABTEILUNG_ID=:abtid, GRUPPE_ID=:gpid, STANDORT_ID=:stid, WERT_ANSCHAFFUNG=:wa, WERT_AKTUELL=:wak, ANGESCHAFFT_AM=:aa, NOTIZ=:notiz, ZUSTAND_ID=:zid where GEGENSTAENDE_ID = :gid";

    QSqlQuery query(m_db);
    query.prepare(strSQL);
    query.bindValue(":gid", gegenstand.iGEGENSTAENDE_ID);
    query.bindValue(":bez", gegenstand.strBEZEICHNUNG);
    query.bindValue(":snr", gegenstand.strSERIENNUMMER);
    query.bindValue(":abtid", gegenstand.ABTEILUNG_ID);
    query.bindValue(":gpid", gegenstand.GRUPPE_ID);
    query.bindValue(":stid", gegenstand.STANDORT_ID);
    query.bindValue(":wa", gegenstand.WERT_ANSCHAFFUNG);
    query.bindValue(":wak", gegenstand.WERT_AKTUELL);
    query.bindValue(":aa", gegenstand.ANGESCHAFFT_AM);
    query.bindValue(":notiz", gegenstand.NOTIZ);
    query.bindValue(":zid", gegenstand.ZUSTAND_ID);

    query.exec();
    return ExecuteSomeSQL(query);
}

// --- Person ---

bool cMANAGER_InventurVERWALTUNG::SpeicherPerson(structPerson& person)
{
    QString strSQL = "";
    if(person.iPERSONEN_ID <= 0)
        strSQL = "insert into PERSONEN (PERSONEN_ID, NAME, VORNAME, BENUTZERNAME, PASSWORT, BEREICH_ID, ZUSTAND_ID) values (:pid, :name, :vorname, :bname, :pw, :brid, :zid)";
    else
        strSQL = "update PERSONEN set NAME=:name, VORNAME=:vorname, BENUTZERNAME=:bname, PASSWORT=:pw, BEREICH_ID=:brid, ZUSTAND_ID=:zid where PERSONEN_ID = :pid";

    QSqlQuery query(m_db);
    query.prepare(strSQL);
    query.bindValue(":pid", person.iPERSONEN_ID);
    query.bindValue(":name", person.NAME);
    query.bindValue(":vorname", person.VORNAME);
    query.bindValue(":bname", person.BENUTZERNAME);
    query.bindValue(":pw", person.PASSWORT);
    query.bindValue(":brid", person.BEREICH_ID);
    query.bindValue(":zid", person.iZUSTAND_ID);

    query.exec();
    return ExecuteSomeSQL(query);
}


// --- Rolle ---

bool cMANAGER_InventurVERWALTUNG::SpeicherRolle(structRolle& rolle)
{
    QString strSQL = "";
    if(rolle.iID <= 0)
        strSQL = "insert into ROLLE (ID, Bez) values (:id, :bez)";
    else
        strSQL = "update ROLLE set Bez=:bez where ID = :id";

    QSqlQuery query(m_db);
    query.prepare(strSQL);
    query.bindValue(":id", rolle.iID);
    query.bindValue(":bez", rolle.strBez);

    query.exec();
    return ExecuteSomeSQL(query);
}


// --- Gruppe ---

bool cMANAGER_InventurVERWALTUNG::SpeicherGruppe(structGruppe& gruppe)
{
    QString strSQL = "";
    if(gruppe.iGRUPPE_ID <= 0)
        strSQL = "insert into GRUPPE (GRUPPE_ID, BESCHREIBUNG) values (:gid, :bes)";
    else
        strSQL = "update GRUPPE set BESCHREIBUNG=:bes where GRUPPE_ID = :gid";

    QSqlQuery query(m_db);
    query.prepare(strSQL);
    query.bindValue(":gid", gruppe.iGRUPPE_ID);
    query.bindValue(":bes", gruppe.strBESCHREIBUNG);

    query.exec();
    return ExecuteSomeSQL(query);
}


// --- Zustand ---

bool cMANAGER_InventurVERWALTUNG::SpeicherZustand(structZustand& zustand)
{
    QString strSQL = "";
    if(zustand.iZUSTAND_ID <= 0)
        strSQL = "insert into ZUSTAND (ZUSTAND_ID, BESCHREIBUNG) values (:zid, :bes)";
    else
        strSQL = "update ZUSTAND set BESCHREIBUNG=:bes where ZUSTAND_ID = :zid";

    QSqlQuery query(m_db);
    query.prepare(strSQL);
    query.bindValue(":zid", zustand.iZUSTAND_ID);
    query.bindValue(":bes", zustand.strBESCHREIBUNG);

    query.exec();
    return ExecuteSomeSQL(query);
}


// --- Abteilung ---

bool cMANAGER_InventurVERWALTUNG::SpeicherAbteilung(structAbteilung& abteilung)
{
    QString strSQL = "";
    if(abteilung.iABTEILUNG_ID <= 0)
        strSQL = "insert into ABTEILUNG (ABTEILUNG_ID, BESCHREIBUNG, ANGELEGT_AM) values (:aid, :bes, :aa)";
    else
        strSQL = "update ABTEILUNG set BESCHREIBUNG=:bes, ANGELEGT_AM=:aa where ABTEILUNG_ID = :aid";

    QSqlQuery query(m_db);
    query.prepare(strSQL);
    query.bindValue(":aid", abteilung.iABTEILUNG_ID);
    query.bindValue(":bes", abteilung.strBESCHREIBUNG);
    query.bindValue(":aa", abteilung.dateANGELEGT_AM);

    query.exec();
    return ExecuteSomeSQL(query);
}


// --- Standort ---

bool cMANAGER_InventurVERWALTUNG::SpeicherStandort(structStandort& standort)
{
    QString strSQL = "";
    if(standort.iSTANDORT_ID <= 0)
        strSQL = "insert into STANDORT (STANDORT_ID, BESCHREIBUNG, BUNDESLAND, PLZ, STRASSE, HAUS_NR, ORT, HAUSZUSATZ) values (:sid, :bes, :bl, :plz, :str, :hnr, :ort, :hz)";
    else
        strSQL = "update STANDORT set BESCHREIBUNG=:bes, BUNDESLAND=:bl, PLZ=:plz, STRASSE=:str, HAUS_NR=:hnr, ORT=:ort, HAUSZUSATZ=:hz where STANDORT_ID = :sid";

    QSqlQuery query(m_db);
    query.prepare(strSQL);
    query.bindValue(":sid", standort.iSTANDORT_ID);
    query.bindValue(":bes", standort.strBESCHREIBUNG);
    query.bindValue(":bl", standort.strBUNDESLAND);
    query.bindValue(":plz", standort.strPLZ);
    query.bindValue(":str", standort.strSTRASSE);
    query.bindValue(":hnr", standort.iHAUS_NR);
    query.bindValue(":ort", standort.strORT);
    query.bindValue(":hz", standort.strHAUSZUSATZ);

    query.exec();
    return ExecuteSomeSQL(query);
}


// --- Bereich ---

bool cMANAGER_InventurVERWALTUNG::SpeicherBereich(structBereich& bereich)
{
    QString strSQL = "";
    if(bereich.iBEREICH_ID <= 0)
        strSQL = "insert into BEREICH (BEREICH_ID, BESCHREIBUNG) values (:bid, :bes)";
    else
        strSQL = "update BEREICH set BESCHREIBUNG=:bes where BEREICH_ID = :bid";

    QSqlQuery query(m_db);
    query.prepare(strSQL);
    query.bindValue(":bid", bereich.iBEREICH_ID);
    query.bindValue(":bes", bereich.strBESCHREIBUNG);

    query.exec();
    return ExecuteSomeSQL(query);
}


// --- ANMELDEN (bleibt unverändert) ---

bool cMANAGER_InventurVERWALTUNG::Anmelden(QString strbenutzername, QString strPasswort)
{
    QString strsql = "select PERSONEN_ID, BENUTZERNAME, PASSWORT from PERSONEN where BENUTZERNAME = :benname and PASSWORT = HASHBYTES('SHA2_256', :passwd)";
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

    if(query.next())
    {
        return true;
    }

    return false;
}
