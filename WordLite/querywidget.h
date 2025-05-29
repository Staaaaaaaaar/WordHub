#ifndef QUERYWIDGET_H
#define QUERYWIDGET_H

#include <QWidget>
#include <wordwidget.h>
#include <./back_head/database.h>

namespace Ui {
class QueryWidget;
}

class QueryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QueryWidget(QWidget *parent = nullptr);
    ~QueryWidget();

    WordDatabase* wordDataBase;
    QString defaultWordDB;
    QVector<QString> wordDBList;

    void setupUI();
    void connectSignals();

private slots:
    void on_searchEdit_returnPressed();

    void on_tabWidget_tabCloseRequested(int index);

    void on_comboBox_currentTextChanged(const QString &arg1);

private: signals:
    void sendMes(QString message, int timeout=0);
    void clearMes();


private:
    Ui::QueryWidget *ui;
};



#endif // QUERYWIDGET_H
