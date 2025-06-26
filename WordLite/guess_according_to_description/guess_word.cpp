//#include "../guess_according_to_description_h/guess_word.h"
#include <QDebug>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QCoreApplication>
#include <QEventLoop> // 新增

#include <QProcess>
#include <map>
using namespace std;

class guess_word : public QObject // 继承 QObject 以使用信号槽
{
    Q_OBJECT // Q_OBJECT 宏

public:
    guess_word(QObject *parent = nullptr); // 构造函数
    map<QString,QString> processingPython();

signals:
    void processingFinished(const map<QString, QString>& result); // 定义一个完成信号
    void processingFailed(const QString& errorString); // 定义一个失败信号
};

guess_word::guess_word(QObject *parent) : QObject(parent) // 实现构造函数
{
    // 构造函数现在为空
}

map<QString,QString> guess_word::processingPython()
{
    map<QString, QString> result;
    QProcess pythonProcess; // 将 QProcess 作为局部变量，自动管理内存

    // 获取应用程序所在目录
    QDir appDir(QCoreApplication::applicationDirPath());
    
    // 设置参数
    QStringList arguments;
    arguments << appDir.absoluteFilePath("codes/python_reasoner.py"); // 脚本作为第一个参数
    arguments << "--database" << "1";
    
    // 启动Python解释器
    QString pythonInterpreter = appDir.absoluteFilePath("codes/python/python.exe");
    
    // 设置工作目录
    pythonProcess.setWorkingDirectory(appDir.path());
    
    // 启动Python脚本
    pythonProcess.start(pythonInterpreter, arguments);

    // 等待脚本完成（设置超时时间）
    if (!pythonProcess.waitForFinished(30000)) {  // 30秒超时
        qDebug() << "Python process timed out or failed:" << pythonProcess.errorString();
        pythonProcess.kill(); // 超时后强制结束进程
        result["error"] = "Process timed out";
        return result;
    }

    // 检查退出状态
    if (pythonProcess.exitStatus() != QProcess::NormalExit || pythonProcess.exitCode() != 0) {
        qDebug() << "Python process crashed or returned an error. Exit code:" << pythonProcess.exitCode();
        QByteArray error = pythonProcess.readAllStandardError();
        qDebug() << "Python error output:" << error;
        result["error"] = "Process crashed: " + QString(error);
        return result;
    }

    // 获取输出
    QByteArray output = pythonProcess.readAllStandardOutput();

    if (output.isEmpty()) {
        qDebug() << "No output from Python script";
        result["error"] = "No output from script";
        return result;
    }

    // 尝试解析JSON
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(output, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "JSON parse error:" << parseError.errorString();
        qDebug() << "Raw output:" << output;
        result["error"] = "JSON parse error";
    } else if (jsonDoc.isObject()) {
        QJsonObject jsonObj = jsonDoc.object();
        if (jsonObj["status"].toString() == "success") {
            result["word"] = jsonObj["word"].toString();
            result["description"] = jsonObj["description"].toString();
            result["translation"] = jsonObj["translation"].toString();
        } else {
            QString errorMessage = jsonObj["message"].toString();
            qDebug() << "Python script returned an error:" << errorMessage;
            result["error"] = "Script error: " + errorMessage;
        }
    }
    return result;
}
