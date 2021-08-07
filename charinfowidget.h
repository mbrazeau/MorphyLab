#ifndef CHARINFOWIDGET_H
#define CHARINFOWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QTableWidget>
#include <QLabel>

#include "chardata.h"

class ToolButton;

class CharInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CharInfoWidget(CharData &cd, QWidget *parent = nullptr);

signals:

private:

    QLabel    *m_descripLabel;
    QLineEdit *m_description;
    QLabel    *m_notesLabel;
    QTextEdit *m_notes;
    QLabel       *m_statesLabel;
    QTableWidget *m_states;

    CharData    *m_charData;
    ToolButton  *m_tb;

};

#endif // CHARINFOWIDGET_H
