#ifndef LEARNWIDGET_H
#define LEARNWIDGET_H

#include <QWidget>

namespace Ui {
class LearnWidget;
}

class LearnWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LearnWidget(QWidget *parent = nullptr);
    ~LearnWidget();

private:
    Ui::LearnWidget *ui;
};

#endif // LEARNWIDGET_H
