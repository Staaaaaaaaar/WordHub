#include <QCoreApplication>
#include "./back_head/learner.h"
#include <QFileInfo>
#include <QDebug>

void printUserInfo(const Learner& learner, const QString& prefix = "")
{
    qDebug() << prefix << "用户名:" << learner.getName();
    qDebug() << prefix << "头像路径:" << learner.getHeadImagePath();
    qDebug() << prefix << "开始学习时间:" << learner.getStartTime().toString(Qt::ISODate);
    qDebug() << prefix << "已学习总数:" << learner.getTotalLearned();
    qDebug() << prefix << "是否登录:" << (learner.isUserLoggedIn() ? "是" : "否");
    qDebug() << "----------------------------------------";
}

bool verifyDatabaseExists()
{
    QString dbPath = QCoreApplication::applicationDirPath() + "/User/user_data.sqlite";
    QFileInfo fileInfo(dbPath);
    bool exists = fileInfo.exists() && fileInfo.isFile();
    qDebug() << "数据库文件检查:" << dbPath << (exists ? "存在" : "不存在");
    
    // 如果文件存在，打印文件大小
    if (exists) {
        qDebug() << "数据库文件大小:" << fileInfo.size() << "字节";
    }
    
    return exists;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    qDebug() << "===== 开始测试 Learner 类 =====";
    qDebug() << "应用程序目录:" << QCoreApplication::applicationDirPath();
    qDebug() << "预期数据库路径:" << QCoreApplication::applicationDirPath() + "/User/user_data.sqlite";
    
    // 测试1: 初始化 - 应该创建Guest用户
    qDebug() << "\n测试1: 初始化 Learner 类";
    {
        qDebug() << "创建第一个Learner实例";
        Learner learner;
        printUserInfo(learner, "初始状态:");
        
        // 验证数据库是否创建
        verifyDatabaseExists();
    }
    
    // 测试2: 创建新用户
    qDebug() << "\n测试2: 创建新用户";
    {
        qDebug() << "创建第二个Learner实例";
        Learner learner;
        bool createResult = learner.createNewUser("测试用户", "password123");
        qDebug() << "创建用户结果:" << (createResult ? "成功" : "失败");
        printUserInfo(learner, "创建用户后:");
        
        // 验证数据库是否创建
        verifyDatabaseExists();
    }
    
    // 测试3: 修改用户信息
    qDebug() << "\n测试3: 修改用户信息";
    {
        qDebug() << "创建第三个Learner实例";
        Learner learner;
        learner.setName("修改后的用户名");
        learner.setHeadImagePath(":/images/new_avatar.png");
        learner.setTotalLearned(50);
        printUserInfo(learner, "修改后:");
        
        // 验证数据库是否创建
        verifyDatabaseExists();
    }
    
    // 测试4: 验证密码
    qDebug() << "\n测试4: 验证密码";
    {
        qDebug() << "创建第四个Learner实例";
        Learner learner;
        qDebug() << "正确密码验证结果:" << (learner.verifyPassword("password123") ? "成功" : "失败");
        qDebug() << "错误密码验证结果:" << (learner.verifyPassword("wrong_password") ? "成功" : "失败");
        
        // 验证数据库是否创建
        verifyDatabaseExists();
    }
    
    // 测试5: 重启应用 - 验证数据持久化
    qDebug() << "\n测试5: 验证数据持久化";
    {
        qDebug() << "创建第五个Learner实例 (模拟应用重启)";
        Learner newLearner;
        printUserInfo(newLearner, "重启后加载的用户:");
        
        // 验证数据库是否创建
        verifyDatabaseExists();
    }
    
    // 测试6: 重置用户
    qDebug() << "\n测试6: 重置用户";
    {
        qDebug() << "创建第六个Learner实例";
        Learner learner;
        bool resetResult = learner.resetUser(true);
        qDebug() << "重置用户结果:" << (resetResult ? "成功" : "失败");
        printUserInfo(learner, "重置后:");
        
        // 验证数据库是否创建
        verifyDatabaseExists();
    }
    
    // 测试7: 重置后创建新用户
    qDebug() << "\n测试7: 重置后创建新用户";
    {
        qDebug() << "创建第七个Learner实例";
        Learner learner;
        bool createResult = learner.createNewUser("新用户", "new_password");
        qDebug() << "创建新用户结果:" << (createResult ? "成功" : "失败");
        printUserInfo(learner, "创建新用户后:");
        
        // 验证数据库是否创建
        verifyDatabaseExists();
    }
    
    // 测试8: 已有用户时尝试创建新用户 - 应该失败
    qDebug() << "\n测试8: 已有用户时尝试创建新用户";
    {
        qDebug() << "创建第八个Learner实例";
        Learner learner;
        bool createResult = learner.createNewUser("冲突用户", "password");
        qDebug() << "尝试创建新用户结果:" << (createResult ? "成功" : "失败");
        printUserInfo(learner, "尝试后:");
        
        // 验证数据库是否创建
        verifyDatabaseExists();
    }
    
    qDebug() << "\n===== 测试完成 =====";
    
    return 0;
}
