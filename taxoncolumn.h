#ifndef TAXONCOLUMN_H
#define TAXONCOLUMN_H

#include <QTableView>
#include <QObject>

class TaxonColumn : public QTableView
{
public:
    explicit TaxonColumn(QWidget *parent = nullptr);

    void moveTaxColumnDivider(int pos, int index);
};

#endif // TAXONCOLUMN_H
