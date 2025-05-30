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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Wordle
{
public:
    QLabel *label;
    QPushButton *exitButton;
    QPushButton *beginButton;
    QPushButton *checkButton;
    QLineEdit *getWord;
    QLabel *label_2;
    QPushButton *commitButton;
    QLabel *winLabel;
    QPushButton *restartButton;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *a53;
    QLabel *a64;
    QLabel *a44;
    QLabel *a41;
    QLabel *a43;
    QLabel *a54;
    QLabel *a42;
    QLabel *a45;
    QLabel *a55;
    QLabel *a63;
    QLabel *a35;
    QLabel *a34;
    QLabel *a33;
    QLabel *a32;
    QLabel *a31;
    QLabel *a21;
    QLabel *a22;
    QLabel *a23;
    QLabel *a24;
    QLabel *a25;
    QLabel *a13;
    QLabel *a12;
    QLabel *a11;
    QLabel *a14;
    QLabel *a15;
    QLabel *a51;
    QLabel *a52;
    QLabel *a61;
    QLabel *a62;
    QLabel *a65;

    void setupUi(QWidget *Wordle)
    {
        if (Wordle->objectName().isEmpty())
            Wordle->setObjectName("Wordle");
        Wordle->resize(513, 418);
        label = new QLabel(Wordle);
        label->setObjectName("label");
        label->setGeometry(QRect(158, 10, 181, 31));
        exitButton = new QPushButton(Wordle);
        exitButton->setObjectName("exitButton");
        exitButton->setGeometry(QRect(10, 40, 93, 41));
        beginButton = new QPushButton(Wordle);
        beginButton->setObjectName("beginButton");
        beginButton->setGeometry(QRect(10, 90, 93, 41));
        checkButton = new QPushButton(Wordle);
        checkButton->setObjectName("checkButton");
        checkButton->setGeometry(QRect(10, 140, 93, 41));
        getWord = new QLineEdit(Wordle);
        getWord->setObjectName("getWord");
        getWord->setGeometry(QRect(310, 320, 131, 31));
        label_2 = new QLabel(Wordle);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(160, 320, 141, 31));
        commitButton = new QPushButton(Wordle);
        commitButton->setObjectName("commitButton");
        commitButton->setGeometry(QRect(10, 190, 93, 41));
        winLabel = new QLabel(Wordle);
        winLabel->setObjectName("winLabel");
        winLabel->setGeometry(QRect(30, 300, 111, 41));
        restartButton = new QPushButton(Wordle);
        restartButton->setObjectName("restartButton");
        restartButton->setGeometry(QRect(10, 240, 93, 41));
        widget = new QWidget(Wordle);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(130, 70, 311, 241));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setHorizontalSpacing(5);
        gridLayout->setVerticalSpacing(6);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        a53 = new QLabel(widget);
        a53->setObjectName("a53");

        gridLayout->addWidget(a53, 8, 2, 1, 1);

        a64 = new QLabel(widget);
        a64->setObjectName("a64");

        gridLayout->addWidget(a64, 9, 3, 1, 1);

        a44 = new QLabel(widget);
        a44->setObjectName("a44");

        gridLayout->addWidget(a44, 7, 3, 1, 1);

        a41 = new QLabel(widget);
        a41->setObjectName("a41");

        gridLayout->addWidget(a41, 7, 0, 1, 1);

        a43 = new QLabel(widget);
        a43->setObjectName("a43");

        gridLayout->addWidget(a43, 7, 2, 1, 1);

        a54 = new QLabel(widget);
        a54->setObjectName("a54");

        gridLayout->addWidget(a54, 8, 3, 1, 1);

        a42 = new QLabel(widget);
        a42->setObjectName("a42");

        gridLayout->addWidget(a42, 7, 1, 1, 1);

        a45 = new QLabel(widget);
        a45->setObjectName("a45");

        gridLayout->addWidget(a45, 7, 4, 1, 1);

        a55 = new QLabel(widget);
        a55->setObjectName("a55");

        gridLayout->addWidget(a55, 8, 4, 1, 1);

        a63 = new QLabel(widget);
        a63->setObjectName("a63");

        gridLayout->addWidget(a63, 9, 2, 1, 1);

        a35 = new QLabel(widget);
        a35->setObjectName("a35");

        gridLayout->addWidget(a35, 6, 4, 1, 1);

        a34 = new QLabel(widget);
        a34->setObjectName("a34");

        gridLayout->addWidget(a34, 6, 3, 1, 1);

        a33 = new QLabel(widget);
        a33->setObjectName("a33");

        gridLayout->addWidget(a33, 6, 2, 1, 1);

        a32 = new QLabel(widget);
        a32->setObjectName("a32");

        gridLayout->addWidget(a32, 6, 1, 1, 1);

        a31 = new QLabel(widget);
        a31->setObjectName("a31");

        gridLayout->addWidget(a31, 6, 0, 1, 1);

        a21 = new QLabel(widget);
        a21->setObjectName("a21");

        gridLayout->addWidget(a21, 5, 0, 1, 1);

        a22 = new QLabel(widget);
        a22->setObjectName("a22");

        gridLayout->addWidget(a22, 5, 1, 1, 1);

        a23 = new QLabel(widget);
        a23->setObjectName("a23");

        gridLayout->addWidget(a23, 5, 2, 1, 1);

        a24 = new QLabel(widget);
        a24->setObjectName("a24");

        gridLayout->addWidget(a24, 5, 3, 1, 1);

        a25 = new QLabel(widget);
        a25->setObjectName("a25");

        gridLayout->addWidget(a25, 5, 4, 1, 1);

        a13 = new QLabel(widget);
        a13->setObjectName("a13");

        gridLayout->addWidget(a13, 4, 2, 1, 1);

        a12 = new QLabel(widget);
        a12->setObjectName("a12");

        gridLayout->addWidget(a12, 4, 1, 1, 1);

        a11 = new QLabel(widget);
        a11->setObjectName("a11");

        gridLayout->addWidget(a11, 4, 0, 1, 1);

        a14 = new QLabel(widget);
        a14->setObjectName("a14");

        gridLayout->addWidget(a14, 4, 3, 1, 1);

        a15 = new QLabel(widget);
        a15->setObjectName("a15");

        gridLayout->addWidget(a15, 4, 4, 1, 1);

        a51 = new QLabel(widget);
        a51->setObjectName("a51");

        gridLayout->addWidget(a51, 8, 0, 1, 1);

        a52 = new QLabel(widget);
        a52->setObjectName("a52");

        gridLayout->addWidget(a52, 8, 1, 1, 1);

        a61 = new QLabel(widget);
        a61->setObjectName("a61");

        gridLayout->addWidget(a61, 9, 0, 1, 1);

        a62 = new QLabel(widget);
        a62->setObjectName("a62");

        gridLayout->addWidget(a62, 9, 1, 1, 1);

        a65 = new QLabel(widget);
        a65->setObjectName("a65");

        gridLayout->addWidget(a65, 9, 4, 1, 1);


        retranslateUi(Wordle);

        QMetaObject::connectSlotsByName(Wordle);
    } // setupUi

    void retranslateUi(QWidget *Wordle)
    {
        Wordle->setWindowTitle(QCoreApplication::translate("Wordle", "Form", nullptr));
        label->setText(QCoreApplication::translate("Wordle", "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:700;\">Wordle</span></p></body></html>", nullptr));
        exitButton->setText(QCoreApplication::translate("Wordle", "\351\200\200\345\207\272\346\270\270\346\210\217", nullptr));
        beginButton->setText(QCoreApplication::translate("Wordle", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        checkButton->setText(QCoreApplication::translate("Wordle", "\346\237\245\347\234\213\350\247\243", nullptr));
        label_2->setText(QCoreApplication::translate("Wordle", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt; font-weight:700;\">\350\257\267\350\276\223\345\205\245\344\275\240\347\214\234\347\232\204\345\215\225\350\257\215</span></p></body></html>", nullptr));
        commitButton->setText(QCoreApplication::translate("Wordle", "\347\241\256\350\256\244\350\276\223\345\205\245", nullptr));
        winLabel->setText(QString());
        restartButton->setText(QCoreApplication::translate("Wordle", "\351\207\215\346\226\260\345\274\200\345\247\213", nullptr));
        a53->setText(QString());
        a64->setText(QString());
        a44->setText(QString());
        a41->setText(QString());
        a43->setText(QString());
        a54->setText(QString());
        a42->setText(QString());
        a45->setText(QString());
        a55->setText(QString());
        a63->setText(QString());
        a35->setText(QString());
        a34->setText(QString());
        a33->setText(QString());
        a32->setText(QString());
        a31->setText(QString());
        a21->setText(QString());
        a22->setText(QString());
        a23->setText(QString());
        a24->setText(QString());
        a25->setText(QString());
        a13->setText(QString());
        a12->setText(QString());
        a11->setText(QString());
        a14->setText(QString());
        a15->setText(QString());
        a51->setText(QString());
        a52->setText(QString());
        a61->setText(QString());
        a62->setText(QString());
        a65->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Wordle: public Ui_Wordle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORDLE_H
