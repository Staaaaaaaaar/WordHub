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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AchievementWidget
{
public:

    void setupUi(QWidget *AchievementWidget)
    {
        if (AchievementWidget->objectName().isEmpty())
            AchievementWidget->setObjectName("AchievementWidget");
        AchievementWidget->resize(576, 498);

        retranslateUi(AchievementWidget);

        QMetaObject::connectSlotsByName(AchievementWidget);
    } // setupUi

    void retranslateUi(QWidget *AchievementWidget)
    {
        AchievementWidget->setWindowTitle(QCoreApplication::translate("AchievementWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AchievementWidget: public Ui_AchievementWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACHIEVEMENTWIDGET_H
