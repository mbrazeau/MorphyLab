TEMPLATE = app
TARGET = MorphyLab

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    CellData.cpp \
    MainLayout.cpp \
    MainWindow.cpp \
    MorphyLabNexusReader.cpp \
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
    abstractphydata.h \
    chardata.h \
    charinfodialog.h \
    phydatatablemodel.h \
    statedata.h \
    taxondata.h \
    toolbutton.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/ncl/release/ -lncl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/ncl/debug/ -lncl
else:unix: LIBS += -L$$PWD/../../../../usr/local/lib/ncl/ -lncl

INCLUDEPATH += $$PWD/../../../../usr/local/include/ncl
INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include/ncl

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/ncl/release/libncl.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/ncl/debug/libncl.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/ncl/release/ncl.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/ncl/debug/ncl.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/ncl/libncl.a
