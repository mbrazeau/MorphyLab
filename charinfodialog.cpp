#include <QTextEdit>
#include <QTableWidget>

#include "charinfodialog.h"
#include "toolbutton.h"

#include <iostream>

CharInfoDialog::CharInfoDialog(QWidget *parent) : QDialog(parent)
{
    setMinimumSize(900, 300);
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);


    QTextEdit *descript = new QTextEdit;

    layout->addWidget(descript);

    QTableWidget *states = new QTableWidget;
    states->setMaximumWidth(300);
    layout->addWidget(states);

    setWindowTitle(tr("A dialog"));
}
