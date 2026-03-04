#ifndef CDIA_ANMELDEN_H
#define CDIA_ANMELDEN_H

#include <QDialog>

namespace Ui {
class CDIA_ANMELDEN;
}

class CDIA_ANMELDEN : public QDialog
{
    Q_OBJECT

public:
    explicit CDIA_ANMELDEN(QWidget *parent = nullptr);
    ~CDIA_ANMELDEN();

    const int GetBenutzerID(){return m_nbenid;}

private slots:
    void on_pushButton_ok_clicked();

private:
    Ui::CDIA_ANMELDEN *ui;
    int m_nbenid;
};

#endif // CDIA_ANMELDEN_H
