#include "mainwindow.h"
#include "cdia_anmelden.h"
#include "cmyapplication.h"

#include <QMessageBox>
#include <QDialog>

int main(int argc, char *argv[])
{
    CMyApplication app(argc, argv);

    CDIA_ANMELDEN andlg;

    int nexec = -1;

    while((nexec = andlg.exec()) == QDialog::Accepted)
    {
        if(app.GetpManagerInventurV()->GetBenutzerNr() == -1)
        {
            QMessageBox msg;
            msg.setWindowTitle("Fehler");
            msg.setText("Falscher Benutzername oder falsches Passwort");
            msg.exec();
        }
        else
        {
            break;
        }
    }

    if(nexec == QDialog::Rejected)
    {
        exit(0);
    }


    MainWindow win;
    win.show();

    return app.exec();
}
