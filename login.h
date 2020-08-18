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
    Controller* controller;
    QGridLayout* layoutLogin;
    QLabel* labeluser;
    QLabel* labelpw;
    QLineEdit* edituser;
    QLineEdit* editpw;
    QPushButton* loginbut;

public:
    Login(QWidget *parent, Controller*);

signals:
private slots:
    void trylogin();

};

#endif // LOGIN_H
