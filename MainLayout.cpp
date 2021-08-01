#include "MainLayout.h"

MainLayout::MainLayout(QWidget* parent, const QMargins &margins, int spacing) : QLayout(parent)
{
    setContentsMargins(margins);
    setSpacing(spacing);
}

MainLayout::MainLayout(int spacing)
{
    setSpacing(spacing);
}

MainLayout::~MainLayout()
{
    QLayoutItem *l;
    while ((l=takeAt(0))) {
        delete l;
    }
}

QSize MainLayout::sizeHint() const
{
    return calculateSize(SizeHint);
}

QSize MainLayout::minimumSize() const
{
    return calculateSize(MinimumSize);
}

//QSize MainLayout::maximumSize() const
//{
//    //
//}

Qt::Orientations MainLayout::expandingDirections() const
{
    return  Qt::Horizontal | Qt::Vertical;
}

bool MainLayout::hasHeightForWidth() const
{
    return false;
}

void MainLayout::setGeometry(const QRect &rect)
{
    ItemWrapper *centre = nullptr;
    int leftWidth = 0;
    int rightWidth = 0;
    int topHeight = 0;
    int bottomHeight = 0;
    int centreHeight = 0;
    int i = 0;

    QLayout::setGeometry(rect);

    for (i = 0; i < list.size(); ++i) {
        ItemWrapper *wrapper = list.at(i);
        QLayoutItem *item = wrapper->item;
        Position position = wrapper->position;

        if (position == Top) {
            item->setGeometry(QRect(rect.x(), topHeight, rect.width(), item->sizeHint().height()));
            topHeight += item->geometry().height() + spacing();
        } else if (position == Bottom) {
            item->setGeometry(QRect(item->geometry().x(), item->geometry().y(), rect.width(), item->sizeHint().height()));
            bottomHeight += item->geometry().height() + spacing();
            item->setGeometry(QRect(rect.x(),
                              rect.y() + rect.height() - bottomHeight + spacing(),
                              item->geometry().width(),
                              item->geometry().height()));
        } else if (position == Centre) {
            centre = wrapper;
        }
    }

    centreHeight = rect.height() - topHeight - bottomHeight;

    for (i = 0; i < list.size(); ++i) {
            ItemWrapper *wrapper = list.at(i);
            QLayoutItem *item = wrapper->item;
            Position position = wrapper->position;

            if (position == Left) {
//                item->setAlignment()
                item->setGeometry(QRect(rect.x() + leftWidth, topHeight,
                                        item->sizeHint().width(), centreHeight));

                leftWidth += item->geometry().width() + spacing();
            } else if (position == Right) {
                item->setGeometry(QRect(item->geometry().x(), item->geometry().y(),
                                        item->sizeHint().width(), centreHeight));

                rightWidth += item->geometry().width() + spacing();

                item->setGeometry(QRect(
                                  rect.x() + rect.width() - rightWidth + spacing(),
                                  topHeight, item->geometry().width(),
                                  item->geometry().height()));
            }
        }

        if (centre)
            centre->item->setGeometry(QRect(leftWidth, topHeight,
                                            rect.width() - rightWidth - leftWidth,
                                            centreHeight));

}

void MainLayout::addItem(QLayoutItem *item)
{
    add(item, Right);
}

void MainLayout::addWidget(QWidget *widget, Position position)
{
    add(new QWidgetItem(widget), position);
}

QLayoutItem *MainLayout::itemAt(int index) const
{
    ItemWrapper *wrapper = list.value(index);
    return wrapper ? wrapper->item : nullptr;
}

QLayoutItem *MainLayout::takeAt(int index)
{
    if (index >= 0 && index < list.size()) {
        ItemWrapper *layoutStruct = list.takeAt(index);
        return layoutStruct->item;
    }

    return nullptr;
}

int MainLayout::count() const
{
    return list.size();
}

void MainLayout::add(QLayoutItem *item, Position position)
{
    list.append(new ItemWrapper(item, position));
}

QSize MainLayout::calculateSize(SizeType sizeType) const
{
    QSize totalSize;

    return totalSize;
}
