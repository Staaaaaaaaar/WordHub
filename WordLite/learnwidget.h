#ifndef LEARNWIDGET_H
#define LEARNWIDGET_H

#include "qtoolbutton.h"
#include <QWidget>

namespace Ui {
class LearnWidget;
class DictButton;
}

class DictButton : public QToolButton
{
    Q_OBJECT

public:
    explicit DictButton(); //附加一个字典指针
    ~DictButton();


private:

};


class LearnWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LearnWidget(QWidget *parent = nullptr);
    ~LearnWidget();

    void addButton(DictButton* dictButtton);

private:
    Ui::LearnWidget *ui;
};




#endif // LEARNWIDGET_H
