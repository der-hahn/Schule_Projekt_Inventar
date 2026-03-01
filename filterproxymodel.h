#ifndef FILTERPROXYMODEL_H
#define FILTERPROXYMODEL_H
#pragma once
#include <QSortFilterProxyModel>

class FilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    void setFilterValues(const QString &abt,
                         const QString &grp,
                         const QString &ver,
                         const QString &lag);

protected:
    bool filterAcceptsRow(int source_row,
                          const QModelIndex &source_parent) const override;

private:
    QString m_abtText;
    QString m_grpText;
    QString m_verText;
    QString m_lagText;
};

#endif // FILTERPROXYMODEL_H
