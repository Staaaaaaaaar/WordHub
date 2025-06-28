#include "guess_word.h" // 正确包含头文件

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QProcess>

// 构造函数实现
guess_word::guess_word(QObject *parent) : QObject(parent)
{
    // 构造函数可以为空
}

// 析构函数实现
guess_word::~guess_word()
{
    // 析构函数可以为空
}

// processingPython 函数实现
std::map<QString, QString> guess_word::processingPython()
{
    std::map<QString, QString> result;
    QProcess pythonProcess; // 将 QProcess 作为局部变量，自动管理内存

    // 获取应用程序所在目录
    QDir appDir(QCoreApplication::applicationDirPath());

    // 设置参数
    QStringList arguments;
    arguments << appDir.absoluteFilePath("codes/python_reasoner.py"); // 脚本作为第一个参数
    arguments << "--database"
              << "1";

    // 启动Python解释器
    QString pythonInterpreter = appDir.absoluteFilePath("codes/python/python.exe");

    // 设置工作目录
    pythonProcess.setWorkingDirectory(appDir.path());

    // 启动Python脚本
    pythonProcess.start(pythonInterpreter, arguments);

    // 等待脚本完成（设置超时时间）
    if (!pythonProcess.waitForFinished(30000))
    { // 30秒超时
        qDebug() << "Python process timed out or failed:" << pythonProcess.errorString();
        pythonProcess.kill(); // 超时后强制结束进程
        result["error"] = "Process timed out";
        return result;
    }

    // 检查退出状态
    if (pythonProcess.exitStatus() != QProcess::NormalExit || pythonProcess.exitCode() != 0)
    {
        qDebug() << "Python process crashed or returned an error. Exit code:" << pythonProcess.exitCode();
        QByteArray error = pythonProcess.readAllStandardError();
        qDebug() << "Python error output:" << error;
        result["error"] = "Process crashed: " + QString(error);
        return result;
    }

    // 获取输出
    QByteArray output = pythonProcess.readAllStandardOutput();

    if (output.isEmpty())
    {
        qDebug() << "No output from Python script";
        result["error"] = "No output from script";
        return result;
    }

    // 尝试解析JSON
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(output, &parseError);

    if (parseError.error != QJsonParseError::NoError)
    {
        qDebug() << "JSON parse error:" << parseError.errorString();
        qDebug() << "Raw output:" << output;
        result["error"] = "JSON parse error";
    }
    else if (jsonDoc.isObject())
    {
        QJsonObject jsonObj = jsonDoc.object();
        if (jsonObj["status"].toString() == "success")
        {
            result["word"] = jsonObj["word"].toString();
            result["description"] = jsonObj["description"].toString();
            result["translation"] = jsonObj["translation"].toString();
        }
        else
        {
            QString errorMessage = jsonObj["message"].toString();
            qDebug() << "Python script returned an error:" << errorMessage;
            result["error"] = "Script error: " + errorMessage;
        }
    }
    return result;
}
