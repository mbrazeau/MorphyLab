#include <QMenu>

#include "datatable.h"
#include "charinfodialog.h"

DataTable::DataTable(QWidget *parent) : QTableView(parent)
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(contextMenuEvent(QContextMenuEvent *)));
}

void DataTable::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    QAction *showCharInfoAction = new QAction(tr("&Edit character info..."));
    menu.addAction(showCharInfoAction);
    connect(showCharInfoAction, &QAction::triggered, this, &CharInfoDialog::show);
    menu.show();
}
