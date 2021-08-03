#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QSplitter>
#include <QScrollArea>
#include <QDialog>


#include "phydatatablemodel.h"
#include "charinfodialog.h"

class ToolButton;
class QTableView;
class MorphyLabNexusReader;
class MainLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:

    void createMenus();
    void createMainWindow();
    void setButtonsDisabled(bool d);
    void createToolButtons();

    void addCharacters();
    void addTaxa();

    void createTableViews();
    void fileOpen();
    void save();
    void fileNew();
    void fileImport();
    void fileExport();
    void fileClose();
    void aboutMenu();

    void createDataTables();
    void initDataTableDisplay();
    void launchTableDisplay();
    void closeDisplay();

    void showMessage(QString message);

    // Tool buttons
    ToolButton *bNewChar;
    ToolButton *bNewTax;
    ToolButton *bDelete;
    ToolButton *bMerge;
    ToolButton *bDiff;
    ToolButton *bInfo;

    QWidget *mainWidget;

    QHBoxLayout *mainLayout;
    QVBoxLayout *taxonButtonLayout;
    QSplitter   *matrixAreaSplitter;
    QScrollArea *scrollArea;
    CharInfoDialog *cd;

    PhyDataTableModel *dataModel;
    QTableView *dataTable;
    QTableView *dataTable2;
    QTableView *taxonColumn;
    QStringList tableHeader;

    MorphyLabNexusReader    *reader;
    QFileDialog             fopen;

    QString styleSheet = "QHeaderView {"
                         "spacing: 10px;"
                         "background-color: rgb(38, 88, 130);}"
                         "QTableCornerButton::section {"
                         "spacing: 10px;"
                         "background-color: rgb(38, 88, 130);}"
                         "QTableView {"
                         "selection-background-color: #b8b8b8;"
                         "selection-color: black;"
                         "background-color: #faf9e3;}"
                         "QTableView::item {"
                         "color: black;}";
signals:

};

#endif // MAINWINDOW_H
