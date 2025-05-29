/********************************************************************************
** Form generated from reading UI file 'querywidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUERYWIDGET_H
#define UI_QUERYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QueryWidget
{
public:
    QLabel *label;
    QLineEdit *searchEdit;
    QTabWidget *tabWidget;
    QWidget *tab;
    QComboBox *comboBox;

    void setupUi(QWidget *QueryWidget)
    {
        if (QueryWidget->objectName().isEmpty())
            QueryWidget->setObjectName("QueryWidget");
        QueryWidget->resize(600, 500);
        label = new QLabel(QueryWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 40, 12));
        searchEdit = new QLineEdit(QueryWidget);
        searchEdit->setObjectName("searchEdit");
        searchEdit->setGeometry(QRect(30, 40, 113, 20));
        tabWidget = new QTabWidget(QueryWidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(30, 70, 531, 400));
        tabWidget->setTabShape(QTabWidget::TabShape::Rounded);
        tabWidget->setIconSize(QSize(16, 16));
        tabWidget->setUsesScrollButtons(false);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(true);
        tabWidget->setMovable(true);
        tabWidget->setTabBarAutoHide(false);
        tab = new QWidget();
        tab->setObjectName("tab");
        tab->setEnabled(true);
        tabWidget->addTab(tab, QString());
        comboBox = new QComboBox(QueryWidget);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(480, 40, 62, 22));

        retranslateUi(QueryWidget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QueryWidget);
    } // setupUi

    void retranslateUi(QWidget *QueryWidget)
    {
        QueryWidget->setWindowTitle(QCoreApplication::translate("QueryWidget", "Form", nullptr));
        label->setText(QCoreApplication::translate("QueryWidget", "query", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("QueryWidget", "welcome", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QueryWidget: public Ui_QueryWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUERYWIDGET_H
