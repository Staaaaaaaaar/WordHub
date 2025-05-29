/********************************************************************************
** Form generated from reading UI file 'learnwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEARNWIDGET_H
#define UI_LEARNWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LearnWidget
{
public:
    QStackedWidget *stackedWidget;
    QWidget *dictTable;
    QGroupBox *customizeBox;
    QWidget *gridLayoutWidget_2;
    QGridLayout *customizeLayout;
    QGroupBox *defaultBox;
    QWidget *gridLayoutWidget;
    QGridLayout *defaultLayout;
    QWidget *dictWidget;
    QLabel *label;
    QToolButton *backButton;
    QLabel *label_2;
    QToolButton *testButton;
    QLabel *label_4;
    QWidget *testWidget;
    QLabel *label_3;
    QToolButton *backButton_2;

    void setupUi(QWidget *LearnWidget)
    {
        if (LearnWidget->objectName().isEmpty())
            LearnWidget->setObjectName("LearnWidget");
        LearnWidget->resize(655, 564);
        stackedWidget = new QStackedWidget(LearnWidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(10, 20, 621, 541));
        dictTable = new QWidget();
        dictTable->setObjectName("dictTable");
        customizeBox = new QGroupBox(dictTable);
        customizeBox->setObjectName("customizeBox");
        customizeBox->setGeometry(QRect(40, 230, 531, 211));
        gridLayoutWidget_2 = new QWidget(customizeBox);
        gridLayoutWidget_2->setObjectName("gridLayoutWidget_2");
        gridLayoutWidget_2->setGeometry(QRect(40, 40, 451, 151));
        customizeLayout = new QGridLayout(gridLayoutWidget_2);
        customizeLayout->setObjectName("customizeLayout");
        customizeLayout->setVerticalSpacing(4);
        customizeLayout->setContentsMargins(0, 0, 0, 0);
        defaultBox = new QGroupBox(dictTable);
        defaultBox->setObjectName("defaultBox");
        defaultBox->setGeometry(QRect(40, 10, 531, 201));
        gridLayoutWidget = new QWidget(defaultBox);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(40, 40, 451, 141));
        defaultLayout = new QGridLayout(gridLayoutWidget);
        defaultLayout->setObjectName("defaultLayout");
        defaultLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget->addWidget(dictTable);
        dictWidget = new QWidget();
        dictWidget->setObjectName("dictWidget");
        label = new QLabel(dictWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(260, 110, 61, 31));
        QFont font;
        font.setPointSize(18);
        label->setFont(font);
        backButton = new QToolButton(dictWidget);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(530, 20, 41, 21));
        label_2 = new QLabel(dictWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(230, 180, 141, 61));
        QFont font1;
        font1.setPointSize(20);
        label_2->setFont(font1);
        testButton = new QToolButton(dictWidget);
        testButton->setObjectName("testButton");
        testButton->setGeometry(QRect(250, 380, 91, 31));
        label_4 = new QLabel(dictWidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(230, 250, 141, 61));
        label_4->setFont(font1);
        stackedWidget->addWidget(dictWidget);
        testWidget = new QWidget();
        testWidget->setObjectName("testWidget");
        label_3 = new QLabel(testWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(250, 60, 91, 31));
        backButton_2 = new QToolButton(testWidget);
        backButton_2->setObjectName("backButton_2");
        backButton_2->setGeometry(QRect(530, 20, 41, 21));
        stackedWidget->addWidget(testWidget);

        retranslateUi(LearnWidget);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(LearnWidget);
    } // setupUi

    void retranslateUi(QWidget *LearnWidget)
    {
        LearnWidget->setWindowTitle(QCoreApplication::translate("LearnWidget", "Form", nullptr));
        customizeBox->setTitle(QCoreApplication::translate("LearnWidget", "\350\207\252\345\256\232\344\271\211\350\257\215\345\272\223", nullptr));
        defaultBox->setTitle(QCoreApplication::translate("LearnWidget", "\351\273\230\350\256\244\350\257\215\345\272\223", nullptr));
        label->setText(QCoreApplication::translate("LearnWidget", "\350\257\215\345\272\223\345\220\215", nullptr));
        backButton->setText(QCoreApplication::translate("LearnWidget", "\350\277\224\345\233\236", nullptr));
        label_2->setText(QCoreApplication::translate("LearnWidget", "\345\255\246\344\271\240\350\277\233\345\272\246", nullptr));
        testButton->setText(QCoreApplication::translate("LearnWidget", "\345\274\200\345\247\213\346\265\213\350\257\225", nullptr));
        label_4->setText(QCoreApplication::translate("LearnWidget", "\345\255\246\344\271\240\350\256\260\345\275\225", nullptr));
        label_3->setText(QCoreApplication::translate("LearnWidget", "\346\265\213\350\257\225\347\225\214\351\235\242", nullptr));
        backButton_2->setText(QCoreApplication::translate("LearnWidget", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LearnWidget: public Ui_LearnWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEARNWIDGET_H
