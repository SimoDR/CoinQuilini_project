#include "login.h"


void Login::impostaStile()
{
    QFile file(":/resources/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    file.close();
    setStyleSheet(styleSheet);
}

Login::Login(Controller* c, QWidget *parent) : QWidget(parent), _controller(c)
{
    setWindowTitle("Login");
    setWindowIcon(QIcon(":/resources/icon.png"));
    //user label
    _labelUser = new QLabel();
    _labelUser->setText("User:");
    //password label
    _labelPw = new QLabel();
    _labelPw->setText("Password:");
    //line edit user
    _editUser = new QLineEdit();
    //line edit password
    _editPw = new QLineEdit();
    _editPw->setEchoMode(QLineEdit::Password);
    //login button
    _loginBut = new QPushButton();
    _loginBut->setText("Login");
    //layout
    _layoutLogin= new QGridLayout;
    _layoutLogin->addWidget(_labelUser, 1, 0);
    _layoutLogin->addWidget(_editUser, 1, 1);
    _layoutLogin->addWidget(_labelPw, 2, 0);
    _layoutLogin->addWidget(_editPw, 2, 1);
    _layoutLogin->addWidget(_loginBut, 3, 0, 1, 2);
    //size
    _layoutLogin->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(_layoutLogin);
    impostaStile();
    connect(_editUser,SIGNAL(returnPressed()), this, SLOT(trylogin()));
    connect(_editPw,SIGNAL(returnPressed()), this, SLOT(trylogin()));
    connect(_loginBut, SIGNAL(clicked()), this, SLOT(trylogin()));

}

//chiama il controller per check credenziali e in caso corrette chiude il login, altrimenti resetta i campi
void Login::trylogin()
{
    bool logged=_controller->login(_editUser->text(), _editPw->text());

    if (logged)
        close();
    else{
        _editUser->clear();
        _editPw->clear();
    }
}
