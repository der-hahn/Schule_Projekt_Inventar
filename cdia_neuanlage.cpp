#include "cdia_neuanlage.h"
#include "cmyapplication.cpp"
#include "ui_cdia_neuanlage.h"

CDIA_NEUANLAGE::CDIA_NEUANLAGE(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CDIA_NEUANLAGE)
{
    ui->setupUi(this);
    m_pmanager = ((CMyApplication*)qApp)->GetpManagerInventurV();
    m_igegenstaende_id = 0;
}

CDIA_NEUANLAGE::~CDIA_NEUANLAGE()
{
    delete ui;
}


void CDIA_NEUANLAGE::showEvent(QShowEvent* event)
{

    FillBildschirm();

    QDialog::showEvent(event);

}

void CDIA_NEUANLAGE::FillBildschirm()
{
    //Abteilung
    //Gruppe
    //Standort
    //Zustand
    //verantwortlicher



    m_pmanager->FillVecAbteilungen();
    m_pmanager->FillVecGruppen();
    m_pmanager->FillVecStandorte();
    m_pmanager->FillVecZustaende();
    m_pmanager->FillVecPersonen();


    const auto pvecabteilungen = m_pmanager->GetvecAbteilungen();
    for(int i = 0; i < pvecabteilungen->size(); i++)
    {
        const auto& abteilung = pvecabteilungen->at(i);
        ui->comboBox_abt->addItem(abteilung.strBESCHREIBUNG, abteilung.iABTEILUNG_ID);
    }


    const auto pvecgruppe = m_pmanager->GetvecGruppen();
    for(int i = 0; i < pvecgruppe->size(); i++)
    {
        const auto& gruppe = pvecgruppe->at(i);
        ui->comboBox_gruppe->addItem(gruppe.strBESCHREIBUNG, gruppe.iGRUPPE_ID);
    }

    const auto pvecStandort = m_pmanager->GetvecStandorte();
    for(int i = 0; i < pvecStandort->size(); i++)
    {
        const auto& standort = pvecStandort->at(i);
        ui->comboBox_standort->addItem(standort.strBESCHREIBUNG, standort.iSTANDORT_ID);
    }

    const auto pvecZustand = m_pmanager->GetvecZustaende();
    for(int i = 0; i < pvecZustand->size(); i++)
    {
        const auto& zustand = pvecZustand->at(i);
        ui->comboBox_zustand->addItem(zustand.strBESCHREIBUNG, zustand.iZUSTAND_ID);
    }


    const auto pvecpersonen = m_pmanager->GetvecPersonen();
    for(int i = 0; i < pvecpersonen->size(); i++)
    {
        const auto& person = pvecpersonen->at(i);
        ui->comboBox_verantwortlicher->addItem(person.VORNAME + " " + person.NAME, person.iPERSONEN_ID);
    }

    int iindex_verantwortlicher = ui->comboBox_verantwortlicher->findData(m_pmanager->GetBenutzerNr());
    ui->comboBox_verantwortlicher->setCurrentIndex(iindex_verantwortlicher);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if(m_igegenstaende_id > 0)
    {


        m_pmanager->FillVecGegenstaende(0, m_igegenstaende_id);

        const auto gegenstand = m_pmanager->GetvecGegenstaende()->at(0);


        int iindex_abteilung = ui->comboBox_abt->findData(gegenstand.ABTEILUNG_ID);
        int iindex_gruppe = ui->comboBox_gruppe->findData(gegenstand.GRUPPE_ID);
        int iindex_standort = ui->comboBox_standort->findData(gegenstand.STANDORT_ID);
        int iindex_zustand = ui->comboBox_zustand->findData(gegenstand.ZUSTAND_ID);
        iindex_verantwortlicher = ui->comboBox_verantwortlicher->findData(gegenstand.iVerantwortlicher_ID);


        // Werte setzen
        ui->comboBox_abt->setCurrentIndex(iindex_abteilung);
        ui->comboBox_gruppe->setCurrentIndex(iindex_gruppe);
        ui->comboBox_standort->setCurrentIndex(iindex_standort);
        ui->comboBox_zustand->setCurrentIndex(iindex_zustand);
        ui->comboBox_verantwortlicher->setCurrentIndex(iindex_verantwortlicher);





        ui->lineEdit_bez->setText(gegenstand.strBEZEICHNUNG);
        ui->lineEdit_seriennr->setText(gegenstand.strSERIENNUMMER);
        ui->doubleSpinBox_ansch->setValue(gegenstand.WERT_ANSCHAFFUNG);
        ui->doubleSpinBox_wertak->setValue(gegenstand.WERT_AKTUELL);
        ui->dateEdit_anscham->setDate(gegenstand.ANGESCHAFFT_AM);
        ui->lineEdit_notiz->setText(gegenstand.NOTIZ);

        if(gegenstand.iVerantwortlicher_ID != m_pmanager->GetBenutzerNr())
        {
            ui->lineEdit_bez->setEnabled(false);
            ui->comboBox_abt->setEnabled(false);
            ui->comboBox_gruppe->               setEnabled(false);//setCurrentIndex(iindex_gruppe);
            ui->comboBox_standort->             setEnabled(false);//setCurrentIndex(iindex_standort);
            ui->comboBox_zustand->              setEnabled(false);//setCurrentIndex(iindex_zustand);
            ui->comboBox_verantwortlicher->     setEnabled(false);//setCurrentIndex(iindex_verantwortlicher);
            ui->lineEdit_seriennr->             setEnabled(false);//setText(gegenstand.strSERIENNUMMER);
            ui->doubleSpinBox_ansch->           setEnabled(false);//setValue(gegenstand.WERT_ANSCHAFFUNG);
            ui->doubleSpinBox_wertak->          setEnabled(false);//setValue(gegenstand.WERT_AKTUELL);
            ui->dateEdit_anscham->              setEnabled(false);//setDate(gegenstand.ANGESCHAFFT_AM);
            ui->lineEdit_notiz->                setEnabled(false);//setText(gegenstand.NOTIZ);
        }

    }


}
