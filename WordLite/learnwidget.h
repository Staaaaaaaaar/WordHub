#ifndef LEARNWIDGET_H
#define LEARNWIDGET_H

#include "qtoolbutton.h"
#include <QWidget>
#include <QGridLayout>
#include <QList>
#include <QScrollArea>
#include <back_head/database.h>

namespace Ui {
class LearnWidget;
class DictButton;
class AutoGridLayout;
}

class DictButton : public QToolButton
{
    Q_OBJECT

public:
    explicit DictButton(QString text="词库名"); //附加一个字典指针
    ~DictButton();

private:

};



class LearnWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LearnWidget(QWidget *parent = nullptr);
    ~LearnWidget();

    WordDatabase* DBptr;
    QVector<QString> defaultDictNames;
    QVector<QString> customDictNames;

    void addButtonsToGrid(QGridLayout *grid, const QList<DictButton*> &buttons, int columns = 3);
    void initDictWidget();
    void initTestWidget();

    // 设置UI和连接信号槽
    void setupUI();
    void connectSignals();

private slots:
    void on_dictButton_clicked();
    void on_testButton_clicked();
    void on_addDictButton_clicked();

private:
    Ui::LearnWidget *ui;
    QList<DictButton*> defaultButtons;
    QList<DictButton*> customizeButtons;
    DictButton* addDictButton;
};




#endif // LEARNWIDGET_H
