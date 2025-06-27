#ifndef GUESS_WORD_WIDGET_H
#define GUESS_WORD_WIDGET_H

#include <QWidget>
#include "guess_according_to_description/guess_word.h"
#include <QFutureWatcher>
#include <map>
#include <QString>

// Forward declaration for pointer members to reduce header dependencies
class QMessageBox;

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
    // 异步流程的槽
    void onBeginButtonClicked();
    void handleProcessingFinished();

    // 其他UI按钮的槽
    void on_exitButton_clicked();
    void onRuleButtonClicked();
    void onAnswerButtonClicked();
    void onCommitButtonClicked();

signals:
    void exitRequested();
    void sendId(int id); 

private:
    Ui::guess_word_widget *ui;
    
    // 异步处理相关
    guess_word* m_guesser;
    QFutureWatcher<std::map<QString, QString>> *m_watcher;
    
    // 状态变量 (来自旧代码)
    QString m_word;
    QString m_translation;
    QString m_description;
    QMessageBox* m_dialog;
};

#endif // GUESS_WORD_WIDGET_H
