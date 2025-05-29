/********************************************************************************
** Form generated from reading UI file 'wordle.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORDLE_H
#define UI_WORDLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Wordle
{
public:
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QWidget *Wordle)
    {
        if (Wordle->objectName().isEmpty())
            Wordle->setObjectName("Wordle");
        Wordle->resize(513, 418);
        label = new QLabel(Wordle);
        label->setObjectName("label");
        label->setGeometry(QRect(158, 10, 181, 31));
        pushButton = new QPushButton(Wordle);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 80, 93, 41));
        pushButton_2 = new QPushButton(Wordle);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(10, 167, 93, 41));
        pushButton_3 = new QPushButton(Wordle);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(10, 260, 93, 41));

        retranslateUi(Wordle);

        QMetaObject::connectSlotsByName(Wordle);
    } // setupUi

    void retranslateUi(QWidget *Wordle)
    {
        Wordle->setWindowTitle(QCoreApplication::translate("Wordle", "Form", nullptr));
        label->setText(QCoreApplication::translate("Wordle", "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:700;\">Wordle</span></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("Wordle", "\351\200\200\345\207\272\346\270\270\346\210\217", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Wordle", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Wordle", "\346\237\245\347\234\213\350\247\243", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Wordle: public Ui_Wordle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORDLE_H
