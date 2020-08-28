#ifndef LOGIN_H
#define LOGIN_H
#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "controller.h"

class Login : public QWidget
{
    Q_OBJECT
private:

    Controller* _controller;
    QGridLayout* _layoutLogin;
    QLabel* _labelUser;
    QLabel* _labelPw;
    QLineEdit* _editUser;
    QLineEdit* _editPw;
    QPushButton* _loginBut;

    void impostaStile();

public:
    Login(Controller*, QWidget *parent=nullptr);

signals:
private slots:
    void trylogin();

};

#endif // LOGIN_H
