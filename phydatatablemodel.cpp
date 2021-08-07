#include <QColor>
#include <iterator>

#include "phydatatablemodel.h"
#include "taxondata.h"
#include "CellData.h"
#include "ncl.h"

PhyDataTableModel::PhyDataTableModel(QObject *parent) : QAbstractTableModel(parent)
{
    headerLables.clear();
    m_headerData.clear();
    m_dataMatrix.clear();
}

PhyDataTableModel::~PhyDataTableModel()
{
    deleteData();
}

QVariant PhyDataTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        if (index.column() == 0 /*&& m_dataMatrix[index.row()][index.column()]*/) {
            // This is a taxon
            TaxonData* td = (TaxonData*)(m_dataMatrix[index.row()][index.column()]);
            QString s = QString::fromStdString(td->displayText());
            return s;
        } else {
            CellData* cd = (CellData*)(m_dataMatrix[index.row()][index.column()]);
            return QString::fromStdString(cd->displayText());
        }
    } else if (role == NexusOutputRole) {
        if (index.column() == 0 /*&& m_dataMatrix[index.row()][index.column()]*/) {
            // TODO: Do this for taxa
            QString s;
            return s;
        } else {
            CellData* cd = (CellData*)(m_dataMatrix[index.row()][index.column()]);
            return QString::fromStdString(cd->nexusStyleData());
        }
    } else if (role == Qt::TextAlignmentRole && index.column() > 0) {
        return Qt::AlignCenter;
    } else {
        return QVariant();
    }
}

int PhyDataTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_dataMatrix.size();
}

int PhyDataTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (m_dataMatrix.size() == 0) {
        return 0;
    }

    return m_dataMatrix.begin()->size();
}

QModelIndex PhyDataTableModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    if (m_dataMatrix.size() == 0) {
        return QModelIndex();
    }

    return createIndex(row, column);
}

QModelIndex PhyDataTableModel::parent(const QModelIndex &index) const
{
    QModelIndex idx;
    return idx;
}

bool PhyDataTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
//        dataMatrix[index.row()][index.column()] = value.toString();
        if (index.column() == 0) {
            // This is a taxon
            TaxonData* td = (TaxonData*)(m_dataMatrix[index.row()][index.column()]);
            std::string s = value.toString().toLocal8Bit().constData();
            td->setGenus(s);
        } else {
            // This is a data cell, so score the data
            CellData* cd = (CellData*)(m_dataMatrix[index.row()][index.column()]);
            if (!cd->scoreData(value.toString().toLocal8Bit().constData())) {
                return false;
            }
        }
        emit this->dataChanged(index, index);
        return true;
    } else if (role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    }

    return false;
}

void PhyDataTableModel::setDimensions(int nrows, int ncols)
{
    m_headerData.clear();
    headerLables.clear();

    headerLables.push_back(tr("Taxon"));

    deleteData();
    insertRows(0, nrows);
    insertColumns(1, ncols); // Add 1 for the taxon column
}

bool PhyDataTableModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    Q_UNUSED(parent)

    beginInsertRows(QModelIndex(), position, position + rows-1);

    for (int i = 0; i < rows; ++i) {
        QVector<AbstractPhyData *> v;
        TaxonData *td = new TaxonData;
        std::string name = "Taxon_";
        name.append(::to_string(i + position + 1));
        td->setGenus(name);
        v.insert(0, td);
        m_dataMatrix.insert(position + i, v);

        for (int j = 1; j < columnCount(); ++j) {
            CellData *cd = new CellData();
            m_dataMatrix[position + i].insert(j, cd);
        }
    }

    endInsertRows();
    return true;
}

bool PhyDataTableModel::insertColumns(int position, int cols, const QModelIndex &parent)
{
    Q_UNUSED(parent)

    beginInsertColumns(QModelIndex(), position, position+cols-1);

    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rowCount(); ++j) {

            AbstractPhyData * v = nullptr;
            if (position == 0) {
                v = new TaxonData();
            } else {
                v = new CellData();
            }

            m_dataMatrix[j].insert(i + position, v);
            headerLables.push_back("");
        }
    }

    // Tidy up header lables
    for (int i = position; i < columnCount() && i > 0; ++i) {
        headerLables[i] = QString::number(i);
        m_headerData.push_back(CharData());
    }

    endInsertColumns();
    return true;
}

bool PhyDataTableModel::removeColumns(int position, int cols, const QModelIndex &index)
{
    beginRemoveColumns(QModelIndex(), position, position+cols-1);

    if (position == 0) {
        return false;
    }

    m_headerData.remove(position-1, 1);
    for (int i = 0; i < rowCount(); ++i) {
        CellData* cd = (CellData*)m_dataMatrix[i][position];
        delete cd;
        m_dataMatrix[i].remove(position);
    }

    endRemoveColumns();
    return true;
}

bool PhyDataTableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    // Remove the rows

    TaxonData* td =  (TaxonData*)m_dataMatrix[position][0];
    delete td;
    for (int i = 1; i < columnCount(); ++i) {
        CellData* cd = (CellData*)m_dataMatrix[position][i];
        delete cd;
    }

    m_dataMatrix.remove(position, 1); // NOTE: This and the above need iteration for myltiple rows

    endRemoveRows();
    return true;
}

QVariant PhyDataTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
       return headerLables[section];
    else if (orientation == Qt::Vertical && role == Qt::DisplayRole)
        return QString::number(section+1);
    else if (role == Qt::ToolTipRole)
        return QString::number(section); // TODO: Could add character description
    else
       return QVariant();
}

bool PhyDataTableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

   if (orientation == Qt::Horizontal) {
       headerLables[section] = value.toString();
       emit headerDataChanged(orientation, section, section);
   }

    return true;
}

Qt::ItemFlags PhyDataTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    if (!index.isValid())
        return Qt::ItemIsSelectable;

    flags |= Qt::ItemIsEditable;

    return flags;
}

void PhyDataTableModel::deleteData()
{
    for (int i = 0; i < m_dataMatrix.size(); ++i) {
        for (int j = 0; j < m_dataMatrix[i].size(); ++j) {
            delete m_dataMatrix[i][j];
            m_dataMatrix[i].clear();
        }
    }
    m_dataMatrix.clear();
}
