#ifndef TAXONCOLUMN_H
#define TAXONCOLUMN_H

#include <QTableView>
#include <QObject>

class TaxonColumn : public QTableView
{
    Q_OBJECT

public:
    explicit TaxonColumn(QWidget *parent = nullptr);
    QSize sizeHint() const override;


    void moveTaxColumnDivider(int pos, int index);
};

#endif // TAXONCOLUMN_H
