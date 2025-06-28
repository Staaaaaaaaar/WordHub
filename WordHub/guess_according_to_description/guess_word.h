#ifndef GUESS_WORD_H
#define GUESS_WORD_H

#include <QObject>
#include <map>
#include <QString>

class guess_word : public QObject
{
    Q_OBJECT

public:
    explicit guess_word(QObject *parent = nullptr);
    ~guess_word(); // 添加析构函数声明

    std::map<QString, QString> processingPython();

signals:
    void processingFinished(const std::map<QString, QString>& result);
    void processingFailed(const QString& errorString);
};

#endif // GUESS_WORD_H