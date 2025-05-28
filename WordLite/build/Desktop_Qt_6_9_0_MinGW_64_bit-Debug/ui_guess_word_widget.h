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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_guess_word_widget
{
public:

    void setupUi(QWidget *guess_word_widget)
    {
        if (guess_word_widget->objectName().isEmpty())
            guess_word_widget->setObjectName("guess_word_widget");
        guess_word_widget->resize(400, 300);

        retranslateUi(guess_word_widget);

        QMetaObject::connectSlotsByName(guess_word_widget);
    } // setupUi

    void retranslateUi(QWidget *guess_word_widget)
    {
        guess_word_widget->setWindowTitle(QCoreApplication::translate("guess_word_widget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class guess_word_widget: public Ui_guess_word_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUESS_WORD_WIDGET_H
