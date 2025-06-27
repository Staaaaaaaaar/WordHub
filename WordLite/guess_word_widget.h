#ifndef GUESS_WORD_WIDGET_H
#define GUESS_WORD_WIDGET_H

#include <QWidget>
#include "guess_according_to_description/guess_word.h" // 引入逻辑处理类
#include <QFutureWatcher> // 引入并发监视器
#include <map> // 引入 map
#include <QString> // 引入 QString

namespace Ui {
class guess_word_widget;
}

class guess_word_widget : public QWidget
{
    Q_OBJECT

public:
    explicit guess_word_widget(QWidget *parent = nullptr);
    ~guess_word_widget();

private slots:
    // 当点击“开始游戏”按钮时触发
    void onStartButtonClicked();
    // 当后台任务完成时，由监视器调用
    void handleProcessingFinished();

    void on_exitButton_clicked();

signals:
    void exitRequested();
    void sendId(int id);

private:
    Ui::guess_word_widget *ui;
    guess_word* m_guesser; // 耗时操作的逻辑对象
    // 监视后台任务的 QFutureWatcher
    QFutureWatcher<std::map<QString, QString>> *m_watcher;
    QString m_correctWord; // 用于存储正确的单词答案
};

#endif // GUESS_WORD_WIDGET_H
