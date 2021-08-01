#include "toolbutton.h"

ToolButton::ToolButton(const QString & text, QWidget * parent) : QPushButton(text, parent)
{
    QWidget::setFixedSize(35, 35);
}

ToolButton::ToolButton(QWidget * parent) : QPushButton(parent)
{
    QWidget::setFixedSize(35, 35);
}

ToolButton::~ToolButton()
{

}

void ToolButton::show()
{
    QPushButton::show();
}


void ToolButton::setGeometry(int x, int y)
{
    QPushButton::setGeometry(x, y, 40, 40);
}
