#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

namespace Ui {
class loginWidget;
}

class loginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit loginWidget(QWidget *parent = nullptr);
    ~loginWidget();
    bool readUser();
    bool comparePassword(const QString & username);
    void judgeLogin();
    void skipToRegister();

signals:
    void loginClicked();
    void registerClicked();

private:
    Ui::loginWidget *ui;
};

#endif // LOGINWIDGET_H
