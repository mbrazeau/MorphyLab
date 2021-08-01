#ifndef STATEDATATABLE_H
#define STATEDATATABLE_H

#include <QAbstractTableModel>

class StateDataTable : public QAbstractTableModel
{
public:
    explicit StateDataTable(QObject *parent = nullptr);


    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
};

#endif // STATEDATATABLE_H
