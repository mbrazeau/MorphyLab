#ifndef STATEINFOWIDGET_H
#define STATEINFOWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>

#include "chardata.h"

class StateInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StateInfoWidget(QWidget *parent = nullptr);

signals:

private:

    QHBoxLayout *m_layout;
    QLineEdit *m_stateSymbol;
    QLineEdit *m_stateLabel;
    QPushButton *m_addSubchars;
};

#endif // STATEINFOWIDGET_H
