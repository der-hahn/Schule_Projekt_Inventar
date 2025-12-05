#ifndef CMANAGER_GegenstaendeVERWALTUNG_H
#define CMANAGER_GegenstaendeVERWALTUNG_H

#include <QSqlDatabase>
#include <vector>
#include <QString>

// --- Strukturen ---

struct structGegenstand
{
    int iID = 0;
    int iGruppeID = 0;
    int iFachID = 0;
    int iStatusID = 0;
    int iEigenschaft = 0;
    int iAbteilung = 0;
};

struct structRolle
{
    int iID = 0;
    QString strBez = "";
};

struct structPerson
{
    int iID = 0;
    QString strName = "";
    QString strVorname = "";
    int iRolle = 0;
    QString strPasswort = ""; //Verhasht
};

struct structGruppe
{
    int iID = 0;
    QString strBez = "";
};

struct structStatus
{
    int iID = 0;
    QString strBez = "";
    int iVerantwortlicherID = 0;
};

struct structFach
{
    int iID = 0;
    QString strBez = "";
};

struct structEigenschaft
{
    int iID = 0;
    QString strBez = "";
};

struct structAbteilung
{
    int iID = 0;
    QString strBez = "";
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

// --- Typedefs für Vektoren ---

typedef std::vector<structGegenstand> vecGegenstaende;
typedef std::vector<structPerson> vecPerson;
typedef std::vector<structRolle> vecRolle; // NEU
typedef std::vector<structGruppe> vecGruppe;
typedef std::vector<structStatus> vecStatus; // NEU
typedef std::vector<structFach> vecFach; // NEU
typedef std::vector<structEigenschaft> vecEigenschaft; // NEU
typedef std::vector<structAbteilung> vecAbteilung; // NEU
typedef std::vector<structStandort> vecStandort; // NEU


class cMANAGER_InventurVERWALTUNG
{
public:
    cMANAGER_InventurVERWALTUNG();
    ~cMANAGER_InventurVERWALTUNG();
    QSqlDatabase* Getdb() const { return const_cast<QSqlDatabase*>(&m_db);}

    // Hilfsfunktion für SQL-Ausführung
    bool ExecuteSomeSQL(QString strSQL); // NEU

    // Gegenstaende
    vecGegenstaende* getvecGegenstaende() const { return const_cast<vecGegenstaende*>(&m_vecGegenstaende); }
    void FillVecGegenstaende();
    bool UpdateGegenstand(structGegenstand& gegenstand); // NEU
    bool InsertGegenstand(structGegenstand& gegenstand); // NEU

    // Person
    vecPerson* GetvecPerson() const { return const_cast<vecPerson*>(&m_vecPerson); }
    void FillVecPerson();
    bool UpdatePerson(structPerson& person); // NEU
    bool InsertPerson(structPerson& person); // NEU

    // Rolle
    vecRolle* GetvecRolle() const { return const_cast<vecRolle*>(&m_vecRolle); }
    void FillVecRolle();
    bool UpdateRolle(structRolle& rolle); // NEU
    bool InsertRolle(structRolle& rolle); // NEU

    // Gruppe
    vecGruppe* GetvecGruppe() const { return const_cast<vecGruppe*>(&m_vecGruppe); }
    void FillVecGruppe();
    bool UpdateGruppe(structGruppe& gruppe); // NEU
    bool InsertGruppe(structGruppe& gruppe); // NEU

    // Status
    vecStatus* GetvecStatus() const { return const_cast<vecStatus*>(&m_vecStatus); }
    void FillVecStatus();
    bool UpdateStatus(structStatus& status); // NEU
    bool InsertStatus(structStatus& status); // NEU

    // Fach
    vecFach* GetvecFach() const { return const_cast<vecFach*>(&m_vecFach); }
    void FillVecFach();
    bool UpdateFach(structFach& fach); // NEU
    bool InsertFach(structFach& fach); // NEU

    // Eigenschaft
    vecEigenschaft* GetvecEigenschaft() const { return const_cast<vecEigenschaft*>(&m_vecEigenschaft); }
    void FillVecEigenschaft();
    bool UpdateEigenschaft(structEigenschaft& eigenschaft); // NEU
    bool InsertEigenschaft(structEigenschaft& eigenschaft); // NEU

    // Abteilung
    vecAbteilung* GetvecAbteilung() const { return const_cast<vecAbteilung*>(&m_vecAbteilung); }
    void FillVecAbteilung();
    bool UpdateAbteilung(structAbteilung& abteilung); // NEU
    bool InsertAbteilung(structAbteilung& abteilung); // NEU

    // Standort
    vecStandort* GetvecStandort() const { return const_cast<vecStandort*>(&m_vecStandort); }
    void FillVecStandort();
    bool UpdateStandort(structStandort& standort); // NEU
    bool InsertStandort(structStandort& standort); // NEU
    bool Anmelden(QString strbenutzername, QString strPasswort);
protected:
    QSqlDatabase m_db;

    vecGegenstaende m_vecGegenstaende;
    vecPerson m_vecPerson;
    vecRolle m_vecRolle; // NEU
    vecGruppe m_vecGruppe;
    vecStatus m_vecStatus; // NEU
    vecFach m_vecFach; // NEU
    vecEigenschaft m_vecEigenschaft; // NEU
    vecAbteilung m_vecAbteilung; // NEU
    vecStandort m_vecStandort; // NEU
};

#endif // CMANAGER_GegenstaendeVERWALTUNG_H
