#include <QMenu>
#include <QScrollBar>
#include <QScrollArea>

#include "datatable.h"
#include "charinfodialog.h"

DataTable::DataTable(QWidget *parent) : QTableView(parent)
{
    setContextMenuPolicy(Qt::CustomContextMenu);
}

//QSize DataTable::sizeHint() const
//{
//    QSize newSize = QTableView::sizeHint();

//    newSize.setWidth(newSize.width() + verticalScrollBar()->width());
//    newSize.setHeight(newSize.height() + horizontalScrollBar()->width());

//    return newSize;
//}

void DataTable::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    QAction *showCharInfoAction = new QAction(tr("&Edit character info..."));
    menu.addAction(showCharInfoAction);
    connect(showCharInfoAction, &QAction::triggered, this, &CharInfoDialog::show);
    menu.show();
}
