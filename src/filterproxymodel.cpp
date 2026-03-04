#include "filterproxymodel.h"

void FilterProxyModel::setFilterValues(const QString &abt,
                                       const QString &grp,
                                       const QString &ver,
                                       const QString &lag)
{
    m_abtText = abt;
    m_grpText = grp;
    m_verText = ver;
    m_lagText = lag;
    invalidate();   // 🔥 erlaubt, weil eigene Klasse
}

bool FilterProxyModel::filterAcceptsRow(int row,
                                        const QModelIndex &parent) const
{
    QModelIndex idxAbt = sourceModel()->index(row, 3, parent);  // Spalte Abteilung
    QModelIndex idxGrp = sourceModel()->index(row, 4, parent);  // Spalte Gruppe
    QModelIndex idxVer = sourceModel()->index(row, 5, parent);  // Spalte Verantwortlicher
    QModelIndex idxLag = sourceModel()->index(row, 6, parent);  // Lager bzw. Standort

    QString abtValue = idxAbt.data().toString();
    QString grpValue = idxGrp.data().toString();
    QString verValue = idxVer.data().toString();
    QString lagValue = idxLag.data().toString();

    // UND-Logik
    if (m_abtText != "Alle" && abtValue != m_abtText)
        return false;

    if (m_grpText != "Alle" && grpValue != m_grpText)
        return false;

    if (m_verText != "Alle" && verValue != m_verText)
        return false;

    if (m_lagText != "Alle" && lagValue  != m_lagText)
        return false;
    return true;
}
