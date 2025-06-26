#include "mainwindow.h"
#include "loginwidget.h"
#include "darktheme_win.h" // <-- 包含我们新的头文件

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

    loginWidget l;
    l.show();

    // 调用我们新的辅助函数
    setDarkTitleBar(l.winId());

    return a.exec();
}
