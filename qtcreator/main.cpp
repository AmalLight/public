#include "mainwindow.h"
#include <QApplication>
#include <stdlib.h>
#include <time.h>

#include <mylistQStringMaps.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    srand (time(nullptr));
    w.show();
    w.prima_fase();

    return a.exec();
}
