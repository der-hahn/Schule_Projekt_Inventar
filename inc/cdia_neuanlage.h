#ifndef CDIA_NEUANLAGE_H
#define CDIA_NEUANLAGE_H

#include "cmanager_inventurverwaltung.h"

#include <QDialog>

namespace Ui {
class CDIA_NEUANLAGE;
}

class CDIA_NEUANLAGE : public QDialog
{
    Q_OBJECT

public:
    explicit CDIA_NEUANLAGE(QWidget *parent = nullptr);
    ~CDIA_NEUANLAGE();

    void showEvent(QShowEvent *event);
    void FillBildschirm();

    void SetGegenstaendeID(int igegenstaende_id){m_igegenstaende_id = igegenstaende_id;}
private:
    Ui::CDIA_NEUANLAGE *ui;
    cMANAGER_InventurVERWALTUNG *m_pmanager;

protected:
    int m_igegenstaende_id;
};

#endif // CDIA_NEUANLAGE_H
