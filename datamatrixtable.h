#ifndef DATAMATRIXTABLE_H
#define DATAMATRIXTABLE_H

#include <QTableView>

class DataMatrixTable : public QTableView
{
    Q_OBJECT
public:
    DataMatrixTable(QAbstractItemModel * model);
    ~DataMatrixTable();

protected:
      void resizeEvent(QResizeEvent *event) override;
      QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) override;
      void scrollTo (const QModelIndex & index, ScrollHint hint = EnsureVisible) override;

private:
      QTableView *dataMatrixTableView;
//      QTableView *taxonColumn;
      void init();
      void updateDataMatrixTableGeometry();

private slots:
      void updateSectionWidth(int logicalIndex, int oldSize, int newSize);
      void updateSectionHeight(int logicalIndex, int oldSize, int newSize);



};

#endif // DATAMATRIXTABLE_H
