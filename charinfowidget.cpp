#include <QRect>
#include <QFrame>
#include <QScrollArea>
#include "charinfowidget.h"
#include "stateinfowidget.h"

CharInfoWidget::CharInfoWidget(CharData &cd, QWidget *parent) : QWidget(parent)
{
    m_charData = &cd;

    setMinimumSize(900, 300); // <<<< MAGIC NUMBERS
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    m_descripLabel = new QLabel;
    m_descripLabel->setText(tr("Description:"));

    m_description = new QLineEdit;

    m_statesLabel = new QLabel;
    m_statesLabel->setText(tr("States:"));

    m_notesLabel = new QLabel;
    m_notesLabel->setText(tr("Notes:"));
    m_notes = new QTextEdit;

    layout->addWidget(m_descripLabel);
    layout->addWidget(m_description);
    layout->addWidget(m_statesLabel);

    // TODO: This is temporary: need a dynamic layout manager here:
    layout->addWidget(new StateInfoWidget(this));
    layout->addWidget(new StateInfoWidget(this));

//    layout->addWidget(m_states);
    layout->addWidget(m_notesLabel);
    layout->addWidget(m_notes);
}
