// // test_learner.cpp
// #include <QCoreApplication>
// #include <QDebug>
// #include <QDir>
// #include "../back_head/Learner.h"

// bool testSingleton()
// {
//     Learner* instance1 = Learner::getInstance();
//     Learner* instance2 = Learner::getInstance();

//     qDebug() << "[1] Singleton Test:";
//     qDebug() << "Instance1 address:" << instance1;
//     qDebug() << "Instance2 address:" << instance2;

//     bool success = (instance1 == instance2) && (instance1 != nullptr);
//     qDebug() << (success ? "✓ Passed" : "✗ Failed");
//     return success;
// }

// bool testDatabasePath()
// {
//     QString actualPath = Learner::getUserDatabasePath();
//     QString expectedPath = QCoreApplication::applicationDirPath()
//                            + "/User/learning_data.db";

//     qDebug() << "\n[2] Database Path Test:";
//     qDebug() << "Expected:" << expectedPath;
//     qDebug() << "Actual  :" << actualPath;

//     bool success = (actualPath == expectedPath);
//     qDebug() << (success ? "✓ Passed" : "✗ Failed");
//     return success;
// }

// bool testUserCreation()
// {
//     Learner* learner = Learner::getInstance();

//     qDebug() << "\n[3] User Creation Test:";
//     bool createResult = learner->createNewUser("testUser", "password123");
//     qDebug() << "Create user result:" << createResult;

//     bool verifyResult = learner->verifyPassword("password123");
//     qDebug() << "Password verification:" << verifyResult;

//     bool success = createResult && verifyResult;
//     qDebug() << (success ? "✓ Passed" : "✗ Failed");
//     return success;
// }

// void cleanupTestData()
// {
//     QString dbPath = Learner::getUserDatabasePath();
//     QFile::remove(dbPath);
//     qDebug() << "\nCleaned up test database:" << dbPath;
// }

// int main(int argc, char *argv[])
// {
//     QCoreApplication a(argc, argv);

//     // 重定向到测试目录
//     QString testDir = QCoreApplication::applicationDirPath() + "/test_data/";
//     QDir().mkpath(testDir);
//     QCoreApplication::setApplicationVersion("TEST");
//     QCoreApplication::setApplicationName("LearnerTest");
//     qputenv("QStandardPaths::AppDataLocation", testDir.toUtf8());

//     qDebug() << "=== Starting Command Line Tests ===";

//     int passed = 0;
//     passed += testSingleton();
//     passed += testDatabasePath();
//     passed += testUserCreation();

//     qDebug() << "\n=== Test Summary ===";
//     qDebug() << "Passed:" << passed << "/ 3 tests";

//     cleanupTestData();
//     return (passed == 3) ? 0 : 1;
// }

#include <QTest>
#include "../back_head/learner.h"

class LearnerTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testSingletonInstance();
    void testCreateNewUser();
    void testResetUser();
    void testVerifyPassword();
    void testSetName();
    void testSetPassword();
    void testSetHeadImagePath();
    void testIsUserLoggedIn();
};

void LearnerTest::initTestCase()
{
    // 初始化操作，例如可以在这里删除之前的测试数据库
    QDir userDir(Learner::getUserDir());
    if (userDir.exists()) {
        userDir.removeRecursively();
    }
}

void LearnerTest::cleanupTestCase()
{
    // 清理操作，例如删除测试数据库
    QDir userDir(Learner::getUserDir());
    if (userDir.exists()) {
        userDir.removeRecursively();
    }
}

void LearnerTest::testSingletonInstance()
{
    Learner* instance1 = Learner::getInstance();
    Learner* instance2 = Learner::getInstance();
    QVERIFY(instance1 == instance2);
}

void LearnerTest::testCreateNewUser()
{
    Learner* learner = Learner::getInstance();
    bool result = learner->createNewUser("testuser", "testpassword");
    QVERIFY(result);
}

void LearnerTest::testResetUser()
{
    Learner* learner = Learner::getInstance();
    bool result = learner->resetUser(true);
    QVERIFY(result);
}

void LearnerTest::testVerifyPassword()
{
    Learner* learner = Learner::getInstance();
    learner->createNewUser("testuser", "testpassword");
    bool result = learner->verifyPassword("testpassword");
    QVERIFY(result);
}

void LearnerTest::testSetName()
{
    Learner* learner = Learner::getInstance();
    learner->setName("newtestuser");
    QCOMPARE(learner->getName(), QString("newtestuser"));
}

void LearnerTest::testSetPassword()
{
    Learner* learner = Learner::getInstance();
    learner->setPassword("newtestpassword");
    bool result = learner->verifyPassword("newtestpassword");
    QVERIFY(result);
}

void LearnerTest::testSetHeadImagePath()
{
    Learner* learner = Learner::getInstance();
    QString testImagePath = "test_image.png";
    learner->setHeadImage(testImagePath);
    QVERIFY(!learner->getHeadImage().isEmpty());
}

void LearnerTest::testIsUserLoggedIn()
{
    Learner* learner = Learner::getInstance();
    // 确保用户未登录
    learner->resetUser(true);

    bool createResult = learner->createNewUser("testuser", "testpassword");
    QVERIFY(createResult);

    bool result = learner->isUserLoggedIn();
    QVERIFY(result);

    learner->resetUser(true);
    result = learner->isUserLoggedIn();
    QVERIFY(!result);
}

QTEST_MAIN(LearnerTest)
#include "learner_test.moc"
