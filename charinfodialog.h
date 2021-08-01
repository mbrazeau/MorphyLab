#ifndef CHARINFODIALOG_H
#define CHARINFODIALOG_H

#include <QDialog>
#include <QObject>
#include <QLayout>

class ToolButton;
class CharInfoDialog : public QDialog
{
public:
   explicit CharInfoDialog(QWidget *parent = nullptr);

private:
    ToolButton *tb;
};

#endif // CHARINFODIALOG_H
