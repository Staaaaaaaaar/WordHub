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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label;
    QWidget *page_2;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QWidget *page_3;
    QStackedWidget *stackedWidget_2;
    QWidget *page_7;
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QLabel *label_3;
    QWidget *page_8;
    QLabel *label_7;
    QToolButton *toolButton_3;
    QWidget *page_9;
    QLabel *label_8;
    QToolButton *toolButton_4;
    QWidget *page_4;
    QLabel *label_4;
    QWidget *page_5;
    QLabel *label_5;
    QWidget *page_6;
    QLabel *label_6;
    QToolButton *btn_user;
    QToolButton *btn_query;
    QToolButton *btn_learn;
    QToolButton *btn_review;
    QToolButton *btn_achievement;
    QToolButton *btn_game;
    QToolButton *btn_exit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(180, 50, 411, 361));
        page = new QWidget();
        page->setObjectName("page");
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 10, 40, 12));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        label_2 = new QLabel(page_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 10, 40, 12));
        lineEdit = new QLineEdit(page_2);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(40, 40, 113, 20));
        tabWidget = new QTabWidget(page_2);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(40, 70, 331, 251));
        tab = new QWidget();
        tab->setObjectName("tab");
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tabWidget->addTab(tab_2, QString());
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        stackedWidget_2 = new QStackedWidget(page_3);
        stackedWidget_2->setObjectName("stackedWidget_2");
        stackedWidget_2->setGeometry(QRect(30, 30, 361, 311));
        page_7 = new QWidget();
        page_7->setObjectName("page_7");
        toolButton = new QToolButton(page_7);
        toolButton->setObjectName("toolButton");
        toolButton->setGeometry(QRect(20, 20, 51, 71));
        toolButton_2 = new QToolButton(page_7);
        toolButton_2->setObjectName("toolButton_2");
        toolButton_2->setGeometry(QRect(80, 20, 51, 71));
        label_3 = new QLabel(page_7);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 0, 40, 12));
        stackedWidget_2->addWidget(page_7);
        page_8 = new QWidget();
        page_8->setObjectName("page_8");
        label_7 = new QLabel(page_8);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(40, 30, 191, 31));
        toolButton_3 = new QToolButton(page_8);
        toolButton_3->setObjectName("toolButton_3");
        toolButton_3->setGeometry(QRect(300, 250, 41, 31));
        stackedWidget_2->addWidget(page_8);
        page_9 = new QWidget();
        page_9->setObjectName("page_9");
        label_8 = new QLabel(page_9);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(80, 60, 151, 41));
        toolButton_4 = new QToolButton(page_9);
        toolButton_4->setObjectName("toolButton_4");
        toolButton_4->setGeometry(QRect(290, 278, 41, 21));
        stackedWidget_2->addWidget(page_9);
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        label_4 = new QLabel(page_4);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(40, 30, 40, 12));
        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        label_5 = new QLabel(page_5);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(40, 30, 40, 12));
        stackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        label_6 = new QLabel(page_6);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(40, 10, 41, 21));
        stackedWidget->addWidget(page_6);
        btn_user = new QToolButton(centralwidget);
        btn_user->setObjectName("btn_user");
        btn_user->setGeometry(QRect(20, 40, 80, 18));
        btn_query = new QToolButton(centralwidget);
        btn_query->setObjectName("btn_query");
        btn_query->setGeometry(QRect(20, 170, 80, 18));
        btn_learn = new QToolButton(centralwidget);
        btn_learn->setObjectName("btn_learn");
        btn_learn->setGeometry(QRect(20, 210, 80, 18));
        btn_review = new QToolButton(centralwidget);
        btn_review->setObjectName("btn_review");
        btn_review->setGeometry(QRect(20, 240, 80, 18));
        btn_achievement = new QToolButton(centralwidget);
        btn_achievement->setObjectName("btn_achievement");
        btn_achievement->setGeometry(QRect(20, 280, 80, 18));
        btn_game = new QToolButton(centralwidget);
        btn_game->setObjectName("btn_game");
        btn_game->setGeometry(QRect(20, 310, 80, 18));
        btn_exit = new QToolButton(centralwidget);
        btn_exit->setObjectName("btn_exit");
        btn_exit->setGeometry(QRect(20, 410, 80, 18));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setTabletTracking(false);
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(5);
        tabWidget->setCurrentIndex(1);
        stackedWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "user", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "query", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "\345\215\225\350\257\2151", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\345\215\225\350\257\2152", nullptr));
        toolButton->setText(QCoreApplication::translate("MainWindow", "\350\257\215\345\272\2231", nullptr));
        toolButton_2->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "learn", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\350\257\215\345\272\223\345\210\235\345\247\213\347\225\214\351\235\242\357\274\214\351\234\200\350\246\201\345\210\251\347\224\250\350\257\215\345\272\223\346\225\260\346\215\256\345\210\235\345\247\213\345\214\226", nullptr));
        toolButton_3->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\350\277\233\344\270\200\346\255\245\347\232\204\357\274\214\347\273\203\344\271\240/\345\255\246\344\271\240\347\225\214\351\235\242", nullptr));
        toolButton_4->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "review", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "ach", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "game", nullptr));
        btn_user->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267", nullptr));
        btn_query->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242", nullptr));
        btn_learn->setText(QCoreApplication::translate("MainWindow", "\345\255\246\344\271\240", nullptr));
        btn_review->setText(QCoreApplication::translate("MainWindow", "\345\244\215\344\271\240", nullptr));
        btn_achievement->setText(QCoreApplication::translate("MainWindow", "\346\210\220\345\260\261", nullptr));
        btn_game->setText(QCoreApplication::translate("MainWindow", "\346\270\270\346\210\217", nullptr));
        btn_exit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
