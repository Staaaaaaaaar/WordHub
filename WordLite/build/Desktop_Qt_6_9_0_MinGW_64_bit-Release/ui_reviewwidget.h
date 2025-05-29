/********************************************************************************
** Form generated from reading UI file 'reviewwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REVIEWWIDGET_H
#define UI_REVIEWWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReviewWidget
{
public:
    QLabel *label;

    void setupUi(QWidget *ReviewWidget)
    {
        if (ReviewWidget->objectName().isEmpty())
            ReviewWidget->setObjectName("ReviewWidget");
        ReviewWidget->resize(604, 511);
        label = new QLabel(ReviewWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 40, 12));

        retranslateUi(ReviewWidget);

        QMetaObject::connectSlotsByName(ReviewWidget);
    } // setupUi

    void retranslateUi(QWidget *ReviewWidget)
    {
        ReviewWidget->setWindowTitle(QCoreApplication::translate("ReviewWidget", "Form", nullptr));
        label->setText(QCoreApplication::translate("ReviewWidget", "review", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReviewWidget: public Ui_ReviewWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REVIEWWIDGET_H
