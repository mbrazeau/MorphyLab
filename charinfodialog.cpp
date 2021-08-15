#include "charinfodialog.h"
#include <QDialogButtonBox>

#include "charinfowidget.h"
#include "toolbutton.h"

#include <iostream>

CharInfoDialog::CharInfoDialog(CharData &cd, QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Edit character"));

    m_layout = new QGridLayout;

    m_charListView = new QListView(this);

    m_charInfoWidget = new CharInfoWidget(cd, this);

    // Add a button box at the bottom
    QDialogButtonBox *buttonBox = new QDialogButtonBox(this);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox:: Ok);

    m_layout->addWidget(m_charListView, 0, 0, 1, 1);
    m_layout->addWidget(m_charInfoWidget, 0, 1, 1, 1);
    m_layout->addWidget(buttonBox, 1, 1, 1, 1);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    setLayout(m_layout);
}
