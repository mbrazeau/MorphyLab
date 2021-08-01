TEMPLATE = app
TARGET = MorphyLab

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    CellData.cpp \
    MainLayout.cpp \
    MainWindow.cpp \
    MorphyLabNexusReader.cpp \
    StateDataTable.cpp \
    abstractphydata.cpp \
    chardata.cpp \
    charinfodialog.cpp \
    main.cpp \
    phydatatablemodel.cpp \
    statedata.cpp \
    taxondata.cpp \
    toolbutton.cpp

HEADERS += \
    CellData.h \
    MainLayout.h \
    MainWindow.h \
    MorphyLabNexusReader.h \
    StateDataTable.h \
    abstractphydata.h \
    chardata.h \
    charinfodialog.h \
    phydatatablemodel.h \
    statedata.h \
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
