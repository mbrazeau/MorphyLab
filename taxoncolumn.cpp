#include "taxoncolumn.h"

TaxonColumn::TaxonColumn(QWidget *parent) : QTableView(parent)
{

}

void TaxonColumn::moveTaxColumnDivider(int pos, int index)
{
    if (index > 1) return;  // This prevents the second splitter from mucking with the column width

    setColumnWidth(0, pos);
}
