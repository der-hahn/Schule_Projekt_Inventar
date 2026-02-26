#include "cdia_anmelden.h"
#include "ui_cdia_anmelden.h"
#include "cmanager_inventurverwaltung.h"
#include "cmyapplication.h"

CDIA_ANMELDEN::CDIA_ANMELDEN(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CDIA_ANMELDEN)
{
    ui->setupUi(this);
    m_nbenid = -1;
}

CDIA_ANMELDEN::~CDIA_ANMELDEN()
{
    delete ui;
}

void CDIA_ANMELDEN::on_pushButton_ok_clicked()
{
    ((CMyApplication*)qApp)->GetpManagerInventurV()->Anmelden(ui->lineEdit_benutzername->text(), ui->lineEdit_passwort->text());
    accept();

}

