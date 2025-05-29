/********************************************************************************
** Form generated from reading UI file 'userwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERWIDGET_H
#define UI_USERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserWidget
{
public:
    QLabel *label;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *UserWidget)
    {
        if (UserWidget->objectName().isEmpty())
            UserWidget->setObjectName("UserWidget");
        UserWidget->resize(553, 442);
        label = new QLabel(UserWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 51, 16));
        graphicsView = new QGraphicsView(UserWidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(70, 130, 351, 131));

        retranslateUi(UserWidget);

        QMetaObject::connectSlotsByName(UserWidget);
    } // setupUi

    void retranslateUi(QWidget *UserWidget)
    {
        UserWidget->setWindowTitle(QCoreApplication::translate("UserWidget", "Form", nullptr));
        label->setText(QCoreApplication::translate("UserWidget", "user", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserWidget: public Ui_UserWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERWIDGET_H
