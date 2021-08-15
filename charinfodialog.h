#ifndef CHARINFODIALOG_H
#define CHARINFODIALOG_H

#include <QDialog>
#include <QObject>
#include <QLayout>
#include <QLabel>
#include <QListView>

class CharInfoWidget;
class CharData;
class CharInfoDialog : public QDialog
{
public:
   explicit CharInfoDialog(CharData &cd, QWidget *parent = nullptr);

private:

    QGridLayout     *m_layout;
    QListView       *m_charListView;
    CharInfoWidget  *m_charInfoWidget;
};

#endif // CHARINFODIALOG_H
