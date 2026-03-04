#ifndef CMYAPPLICATION_H
#define CMYAPPLICATION_H

#include <QApplication>
#include "cmanager_inventurverwaltung.h"

class CMyApplication : public QApplication
{
public:
    using QApplication::QApplication;
    cMANAGER_InventurVERWALTUNG* GetpManagerInventurV(){return &m_manager_inventurv;}
protected:
    cMANAGER_InventurVERWALTUNG m_manager_inventurv;
};

#endif // CMYAPPLICATION_H
