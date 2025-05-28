#include "../guess_according_to_description_h/guess_word.h"
#include <QProcess>
#include <QDebug>

guess_word::guess_word()
{
    pythonprocess = new QProcess();
}

void guess_word::processingPython()
{
    // 获取用户输入的数据
    QString inputData="1";

    // 启动Python脚本
    pythonprocess->start("python3", QStringList() << "../python_reasoner/python_reasoner.py");

    if (pythonprocess->waitForStarted())
    {
        // 向Python脚本发送数据
        pythonprocess->write(inputData.toUtf8() + '\n');
        pythonprocess->closeWriteChannel();
    }
    else
    {
        qDebug() << "Failed to start Python process.";
    }

    QByteArray output = pythonprocess->readAllStandardOutput();
    QString result = QString::fromUtf8(output);
    qDebug()<<result;
}
