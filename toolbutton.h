#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QPushButton>

class ToolButton : public QPushButton
{
    Q_OBJECT

public:
    ToolButton(const QString & text, QWidget * parent = 0);
    ToolButton(QWidget * parent = 0);
    virtual ~ToolButton();


    void show();
    void setGeometry(int x, int y);
};

#endif // TOOLBUTTON_H
