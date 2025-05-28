/********************************************************************************
** Form generated from reading UI file 'gamewidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWIDGET_H
#define UI_GAMEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWidget
{
public:
    QStackedWidget *stackedWidget;
    QWidget *gameTable;
    QToolButton *wordleButton;
    QPushButton *guessButton;
    QWidget *wordleWidget;
    QToolButton *toolButton;
    QToolButton *toolButton_2;

    void setupUi(QWidget *GameWidget)
    {
        if (GameWidget->objectName().isEmpty())
            GameWidget->setObjectName("GameWidget");
        GameWidget->resize(512, 400);
        stackedWidget = new QStackedWidget(GameWidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(20, 20, 471, 371));
        gameTable = new QWidget();
        gameTable->setObjectName("gameTable");
        wordleButton = new QToolButton(gameTable);
        wordleButton->setObjectName("wordleButton");
        wordleButton->setGeometry(QRect(50, 40, 121, 61));
        guessButton = new QPushButton(gameTable);
        guessButton->setObjectName("guessButton");
        guessButton->setGeometry(QRect(50, 230, 121, 61));
        stackedWidget->addWidget(gameTable);
        wordleWidget = new QWidget();
        wordleWidget->setObjectName("wordleWidget");
        toolButton = new QToolButton(wordleWidget);
        toolButton->setObjectName("toolButton");
        toolButton->setGeometry(QRect(340, 20, 41, 21));
        toolButton_2 = new QToolButton(wordleWidget);
        toolButton_2->setObjectName("toolButton_2");
        toolButton_2->setGeometry(QRect(410, 20, 31, 21));
        stackedWidget->addWidget(wordleWidget);

        retranslateUi(GameWidget);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GameWidget);
    } // setupUi

    void retranslateUi(QWidget *GameWidget)
    {
        GameWidget->setWindowTitle(QCoreApplication::translate("GameWidget", "Form", nullptr));
        wordleButton->setText(QCoreApplication::translate("GameWidget", "Wordle", nullptr));
        guessButton->setText(QCoreApplication::translate("GameWidget", "Guess", nullptr));
        toolButton->setText(QCoreApplication::translate("GameWidget", "\345\210\267\346\226\260", nullptr));
        toolButton_2->setText(QCoreApplication::translate("GameWidget", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameWidget: public Ui_GameWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWIDGET_H
