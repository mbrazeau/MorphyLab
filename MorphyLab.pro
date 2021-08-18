TEMPLATE = app
TARGET = MorphyLab

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += qt \
    warn_on

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.14

SOURCES += \
    CellData.cpp \
    MainLayout.cpp \
    MainWindow.cpp \
    MorphyLabNexusReader.cpp \
    StateDataTable.cpp \
    abstractphydata.cpp \
    characterlistmodel.cpp \
    chardata.cpp \
    charinfodialog.cpp \
    charinfowidget.cpp \
    datatable.cpp \
    main.cpp \
    phydatatablemodel.cpp \
    statedata.cpp \
    stateinfowidget.cpp \
    taxoncolumn.cpp \
    taxondata.cpp \
    toolbutton.cpp

HEADERS += \
    CellData.h \
    MainLayout.h \
    MainWindow.h \
    MorphyLabNexusReader.h \
    StateDataTable.h \
    abstractphydata.h \
    characterlistmodel.h \
    chardata.h \
    charinfodialog.h \
    charinfowidget.h \
    datatable.h \
    phydatatablemodel.h \
    statedata.h \
    stateinfowidget.h \
    taxoncolumn.h \
    taxondata.h \
    toolbutton.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/external/ncl/build/ncl/release/ -lncl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/external/ncl/build/ncl/debug/ -lncl
else:unix: LIBS += -L$$PWD/external/ncl/build/ncl/ -lncl

INCLUDEPATH += $$PWD/external/ncl/ncl
INCLUDEPATH += $$PWD/external/ncl
DEPENDPATH += $$PWD/external/ncl/ncl

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/external/ncl/build/ncl/release/libncl.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/external/ncl/build/ncl/debug/libncl.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/external/ncl/build/ncl/release/ncl.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/external/ncl/build/ncl/debug/ncl.lib
else:unix: PRE_TARGETDEPS += $$PWD/external/ncl/build/ncl/libncl.a

RESOURCES += \
    morphylab.qrc
