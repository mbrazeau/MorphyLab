#ifndef CHARINFODIALOG_H
#define CHARINFODIALOG_H

#include <QDialog>
#include <QObject>
#include <QLayout>
#include <QLabel>

class CharInfoWidget;
class CharData;
class CharInfoDialog : public QDialog
{
public:
   explicit CharInfoDialog(CharData &cd, QWidget *parent = nullptr);

private:

    QVBoxLayout *m_layout;
    CharInfoWidget *m_charInfoWidget;
};

#endif // CHARINFODIALOG_H
