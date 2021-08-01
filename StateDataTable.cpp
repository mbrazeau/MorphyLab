#include "StateDataTable.h"

StateDataTable::StateDataTable(QObject *parent) : QAbstractTableModel(parent)
{
}

QModelIndex StateDataTable::index(int row, int column, const QModelIndex &parent) const
{
}

QModelIndex StateDataTable::parent(const QModelIndex &child) const
{
}

int StateDataTable::rowCount(const QModelIndex &parent) const
{
}

int StateDataTable::columnCount(const QModelIndex &parent) const
{
}

QVariant StateDataTable::data(const QModelIndex &index, int role) const
{
}
