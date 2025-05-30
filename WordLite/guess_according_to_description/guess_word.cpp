#include "../guess_according_to_description_h/guess_word.h"
#include <QDebug>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

guess_word::guess_word()
{
    pythonprocess = new QProcess();
}

map<QString,QString> guess_word::processingPython()
{

    // 设置参数（作为命令行参数传递）
    QStringList arguments;
    map<QString,QString> result;
    arguments << "--database" << "1";  // 直接作为命令行参数

    // 启动Python脚本
    pythonprocess->start("python3", QStringList() << "../../python_reasoner/python_reasoner.py" << arguments);

    if (!pythonprocess->waitForStarted()) {
        qDebug() << "Failed to start Python process:" << pythonprocess->errorString();
        return result;
    }

    // 等待脚本完成（设置超时时间）
    if (!pythonprocess->waitForFinished(30000)) {  // 30秒超时
        qDebug() << "Python process timed out or failed:" << pythonprocess->errorString();
        return result;
    }

    // 检查退出状态
    if (pythonprocess->exitStatus() != QProcess::NormalExit) {
        qDebug() << "Python process crashed";
        return result;
    }

    // 获取输出
    QByteArray output = pythonprocess->readAllStandardOutput();
    QByteArray error = pythonprocess->readAllStandardError();

    if (!error.isEmpty()) {
        qDebug() << "Python error output:" << error;
    }

    if (!output.isEmpty()) {

        // 尝试解析JSON
        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(output, &parseError);

        if (parseError.error != QJsonParseError::NoError) {
            qDebug() << "JSON parse error:" << parseError.errorString();
            qDebug() << "Raw output:" << output;
        } else if (jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();
            qDebug() << "Word:" << jsonObj["word"].toString();
            qDebug() << "Description:" << jsonObj["description"].toString();
            qDebug() << "Translation:" << jsonObj["translation"].toString();
            result["word"]=jsonObj["word"].toString();
            result["description"]=jsonObj["description"].toString();
            result["translation"]=jsonObj["translation"].toString();
        }
    } else {
        qDebug() << "No output from Python script";
    }
    return result;
}
