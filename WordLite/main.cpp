#include "mainwindow.h"
#include "loginwidget.h"

#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString qss;
    QFile file(":/QSS/AMOLED.qss");
    file.open(QFile::ReadOnly);
    qss=file.readAll();
    file.close();
    a.setStyleSheet(qss);
    // MainWindow w;
    // w.show();
    loginWidget l;
    l.show();
    return a.exec();
}
