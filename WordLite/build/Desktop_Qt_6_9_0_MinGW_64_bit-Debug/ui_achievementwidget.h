/********************************************************************************
** Form generated from reading UI file 'achievementwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACHIEVEMENTWIDGET_H
#define UI_ACHIEVEMENTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AchievementWidget
{
public:
    QLabel *label;

    void setupUi(QWidget *AchievementWidget)
    {
        if (AchievementWidget->objectName().isEmpty())
            AchievementWidget->setObjectName("AchievementWidget");
        AchievementWidget->resize(400, 300);
        label = new QLabel(AchievementWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 40, 12));

        retranslateUi(AchievementWidget);

        QMetaObject::connectSlotsByName(AchievementWidget);
    } // setupUi

    void retranslateUi(QWidget *AchievementWidget)
    {
        AchievementWidget->setWindowTitle(QCoreApplication::translate("AchievementWidget", "Form", nullptr));
        label->setText(QCoreApplication::translate("AchievementWidget", "ach", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AchievementWidget: public Ui_AchievementWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACHIEVEMENTWIDGET_H
