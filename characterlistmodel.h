#ifndef CHARACTERLISTMODEL_H
#define CHARACTERLISTMODEL_H

#include <QAbstractTableModel>
#include <QObject>

class CharData;

class CharacterListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CharacterListModel(QObject *parent = nullptr);


    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:
    QVector<CharData> *m_charData;
};

#endif // CHARACTERLISTMODEL_H
