#include <QScrollBar>
#include <QScrollArea>

#include "taxoncolumn.h"

TaxonColumn::TaxonColumn(QWidget *parent) : QTableView(parent)
{
}

QSize TaxonColumn::sizeHint() const
{
    QSize newSize = QTableView::sizeHint();

    newSize.setWidth(newSize.width() + verticalScrollBar()->width());
    newSize.setHeight(newSize.height() + horizontalScrollBar()->width());

    return newSize;
}

void TaxonColumn::moveTaxColumnDivider(int pos, int index)
{
    if (index > 1) return;  // This prevents the second splitter from mucking with the column width

    setColumnWidth(0, pos);
}
