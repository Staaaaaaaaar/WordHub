/********************************************************************************
** Form generated from reading UI file 'guess_word_widget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUESS_WORD_WIDGET_H
#define UI_GUESS_WORD_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_guess_word_widget
{
public:
    QPushButton *exitButton;
    QPushButton *answerButton;
    QTextEdit *displayTextEdit;
    QPushButton *beginButton;
    QLabel *label;
    QPushButton *ruleButton;
    QLabel *label_2;
    QLineEdit *answerLineEdit;
    QPushButton *commitButton;

    void setupUi(QWidget *guess_word_widget)
    {
        if (guess_word_widget->objectName().isEmpty())
            guess_word_widget->setObjectName("guess_word_widget");
        guess_word_widget->resize(559, 445);
        exitButton = new QPushButton(guess_word_widget);
        exitButton->setObjectName("exitButton");
        exitButton->setGeometry(QRect(30, 163, 93, 41));
        answerButton = new QPushButton(guess_word_widget);
        answerButton->setObjectName("answerButton");
        answerButton->setGeometry(QRect(30, 223, 91, 41));
        displayTextEdit = new QTextEdit(guess_word_widget);
        displayTextEdit->setObjectName("displayTextEdit");
        displayTextEdit->setGeometry(QRect(150, 70, 291, 221));
        beginButton = new QPushButton(guess_word_widget);
        beginButton->setObjectName("beginButton");
        beginButton->setGeometry(QRect(30, 103, 93, 41));
        label = new QLabel(guess_word_widget);
        label->setObjectName("label");
        label->setGeometry(QRect(210, 10, 171, 61));
        ruleButton = new QPushButton(guess_word_widget);
        ruleButton->setObjectName("ruleButton");
        ruleButton->setGeometry(QRect(30, 40, 93, 41));
        label_2 = new QLabel(guess_word_widget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 300, 121, 19));
        answerLineEdit = new QLineEdit(guess_word_widget);
        answerLineEdit->setObjectName("answerLineEdit");
        answerLineEdit->setGeometry(QRect(240, 300, 191, 25));
        commitButton = new QPushButton(guess_word_widget);
        commitButton->setObjectName("commitButton");
        commitButton->setGeometry(QRect(30, 280, 93, 41));

        retranslateUi(guess_word_widget);

        QMetaObject::connectSlotsByName(guess_word_widget);
    } // setupUi

    void retranslateUi(QWidget *guess_word_widget)
    {
        guess_word_widget->setWindowTitle(QCoreApplication::translate("guess_word_widget", "Form", nullptr));
        exitButton->setText(QCoreApplication::translate("guess_word_widget", "\351\200\200\345\207\272\346\270\270\346\210\217", nullptr));
        answerButton->setText(QCoreApplication::translate("guess_word_widget", "\346\237\245\347\234\213\347\255\224\346\241\210", nullptr));
        beginButton->setText(QCoreApplication::translate("guess_word_widget", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        label->setText(QCoreApplication::translate("guess_word_widget", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; font-weight:700;\">\347\214\234\350\257\215\346\270\270\346\210\217</span></p></body></html>", nullptr));
        ruleButton->setText(QCoreApplication::translate("guess_word_widget", "\346\270\270\346\210\217\350\247\204\345\210\231", nullptr));
        label_2->setText(QCoreApplication::translate("guess_word_widget", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt; font-weight:700;\">\345\234\250\346\255\244\350\276\223\345\205\245\347\255\224\346\241\210\357\274\232</span></p></body></html>", nullptr));
        commitButton->setText(QCoreApplication::translate("guess_word_widget", "\347\241\256\345\256\232\347\255\224\346\241\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class guess_word_widget: public Ui_guess_word_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUESS_WORD_WIDGET_H
