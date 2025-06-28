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
    void refresh();
    static const int MARGIN=5;
    static const int WIDTH=30;
    QVector<int> dailyLearningData;
    QVector<double> dailyLearningAcc;
    void clear();
    QString getname();

    // --- 新增：公共的成就检查函数 ---
    void checkLearningAchievements();

protected:
    void paintEvent(QPaintEvent *event)override;

    // --- 新增：重写 showEvent 以便在界面显示时自动触发 ---
    void showEvent(QShowEvent *event) override;

signals:
    // --- 新增：用于请求解锁成就的信号 ---
    void requestUnlockAchievement(int achievementId);

private slots:
    // --- 修改：槽函数名与 refreshButton 匹配 ---
    void on_refreshButton_clicked();

private:
    Ui::UserWidget *ui;
};

#endif // USERWIDGET_H
