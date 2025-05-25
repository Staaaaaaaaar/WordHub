#include <QCoreApplication>
#include<QString>
#include<QDir>
#include "database.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 确保数据目录存在
    QString dataDir = QCoreApplication::applicationDirPath() + "/datas";
    QDir dir(dataDir);
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qFatal("无法创建数据目录!");
            return 1;
        }
    }

    QString lib="myfaverator";
    WordDatabase db1(lib);
    QString dbPath1 = QCoreApplication::applicationDirPath() +"/datas/"+ lib +".db";
    if (!db1.initDatabase(dbPath1)) {
        qFatal("数据库初始化失败!");
        return 1;
    }

    // 测试添加单词
    Word word;
    word.word = "abcd";
    word.meaning = "whatcanisay";
    if (db1.addWord(word)) {
        qInfo() << "单词添加成功";
    } else {
        qWarning() << "单词添加失败";
    }

    for(auto p:db1.getAllWords())
    {
        qInfo()<<p.word;
        qInfo()<<p.meaning;
        qInfo()<<p.pronunciation;
    }


    qInfo()<<"____________________________________________________";

    WordDatabase db2("bad");
    QString dbPath2 = QCoreApplication::applicationDirPath()  +"/datas/"+"bad" +".db";
    if (!db2.initDatabase(dbPath2)) {
        qFatal("数据库初始化失败!");
        return 1;
    }
    Word word2;
    word2.word = "abcd";
    word2.meaning = "调试";
    if (db2.addWord(word2)) {
        qInfo() << "单词添加成功";
    } else {
        qWarning() << "单词添加失败";
    }

    for(auto p:db2.getAllWords())
    {
        qInfo()<<p.word;
        qInfo()<<p.meaning;
        qInfo()<<p.pronunciation;
    }

    return 0;
}
