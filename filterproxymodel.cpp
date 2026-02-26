#include "filterproxymodel.h"

void FilterProxyModel::setFilterValues(const QString &abt,
                                       const QString &grp,
                                       const QString &ver)
{
    m_abtText = abt;
    m_grpText = grp;
    m_verText = ver;
    invalidate();   // 🔥 erlaubt, weil eigene Klasse
}

bool FilterProxyModel::filterAcceptsRow(int row,
                                        const QModelIndex &parent) const
{
    QModelIndex idxAbt = sourceModel()->index(row, 3, parent);  // Spalte Abteilung
    QModelIndex idxGrp = sourceModel()->index(row, 4, parent);  // Spalte Gruppe
    QModelIndex idxVer = sourceModel()->index(row, 5, parent);  // Spalte Verantwortlicher

    QString abtValue = idxAbt.data().toString();
    QString grpValue = idxGrp.data().toString();
    QString verValue = idxVer.data().toString();

    // UND-Logik
    if (m_abtText != "Alle" && abtValue != m_abtText)
        return false;

    if (m_grpText != "Alle" && grpValue != m_grpText)
        return false;

    if (m_verText != "Alle" && verValue != m_verText)
        return true;

    return true;
}
