/********************************************************************************
** Form generated from reading UI file 'wordwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORDWIDGET_H
#define UI_WORDWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WordWidget
{
public:
    QLabel *label;

    void setupUi(QWidget *WordWidget)
    {
        if (WordWidget->objectName().isEmpty())
            WordWidget->setObjectName("WordWidget");
        WordWidget->resize(500, 400);
        label = new QLabel(WordWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 10, 111, 41));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);

        retranslateUi(WordWidget);

        QMetaObject::connectSlotsByName(WordWidget);
    } // setupUi

    void retranslateUi(QWidget *WordWidget)
    {
        WordWidget->setWindowTitle(QCoreApplication::translate("WordWidget", "Form", nullptr));
        label->setText(QCoreApplication::translate("WordWidget", "word", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WordWidget: public Ui_WordWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORDWIDGET_H
