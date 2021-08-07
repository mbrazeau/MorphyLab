#ifndef DATATABLE_H
#define DATATABLE_H

#include <QTableView>
#include <QObject>

class DataTable : public QTableView
{
public:
    explicit DataTable(QWidget *parent = nullptr);

public slots:
    void contextMenuEvent(QContextMenuEvent *event);
};

#endif // DATATABLE_H
