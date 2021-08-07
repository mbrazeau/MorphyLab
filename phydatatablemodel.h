#ifndef PHYDATATABLEMODEL_H
#define PHYDATATABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QString>

#include "chardata.h"
#include "taxondata.h"
#include "chardata.h"
//#include "CellData.h"

class AbstractPhyData;

class PhyDataTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum PhyDataUserRoles {
        NexusOutputRole = Qt::UserRole,
        NexusInputRole = Qt::UserRole + 1
    };

    explicit PhyDataTableModel(QObject *parent = nullptr);
    ~PhyDataTableModel();

    QVariant data(const QModelIndex &index, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    void setDimensions(int nrows, int ncols);
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool insertColumns(int position, int cols, const QModelIndex &index = QModelIndex()) override;
    bool removeColumns(int position, int cols, const QModelIndex &index = QModelIndex()) override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:

    void deleteData();

    QVector<QString> headerLables;

    QVector<CharData> m_headerData;
    QVector<QVector<AbstractPhyData *>> m_dataMatrix;

};

#endif // PHYDATATABLEMODEL_H
