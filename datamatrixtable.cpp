#include <QScrollBar>
#include <QHeaderView>

#include "datamatrixtable.h"

DataMatrixTable::DataMatrixTable(QAbstractItemModel * model)
{
    setModel(model);
    dataMatrixTableView = new QTableView(this);
//    taxonColumn = new QTableView(this);

    init();

    //connect the headers and scrollbars of both tableviews together
    connect(horizontalHeader(),&QHeaderView::sectionResized, this,
            &DataMatrixTable::updateSectionWidth);
    connect(verticalHeader(),&QHeaderView::sectionResized, this,
            &DataMatrixTable::updateSectionHeight);

    connect(dataMatrixTableView->verticalScrollBar(), &QAbstractSlider::valueChanged,
            verticalScrollBar(), &QAbstractSlider::setValue);
    connect(verticalScrollBar(), &QAbstractSlider::valueChanged,
            dataMatrixTableView->verticalScrollBar(), &QAbstractSlider::setValue);

}

DataMatrixTable::~DataMatrixTable()
{
    delete dataMatrixTableView;
}

void DataMatrixTable::init()
{
      dataMatrixTableView->setModel(model());
      dataMatrixTableView->setFocusPolicy(Qt::NoFocus);
      dataMatrixTableView->verticalHeader()->hide();
      dataMatrixTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

      viewport()->stackUnder(dataMatrixTableView);

     /* dataMatrixTableView->setStyleSheet("QTableView { border: none;"
                                     "background-color: #8EDE21;"
                                     "selection-background-color: #999}"); *///for demo purposes

      dataMatrixTableView->setSelectionModel(selectionModel());
//      for (int col = 1; col < model()->columnCount(); ++col)
//            dataMatrixTableView->setColumnWidth(col, 30);

      dataMatrixTableView->setColumnWidth(0, columnWidth(0) );

      dataMatrixTableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
      dataMatrixTableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
      dataMatrixTableView->show();

      updateDataMatrixTableGeometry();

      setHorizontalScrollMode(ScrollPerPixel);
      setVerticalScrollMode(ScrollPerPixel);
      dataMatrixTableView->setVerticalScrollMode(ScrollPerPixel);
}


void DataMatrixTable::updateSectionWidth(int logicalIndex, int /* oldSize */, int newSize)
{
      if (logicalIndex == 0){
            dataMatrixTableView->setColumnWidth(0, newSize);
            updateDataMatrixTableGeometry();
      }
}

void DataMatrixTable::updateSectionHeight(int logicalIndex, int /* oldSize */, int newSize)
{
      dataMatrixTableView->setRowHeight(logicalIndex, newSize);
}
//! [sections]


//! [resize]
void DataMatrixTable::resizeEvent(QResizeEvent * event)
{
      QTableView::resizeEvent(event);
      updateDataMatrixTableGeometry();
 }
//! [resize]


//! [navigate]
QModelIndex DataMatrixTable::moveCursor(CursorAction cursorAction,
                                          Qt::KeyboardModifiers modifiers)
{
      QModelIndex current = QTableView::moveCursor(cursorAction, modifiers);

      if (cursorAction == MoveLeft && current.column() > 0
              && visualRect(current).topLeft().x() < dataMatrixTableView->columnWidth(0) ){
            const int newValue = horizontalScrollBar()->value() + visualRect(current).topLeft().x()
                                 - dataMatrixTableView->columnWidth(0);
            horizontalScrollBar()->setValue(newValue);
      }
      return current;
}
//! [navigate]

void DataMatrixTable::scrollTo (const QModelIndex & index, ScrollHint hint){
    if (index.column() > 0)
        QTableView::scrollTo(index, hint);
}

//! [geometry]
void DataMatrixTable::updateDataMatrixTableGeometry()
{
      dataMatrixTableView->setGeometry(verticalHeader()->width() + frameWidth(),
                                   frameWidth(), columnWidth(0),
                                   viewport()->height()+horizontalHeader()->height());
}

