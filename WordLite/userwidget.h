#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QWidget>

namespace Ui {
class UserWidget;
}

class UserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserWidget(QWidget *parent = nullptr);
    ~UserWidget();
    void setUser();
    void setDays();
    void setAcc();
    void setPic();
    void setTotalAcc();
    static const int MARGIN=5;
    static const int WIDTH=30;
    QVector<int> dailyLearningData;
    QVector<double> dailyLearningAcc;
    void clear();
    QString getname();

protected:
    void paintEvent(QPaintEvent *event)override;

private:
    Ui::UserWidget *ui;
};

#endif // USERWIDGET_H
