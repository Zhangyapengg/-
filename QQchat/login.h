#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QVector>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private:
    Ui::Login *ui;
    QVector<bool> Isshow;
};

#endif // LOGIN_H
