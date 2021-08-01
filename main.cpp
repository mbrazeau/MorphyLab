#include <QApplication>
#include <QScreen>

#include "MainWindow.h"

int main(int argc, char **argv)
{
    QApplication            MorphyLab(argc, argv);
    MainWindow              mw;

    QRect s = MorphyLab.primaryScreen()->geometry();
    mw.move(s.left(), s.top());
    mw.show();
    return MorphyLab.exec();
}
