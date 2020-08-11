#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller *controller=new Controller;
    Login l(nullptr, controller);
    l.show();
    return a.exec();
}
