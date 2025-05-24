/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QToolButton *userButton;
    QToolButton *queryButton;
    QToolButton *learnButton;
    QToolButton *reviewButton;
    QToolButton *achievementButton;
    QToolButton *gameButton;
    QToolButton *exitButton;
    QStackedWidget *stackedWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        userButton = new QToolButton(centralwidget);
        userButton->setObjectName("userButton");
        userButton->setGeometry(QRect(20, 40, 71, 61));
        queryButton = new QToolButton(centralwidget);
        queryButton->setObjectName("queryButton");
        queryButton->setGeometry(QRect(20, 170, 71, 41));
        learnButton = new QToolButton(centralwidget);
        learnButton->setObjectName("learnButton");
        learnButton->setGeometry(QRect(20, 220, 71, 41));
        reviewButton = new QToolButton(centralwidget);
        reviewButton->setObjectName("reviewButton");
        reviewButton->setGeometry(QRect(20, 270, 71, 41));
        achievementButton = new QToolButton(centralwidget);
        achievementButton->setObjectName("achievementButton");
        achievementButton->setGeometry(QRect(20, 320, 71, 41));
        gameButton = new QToolButton(centralwidget);
        gameButton->setObjectName("gameButton");
        gameButton->setGeometry(QRect(20, 370, 71, 41));
        exitButton = new QToolButton(centralwidget);
        exitButton->setObjectName("exitButton");
        exitButton->setGeometry(QRect(20, 490, 71, 31));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(130, 40, 600, 500));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setTabletTracking(false);
        MainWindow->setStatusBar(statusbar);
        QWidget::setTabOrder(userButton, queryButton);
        QWidget::setTabOrder(queryButton, learnButton);
        QWidget::setTabOrder(learnButton, reviewButton);
        QWidget::setTabOrder(reviewButton, achievementButton);
        QWidget::setTabOrder(achievementButton, gameButton);
        QWidget::setTabOrder(gameButton, exitButton);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        userButton->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267", nullptr));
        queryButton->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242", nullptr));
        learnButton->setText(QCoreApplication::translate("MainWindow", "\345\255\246\344\271\240", nullptr));
        reviewButton->setText(QCoreApplication::translate("MainWindow", "\345\244\215\344\271\240", nullptr));
        achievementButton->setText(QCoreApplication::translate("MainWindow", "\346\210\220\345\260\261", nullptr));
        gameButton->setText(QCoreApplication::translate("MainWindow", "\346\270\270\346\210\217", nullptr));
        exitButton->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
