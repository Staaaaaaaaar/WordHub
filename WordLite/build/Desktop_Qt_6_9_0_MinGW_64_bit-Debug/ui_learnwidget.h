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
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LearnWidget
{
public:
    QLabel *label;
    QGroupBox *groupBox;
    QWidget *widget;
    QGridLayout *gridLayout;
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QGroupBox *groupBox_2;
    QWidget *widget1;
    QGridLayout *gridLayout_2;
    QToolButton *toolButton_3;
    QToolButton *toolButton_4;

    void setupUi(QWidget *LearnWidget)
    {
        if (LearnWidget->objectName().isEmpty())
            LearnWidget->setObjectName("LearnWidget");
        LearnWidget->resize(614, 486);
        label = new QLabel(LearnWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 40, 12));
        groupBox = new QGroupBox(LearnWidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(30, 30, 441, 201));
        widget = new QWidget(groupBox);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(30, 30, 131, 51));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        toolButton = new QToolButton(widget);
        toolButton->setObjectName("toolButton");

        gridLayout->addWidget(toolButton, 0, 0, 1, 1);

        toolButton_2 = new QToolButton(widget);
        toolButton_2->setObjectName("toolButton_2");

        gridLayout->addWidget(toolButton_2, 0, 1, 1, 1);

        groupBox_2 = new QGroupBox(LearnWidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(30, 240, 441, 201));
        widget1 = new QWidget(groupBox_2);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(30, 30, 141, 51));
        gridLayout_2 = new QGridLayout(widget1);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        toolButton_3 = new QToolButton(widget1);
        toolButton_3->setObjectName("toolButton_3");

        gridLayout_2->addWidget(toolButton_3, 0, 0, 1, 1);

        toolButton_4 = new QToolButton(widget1);
        toolButton_4->setObjectName("toolButton_4");

        gridLayout_2->addWidget(toolButton_4, 0, 1, 1, 1);


        retranslateUi(LearnWidget);

        QMetaObject::connectSlotsByName(LearnWidget);
    } // setupUi

    void retranslateUi(QWidget *LearnWidget)
    {
        LearnWidget->setWindowTitle(QCoreApplication::translate("LearnWidget", "Form", nullptr));
        label->setText(QCoreApplication::translate("LearnWidget", "learn", nullptr));
        groupBox->setTitle(QCoreApplication::translate("LearnWidget", "\351\273\230\350\256\244\350\257\215\345\272\223", nullptr));
        toolButton->setText(QCoreApplication::translate("LearnWidget", "\350\257\215\345\272\2231", nullptr));
        toolButton_2->setText(QCoreApplication::translate("LearnWidget", "\350\257\215\345\272\2232", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("LearnWidget", "\350\207\252\345\256\232\344\271\211\350\257\215\345\272\223", nullptr));
        toolButton_3->setText(QCoreApplication::translate("LearnWidget", "\350\257\215\345\272\2231", nullptr));
        toolButton_4->setText(QCoreApplication::translate("LearnWidget", "\350\257\215\345\272\2232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LearnWidget: public Ui_LearnWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEARNWIDGET_H
