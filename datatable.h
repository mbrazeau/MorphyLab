#ifndef DATATABLE_H
#define DATATABLE_H

#include <QTableView>
#include <QObject>

class DataTable : public QTableView
{
    Q_OBJECT
public:
    explicit DataTable(QWidget *parent = nullptr);
//    QSize sizeHint() const override;

public slots:
    void contextMenuEvent(QContextMenuEvent *event) override;
};

#endif // DATATABLE_H
