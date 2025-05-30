#include "mainwindow.h"
#include "loginwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    loginWidget l;
    l.show();
    return a.exec();
}
