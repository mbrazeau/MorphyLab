#include "characterlistmodel.h"
#include "phydatatablemodel.h"

CharacterListModel::CharacterListModel(QObject *parent) : QAbstractTableModel(parent)
{

}



QModelIndex CharacterListModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    if (m_charData->size() == 0) {
        return QModelIndex();
    }

    return createIndex(row, column);
}

QModelIndex CharacterListModel::parent(const QModelIndex &child) const
{
    QModelIndex idx;
    return idx;
}

int CharacterListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

int CharacterListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_charData->size();
}

QVariant CharacterListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() > 1)
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
            return QString("Character %1").arg(index.column());
    }
//    } else if (role == PhyDataTableModel::NexusOutputRole) {
//        if (index.column() == 0 /*&& m_dataMatrix[index.row()][index.column()]*/) {
//            // TODO: Do this for taxa
//            QString s;
//            return s;
//        } else {
//            CellData* cd = (CellData*)(m_dataMatrix[index.row()][index.column()]);
//            return QString::fromStdString(cd->nexusStyleData());
//        }
//    }
    else if (role == Qt::TextAlignmentRole && index.column() > 0) {
        return Qt::AlignCenter;
    } else {
        return QVariant();
    }
}
