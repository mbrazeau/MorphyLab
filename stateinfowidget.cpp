#include <QFrame>

#include "stateinfowidget.h"

StateInfoWidget::StateInfoWidget(QWidget *parent) : QWidget(parent)
{
    m_stateSymbol = new QLineEdit;
    m_stateSymbol->setMaximumWidth(35); // << MAGIC NUMBER
    m_stateLabel = new QLineEdit;

    m_layout = new QHBoxLayout;

    m_addSubchars = new QPushButton;
    m_addSubchars->setText(tr("Add subcharacters..."));

    m_layout->addWidget(m_stateSymbol);
    m_layout->addWidget(m_stateLabel);
    m_layout->addWidget(m_addSubchars);

    setLayout(m_layout);
}
