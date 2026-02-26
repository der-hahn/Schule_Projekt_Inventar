#ifndef CMANAGER_GegenstaendeVERWALTUNG_H
#define CMANAGER_GegenstaendeVERWALTUNG_H

#include <QSqlDatabase>
#include <vector>
#include <QString>
#include <QDate>
#include <QSqlQuery>

// --- Strukturen (Bleiben unverändert) ---
// ... (structGegenstand, structRolle, structPerson, structGruppe, structZustand, structAbteilung, structStandort, structBereich) ...

struct structGegenstand
{
    int iGEGENSTAENDE_ID = 0;
    QString strBEZEICHNUNG = "";
    QString strSERIENNUMMER = "";
    int ABTEILUNG_ID = 0;
    int GRUPPE_ID = 0;
    int STANDORT_ID = 0;
    double WERT_ANSCHAFFUNG = 0;
    double WERT_AKTUELL = 0;
    QDate ANGESCHAFFT_AM;
    QString NOTIZ = "";
    int ZUSTAND_ID = 0;
    int iVerantwortlicher_ID = 0;
    QString strVerantwortlicherName = "";
};

struct structPerson
{
    int iPERSONEN_ID = 0;
    QString NAME = "";
    QString VORNAME = "";
    QString BENUTZERNAME = "";
    QString PASSWORT = "";  //Verhasht
    int BEREICH_ID = 0;
    int iZUSTAND_ID = 0;
};

struct structGruppe
{
    int iGRUPPE_ID = 0;
    QString strBESCHREIBUNG = "";
};

struct structZustand
{
    int iZUSTAND_ID = 0;
    QString strBESCHREIBUNG = "";
};

struct structAbteilung
{
    int iABTEILUNG_ID = 0;
    QString strBESCHREIBUNG = "";
    QDate dateANGELEGT_AM;
};

struct structStandort
{
    int iSTANDORT_ID = 0;
    QString strBESCHREIBUNG = "";
    QString strBUNDESLAND = "";
    QString strPLZ = "";
    QString strSTRASSE = "";
    int iHAUS_NR = 0;
    QString strORT = "";
    QString strHAUSZUSATZ = "";
};

struct structBereich
{
    int iBEREICH_ID = 0;
    QString strBESCHREIBUNG = "";
};

struct structFach
{
    int iFACH_ID = 0;
    QString strBEZEICHNUNG = "";
};

// --- Typedefs für Vektoren (Bleiben unverändert) ---
// ... (vecGegenstaende, vecPersonen, vecRollen, vecGruppen, vecZustaende, vecAbteilungen, vecStandorte, vecBereiche) ...

typedef std::vector<structGegenstand> vecGegenstaende;
typedef std::vector<structPerson> vecPersonen;
typedef std::vector<structGruppe> vecGruppen;
typedef std::vector<structZustand> vecZustaende;
typedef std::vector<structAbteilung> vecAbteilungen;
typedef std::vector<structStandort> vecStandorte;
typedef std::vector<structBereich> vecBereiche;
typedef std::vector<structFach> vecFach;


class cMANAGER_InventurVERWALTUNG
{
public:
    cMANAGER_InventurVERWALTUNG();
    ~cMANAGER_InventurVERWALTUNG();
    QSqlDatabase* Getdb() const { return const_cast<QSqlDatabase*>(&m_db);}

    // Hilfsfunktion für SQL-Ausführung
    bool ExecuteSomeSQL(const QSqlQuery& query);

    // Gegenstaende
    vecGegenstaende* GetvecGegenstaende() const { return const_cast<vecGegenstaende*>(&m_vecGegenstaende); }
    void FillVecGegenstaende(int izustandid=0);
    bool SpeicherGegenstand(structGegenstand& gegenstand); // NEU/GEÄNDERT

    // Person
    vecPersonen* GetvecPersonen() const { return const_cast<vecPersonen*>(&m_vecPersonen); }
    void FillVecPersonen();
    bool SpeicherPerson(structPerson& person); // NEU/GEÄNDERT


    // Gruppe
    vecGruppen* GetvecGruppen() const { return const_cast<vecGruppen*>(&m_vecGruppen); }
    void FillVecGruppen();
    bool SpeicherGruppe(structGruppe& gruppe); // NEU/GEÄNDERT

    // Zustand
    vecZustaende* GetvecZustaende() const { return const_cast<vecZustaende*>(&m_vecZustaende); }
    void FillVecZustaende();
    bool SpeicherZustand(structZustand& zustand); // NEU/GEÄNDERT

    // Abteilung
    vecAbteilungen* GetvecAbteilungen() const { return const_cast<vecAbteilungen*>(&m_vecAbteilungen); }
    void FillVecAbteilungen();
    bool SpeicherAbteilung(structAbteilung& abteilung); // NEU/GEÄNDERT

    // Standort
    vecStandorte* GetvecStandorte() const { return const_cast<vecStandorte*>(&m_vecStandorte); }
    void FillVecStandorte();
    bool SpeicherStandort(structStandort& standort); // NEU/GEÄNDERT

    // Bereich
    vecBereiche* GetvecBereiche() const { return const_cast<vecBereiche*>(&m_vecBereiche); }
    void FillVecBereiche();
    bool SpeicherBereich(structBereich& bereich); // NEU/GEÄNDERT

    // Fach
    vecFach* GetvecFach() const { return const_cast<vecFach*>(&m_vecFach); }
    void FillVecFach();
    bool SpeicherFach(structFach& fach); // NEU/GEÄNDERT

    bool Anmelden(QString strbenutzername, QString strPasswort);
public:
    QSqlDatabase m_db;

    bool LoescheGegenstand(int gegenstandid);
    bool Loeschevontabelle(int ipk, QString strtabname);
    bool LoeschePerson(int ipersonid);
    bool LoescheBereich(int ibereichid);
    bool LoescheStandort(int istandortid);
    bool LoescheAbteilung(int iabteilungid);
    bool LoescheZustand(int izustandid);
    bool LoescheGruppe(int igruppenid);
    QString GetVerantwortlicherName(int iverantwortlicherid);
    const int GetBenutzerNr(){return m_nbenutzernummer;}
protected:

    vecGegenstaende m_vecGegenstaende;
    vecPersonen m_vecPersonen;
    vecGruppen m_vecGruppen;
    vecZustaende m_vecZustaende;
    vecAbteilungen m_vecAbteilungen;
    vecStandorte m_vecStandorte;
    vecBereiche m_vecBereiche;
    vecFach m_vecFach;

    int m_nbenutzernummer;
};

#endif // CMANAGER_GegenstaendeVERWALTUNG_H
