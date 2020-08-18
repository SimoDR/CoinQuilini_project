#include "login.h"

Login::Login(QWidget *parent, Controller* c) : QWidget(parent), controller(c)
{
    setWindowTitle("Login");
    //user label
    labeluser = new QLabel();
    labeluser->setText("User:");
    //password label
    labelpw = new QLabel();
    labelpw->setText("Password:");
    //line edit user
    edituser = new QLineEdit();
    //line edit password
    editpw = new QLineEdit();
    editpw->setEchoMode(QLineEdit::Password);
    //login button
    loginbut = new QPushButton();
    loginbut->setText("Login");
    //layout
    layoutLogin= new QGridLayout;
    layoutLogin->addWidget(labeluser, 1, 0);
    layoutLogin->addWidget(edituser, 1, 1);
    layoutLogin->addWidget(labelpw, 2, 0);
    layoutLogin->addWidget(editpw, 2, 1);
    layoutLogin->addWidget(loginbut, 3, 0, 1, 2);
    //size
    layoutLogin->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(layoutLogin);

    connect(loginbut, SIGNAL(clicked()), this, SLOT(trylogin()));
}

//chiama il controller per check credenziali e in caso corrette chiude il login, altrimenti resetta i campi
void Login::trylogin()
{

    bool logged=controller->login(edituser->text(), editpw->text());
    if (logged)
        close();
    else{

        edituser->clear();
        editpw->clear();
    }
}




