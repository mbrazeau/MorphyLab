
#include <QTableWidget>
#include <QMenuBar>
#include <QScrollBar>
#include <QHeaderView>
#include <QPalette>
#include <QIcon>
#include <QLineEdit>
#include <QMessageBox>
#include <QTextStream>
#include <QItemSelectionModel>
#include <QInputDialog>
#include <QScreen>
#include <QApplication>

#include "ncl.h"
#include "MainLayout.h"
#include "MorphyLabNexusReader.h"
#include "MainWindow.h"
#include "toolbutton.h"
#include "phydatatablemodel.h"
#include "charinfodialog.h"

MainWindow::MainWindow() : QMainWindow()
{
    // Initialise variables:
    mainLayout = nullptr;
    dataModel = nullptr;
    dataTable = nullptr;
    dataTable2 = nullptr;
    taxonColumn = nullptr;
    tableHeader.clear();

    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    QPalette pal = this->palette();

    pal.setColor(QPalette::Window, QColor(0, 38, 69));
    setAutoFillBackground(true);
    setPalette(pal);

    reader = new MorphyLabNexusReader;
    createMenus();
    setWindowTitle("MorphyLab");

//    createMainWindow();
}

void MainWindow::createMenus()
{
    // Create the menus

    // File menu
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *newAct = new QAction(tr("&New..."), this);
    fileMenu->addAction(newAct);
    newAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    connect(newAct, &QAction::triggered, this, &MainWindow::fileNew);

    QAction *openAct = new QAction(tr("&Open..."), this);
    fileMenu->addAction(openAct);
    openAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    connect(openAct, &QAction::triggered, this, &MainWindow::fileOpen);

    QAction *saveAct = new QAction(tr("&Save..."), this);
    fileMenu->addAction(saveAct);
    saveAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    QAction *importAct = new QAction(tr("&Import..."), this);
    fileMenu->addAction(importAct);
    connect(importAct, &QAction::triggered, this, &MainWindow::fileImport);

    QAction *exportAct = new QAction(tr("&Export..."), this);
    fileMenu->addAction(exportAct);
    connect(exportAct, &QAction::triggered, this, &MainWindow::fileExport);


    // Edit menu
    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    QAction *copyAction = new QAction(tr("&Copy"), this);
    editMenu->addAction(copyAction);

    // Taxa Menu
    QMenu *taxaMenu = menuBar()->addMenu(tr("&Taxa"));
    QAction *addTaxaAction = new QAction(tr("&Add taxa..."), this);
    taxaMenu->addAction(addTaxaAction);

    // Characters menu
    QMenu *charsMenu = menuBar()->addMenu(tr("&Characters"));
    QAction *addCharsAction = new QAction(tr("&Add characters..."), this);
    charsMenu->addAction(addCharsAction);
    QAction *editCharInfo = new QAction(tr("&Edit character..."), this);
    charsMenu->addAction(editCharInfo);
    charsMenu->addSeparator();
    QAction *mergeChars = new QAction(tr("&Merge characters"), this);
    charsMenu->addAction(mergeChars);
    QAction *splitChar = new QAction(tr("&Split character"), this);
    charsMenu->addAction(splitChar);
    charsMenu->addSeparator();
    QAction *defineNetwork = new QAction(tr("&Define hierarchy..."), this);
    charsMenu->addAction(defineNetwork);
    QAction *defineCharModel = new QAction(tr("&Set type/model..."), this);
    charsMenu->addAction(defineCharModel);
//    charsMenu->addSeparator();

    // Help
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

    QAction *aboutAction = new QAction(tr("&About"), this);
    helpMenu->addAction(aboutAction);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::aboutMenu);
}

//void MainWindow::createLayout()
//{

//    matrixAreaSplitter = new QSplitter;

//    mlay = new MainLayout;

//    dataModel = new PhyDataTableModel;//(this);
//    dataTable = new QTableView;//(this);
//    taxonColumn = new QTableView;//(this);

//    matrixAreaSplitter->addWidget(taxonColumn);
//    matrixAreaSplitter->addWidget(dataTable);

////    taxonColumn->setModel(dataModel);

//    mlay->addWidget(matrixAreaSplitter, MainLayout::Centre);

//    bNew    = new ToolButton("New");
//    bSplit  = new ToolButton("Split");
//    bMerge  = new ToolButton("Merge");
//    bDiff   = new ToolButton("Diff");
//    bInfo   = new ToolButton("Info");

//    mlay->addWidget(bNew, MainLayout::Left);
//    mlay->addWidget(bSplit, MainLayout::Left);
//    mlay->addWidget(bMerge, MainLayout::Left);
//    mlay->addWidget(bDiff, MainLayout::Left);
//    mlay->addWidget(bInfo, MainLayout::Left);
////    mlay->addStretch();

//    mainWidget->setLayout(mlay);
//}

void MainWindow::createMainWindow()
{
    mainLayout = new QHBoxLayout(mainWidget);
    taxonButtonLayout = new QVBoxLayout;

    createToolButtons();

    createTableViews();

    mainWidget->setLayout(mainLayout);
}

void MainWindow::createToolButtons()
{
    // Create the buttons
    ToolButton *bNewChar;
    ToolButton *bNewTax;
    ToolButton *bDelete;
    ToolButton *bMerge;
    ToolButton *bDiff;
    ToolButton *bInfo;

    bNewChar    = new ToolButton(this);
    bNewTax     = new ToolButton(this);
    bDelete      = new ToolButton(this);
    bMerge      = new ToolButton(this);
    bDiff       = new ToolButton(this);
    bInfo       = new ToolButton(this);

    taxonButtonLayout->addWidget(bNewChar);
    connect(bNewChar, &QPushButton::clicked, this, &MainWindow::addCharacters);
    bNewChar->setIcon(QIcon("/Users/mbrazeau/Code/MorphyLab/support/add-col.png"));
    bNewChar->setToolTip(tr("Add characters"));

    taxonButtonLayout->addWidget(bNewTax);
    connect(bNewTax, &QPushButton::clicked, this, &MainWindow::addTaxa);
    bNewTax->setIcon(QIcon("/Users/mbrazeau/Code/MorphyLab/support/add-row.png"));
    bNewTax->setToolTip("Add taxa");

    taxonButtonLayout->addWidget(bDelete);
//    connect(bNewTax, &QPushButton::clicked, this, &MainWindow::doDeletion);
    bDelete->setIcon(QIcon("/Users/mbrazeau/Code/MorphyLab/support/delete.png"));
    bDelete->setToolTip("Delete selection");

    taxonButtonLayout->addWidget(bMerge);
    bMerge->setIcon(QIcon("/Users/mbrazeau/Code/MorphyLab/support/merge.png"));
    taxonButtonLayout->addWidget(bDiff);
    bDiff->setIcon(QIcon("/Users/mbrazeau/Code/MorphyLab/support/compare.png"));
    taxonButtonLayout->addWidget(bInfo);
    bInfo->setIcon(QIcon("/Users/mbrazeau/Code/MorphyLab/support/info.png"));
    taxonButtonLayout->addStretch();
}

void MainWindow::addCharacters()
{
    bool ok = true;
    int newchars = QInputDialog::getInt(this, tr("Add character columns"), tr("Enter a number of characters"), 1, QLineEdit::Normal);

    assert(dataModel->columnCount() != 0);
    dataModel->insertColumns(dataModel->columnCount()-1, newchars);  // TODO: REPLACE WITH AN NTAX GETTER!!!
    initDataTableDisplay();
}

void MainWindow::addTaxa()
{
    bool ok = true;
    int newtaxa = QInputDialog::getInt(this, tr("Add taxon rows"), tr("Enter a number of taxa"), 1, QLineEdit::Normal);

    assert(dataModel->rowCount() != 0);
    dataModel->insertRows(dataModel->rowCount(), newtaxa);  // TODO: REPLACE WITH AN NCHAR GETTER!!!
    initDataTableDisplay();
}


void MainWindow::createTableViews()
{
    matrixAreaSplitter = new QSplitter;
    scrollArea = new QScrollArea;

    matrixAreaSplitter->setHandleWidth(1);

    // Create the tables: one for taxa only and one for matrix cells
    dataModel = new PhyDataTableModel(this);

    dataTable = new QTableView(this);
    dataTable2 = new QTableView(this);
    taxonColumn = new QTableView(this);

    dataTable->setModel(dataModel);
    dataTable2->setModel(dataModel);
    taxonColumn->setModel(dataModel);

    dataTable->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
    dataTable->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
    dataTable2->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
    dataTable2->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
    taxonColumn->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);

    // C'nect the scroll bars.
    connect(dataTable->verticalScrollBar(), &QAbstractSlider::valueChanged,
            dataTable2->verticalScrollBar(), &QAbstractSlider::setValue);
    connect(dataTable2->verticalScrollBar(), &QAbstractSlider::valueChanged,
            taxonColumn->verticalScrollBar(), &QAbstractSlider::setValue);
    connect(taxonColumn->verticalScrollBar(), &QAbstractSlider::valueChanged,
            dataTable->verticalScrollBar(), &QAbstractSlider::setValue);

    // TODO: This is working poorly and needs fixing
    // This part controls the propagation of selections from one table to all others
    /*
     * Review QItemSelectionModel Class
     * Review QTableView::setSelectionModel
    */
    QObject::connect(taxonColumn->selectionModel(), &QItemSelectionModel::currentRowChanged,
                         [this](const QModelIndex &current, const QModelIndex & previous)
        {
            if(previous.isValid()) {
                dataTable->clearSelection();
                dataTable2->clearSelection();
                dataTable->selectRow(current.row());
                dataTable2->selectRow(current.row());
            }
        });
    QObject::connect(dataTable->selectionModel(), &QItemSelectionModel::currentColumnChanged,
                         [this](const QModelIndex &current, const QModelIndex & previous)
        {
            if(previous.isValid()) {
                taxonColumn->clearSelection();
                dataTable2->clearSelection();
                dataTable2->selectColumn(current.column());
            }
        });

    QObject::connect(dataTable2->selectionModel(), &QItemSelectionModel::currentColumnChanged,
                         [this](const QModelIndex &current, const QModelIndex & previous)
        {
            if(previous.isValid()) {
                dataTable->clearSelection();
                taxonColumn->clearSelection();
                dataTable->selectColumn(current.column());
            }
        });

    QObject::connect(taxonColumn->selectionModel(), &QItemSelectionModel::currentColumnChanged,
                         [this](const QModelIndex &current, const QModelIndex & previous)
        {
            if(previous.isValid()) {
                dataTable->clearSelection();
                dataTable2->clearSelection();
            }
        });

    dataTable->horizontalHeader()->setSectionsMovable(true);
    dataTable->horizontalHeader()->setDragEnabled(true);
    dataTable->setDragDropMode(QAbstractItemView::InternalMove);

    taxonColumn->verticalHeader()->setSectionsMovable(true);
    taxonColumn->verticalHeader()->setDragEnabled(true);
    taxonColumn->setDragDropMode(QAbstractItemView::InternalMove);

    mainLayout->addLayout(taxonButtonLayout);
    matrixAreaSplitter->addWidget(taxonColumn);
    matrixAreaSplitter->addWidget(dataTable);
    matrixAreaSplitter->addWidget(dataTable2);

    mainLayout->addWidget(matrixAreaSplitter);

    //
    dataTable->verticalHeader()->hide();
    dataTable2->verticalHeader()->hide();
    dataTable->hideColumn(0);
    dataTable2->hideColumn(0);
    taxonColumn->setMaximumWidth(taxonColumn->columnWidth(0));

    taxonColumn->setStyleSheet(styleSheet);
    dataTable->setStyleSheet(styleSheet);
    dataTable2->setStyleSheet(styleSheet);
}


void MainWindow::fileOpen()
{
    // TODO: put in a check and a dialog for when a file is already open
    // Alternatively: deactivate ("ghost") File > Open... when a file is already open

    if (dataModel) {
        showMessage(tr("A ddataset is already open. To open another one, save and close the current file"));
        return;
    }

    QString filename;
    filename = fopen.getOpenFileName();

    if(filename.isEmpty()) {
        return;
    }

    QByteArray qbfilename = filename.toLocal8Bit();
    char* cfilename = qbfilename.data();

    launchTableDisplay();

    reader->openNexusFile(cfilename);

    dataModel->setDimensions(reader->getNtax(), reader->getNchar());

    QString *name;
    QString *celldata;

    dataModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Taxon"));  // <<<<<<<<<<<<<<<<<<<<<<<<<<<< TODO: Make this not needed

    for (unsigned int i = 0; i < reader->getNtax(); ++i ) {

        QModelIndex index = dataModel->index(i, 0, QModelIndex());
        name = new QString(reader->getTaxLabel(i));
        dataModel->setData(index, *name);

        for (unsigned int j = 0; j < reader->getNchar(); ++j) {
            QModelIndex index = dataModel->index(i, j+1, QModelIndex());
            celldata = new QString(reader->getCellData(i, j));
            dataModel->setData(index, *celldata);
        }
    }

    initDataTableDisplay();
}

void MainWindow::save()
{
    QString filename = fopen.getSaveFileName();
    QVector<QString> names;

    if (filename.isEmpty()) {
        return;
    }

    QFile fSave(filename);
    if (!fSave.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
        fSave.errorString());
        return;
    }

    // TODO: Deal with spaces in names
    QTextStream out(&fSave);
    out << QString("#NEXUS\n\n");
    out << QString("BEGIN TAXA;\n");
    out << QString("    DIMENSIONS NTAX=%1;\n").arg(dataModel->rowCount());
    out << QString("    TAXLABELS\n");
    for (int i = 0; i < dataModel->rowCount(); ++i) {
        out << QString("    ");
        QModelIndex idx = dataModel->index(i, 0);
//        dataModel->data(idx, Qt::DisplayRole);
        QString taxLabel = dataModel->data(idx, Qt::DisplayRole).toString();
        if (taxLabel.contains(" ", Qt::CaseInsensitive)) {
            taxLabel.insert(0, '\'');
            taxLabel.append("\'");
        }
        names.push_back(taxLabel);
        out << taxLabel;
        out << QString("\n");
    }
    out << QString("    ;\n");
    out << QString("END;\n\n");
    out << QString("BEGIN CHARACTERS;\n");
    out << QString("    DIMENSIONS NCHAR=%1;\n").arg(dataModel->columnCount()-1); // TODO: Write an NCHAR getter!
    out << QString("    FORMAT DATATYPE=%1 ").arg("STANDARD"); // TODO: Obviously can accommodate more datatypes.
    out << QString("GAP=%1 ").arg("-");
    out << QString("MISSING=%1 ").arg("?");
    out << QString("SYMBOLS=%1").arg("\"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\""); // TODO: Replace this with a getter for the symbols
    out << QString(";");
    // Loop out the symbols

    out << QString("\n");
    out << QString("    MATRIX\n");
    for (int i = 0; i < dataModel->rowCount(); ++i) {
        out << QString("    ");
        out << names[i];
        out << "    ";
        for (int j = 1; j < dataModel->columnCount(); ++j) {
            QModelIndex idx = dataModel->index(i, j);
            out << QString(dataModel->data(idx, PhyDataTableModel::NexusOutputRole).toString());
        }
        out << QString("\n");
    }

    out << QString("    ;\n");
    out << QString("END;\n");
}

void MainWindow::fileNew()
{
    if (dataModel) {
        showMessage(tr("A ddataset is already open. To open another one, save and close the current file"));
        return;
    }

    int taxcount = 1;
    int charcount = 1;

    taxcount = QInputDialog::getInt(this, tr("Add taxon rows"), tr("Enter a number of taxa"), 1, QLineEdit::Normal);
    charcount = QInputDialog::getInt(this, tr("Add character columns"), tr("Enter a number of characters"), 3, QLineEdit::Normal);

    launchTableDisplay();

    dataModel->setDimensions(taxcount, charcount);
    dataModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Taxon"));

    for (unsigned int i = 0; i < 3; ++i ) {

        QModelIndex index = dataModel->index(i, 0, QModelIndex());
        dataModel->setData(index,  QString("Taxon_%1").arg(i+1));

        for (unsigned int j = 1; j < 2; ++j) {
            QModelIndex index = dataModel->index(i, j, QModelIndex());
            dataModel->setData(index, QString("?"));
        }
    }

    initDataTableDisplay();
}

void MainWindow::fileImport()
{
    showMessage("Feature not yet implemented.\n Note: This will replace file open for Nexus file in the future.\n");
}

void MainWindow::fileExport()
{
    showMessage("Feature not yet implemented.");
}

void MainWindow::aboutMenu()
{
    QString about =

    "This program is written by Martin D. Brazeau."
    "\n\n"
    "This program uses the Nexus Class Library by Mark Holder and Paul O. Lewis.";

    showMessage(about);
}

void MainWindow::initDataTableDisplay()
{
    for (int i = 1; i < dataModel->columnCount(); ++i) {
        dataModel->setHeaderData(i, Qt::Horizontal, QString::number(i));
        dataTable->setColumnWidth(i, 35);
        dataTable2->setColumnWidth(i, 35);
        taxonColumn->hideColumn(i);
    }

    taxonColumn->resizeColumnToContents(0);
    taxonColumn->setMaximumWidth(taxonColumn->columnWidth(0) + taxonColumn->verticalHeader()->width());
    dataTable->hideColumn(0);
    dataTable2->hideColumn(0);
    matrixAreaSplitter->setSizes(QList<int>() << taxonColumn->columnWidth(0) + taxonColumn->verticalHeader()->width() + taxonColumn->verticalScrollBar()->width()
                                 << dataTable->width()
                                 << 0);
}

void MainWindow::launchTableDisplay()
{
    createMainWindow();
    showMaximized();
}

void MainWindow::showMessage(QString message)
{
    QMessageBox mb(this);
    mb.setText(message);

    mb.setStandardButtons(QMessageBox::Ok);
    mb.exec();
}
