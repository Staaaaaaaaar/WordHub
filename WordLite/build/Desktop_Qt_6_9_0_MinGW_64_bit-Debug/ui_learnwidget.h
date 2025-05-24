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
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LearnWidget
{
public:
    QLabel *label;
    QToolButton *toolButton;
    QToolButton *toolButton_2;

    void setupUi(QWidget *LearnWidget)
    {
        if (LearnWidget->objectName().isEmpty())
            LearnWidget->setObjectName("LearnWidget");
        LearnWidget->resize(400, 300);
        label = new QLabel(LearnWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 40, 12));
        toolButton = new QToolButton(LearnWidget);
        toolButton->setObjectName("toolButton");
        toolButton->setGeometry(QRect(20, 50, 51, 71));
        toolButton_2 = new QToolButton(LearnWidget);
        toolButton_2->setObjectName("toolButton_2");
        toolButton_2->setGeometry(QRect(240, 50, 51, 71));

        retranslateUi(LearnWidget);

        QMetaObject::connectSlotsByName(LearnWidget);
    } // setupUi

    void retranslateUi(QWidget *LearnWidget)
    {
        LearnWidget->setWindowTitle(QCoreApplication::translate("LearnWidget", "Form", nullptr));
        label->setText(QCoreApplication::translate("LearnWidget", "learn", nullptr));
        toolButton->setText(QCoreApplication::translate("LearnWidget", "\350\257\215\345\272\2231", nullptr));
        toolButton_2->setText(QCoreApplication::translate("LearnWidget", "\350\257\215\345\272\2232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LearnWidget: public Ui_LearnWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEARNWIDGET_H
