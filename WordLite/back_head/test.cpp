#include <QCoreApplication>
#include<QString>
#include<QDir>
#include<QDebug>
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
        qInfo()<<p;
    }

    qInfo()<<"________________________1__________________________";
    qInfo()<<db1.getCategoryById(1).name<<"\n";
    for(auto p:db1.getWordsByCategory(1))
    {
        qInfo()<<p;
    }

    qInfo()<<"_______________________2___________________________";
    qInfo()<<db1.getCategoryById(2).name<<"\n";
    for(auto p:db1.getWordsByCategory(2))
    {
        qInfo()<<p;
    }

    qInfo()<<"_______________________3___________________________";
    qInfo()<<db1.getCategoryById(3).name<<"\n";
    for(auto p:db1.getWordsByCategory(3))
    {
        qInfo()<<p;
    }

    db1.deleteWord(6);
    qInfo()<<"word id=2 is deleted\n";

    qInfo()<<db1.getWordById(4);

    db1.removeWordFromCategory(1,1);
    qInfo()<<"________________________1__________________________";
    qInfo()<<db1.getCategoryById(1).name<<"\n";
    for(auto p:db1.getWordsByCategory(1))
    {
        qInfo()<<p;
    }

    qInfo()<<"_______________________2___________________________";
    qInfo()<<db1.getCategoryById(2).name<<"\n";
    for(auto p:db1.getWordsByCategory(2))
    {
        qInfo()<<p;
    }

    qInfo()<<"_______________________3___________________________";
    qInfo()<<db1.getCategoryById(3).name<<"\n";
    for(auto p:db1.getWordsByCategory(3))
    {
        qInfo()<<p;
    }




    return 0;
}
