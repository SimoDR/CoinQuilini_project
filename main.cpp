
#include <iostream>
#include<vector>
#include <QApplication>
#include "calendario.h"
#include "login.h"
using std::cout;
using std::endl;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller controller;
    Login l(nullptr, &controller);
    l.show();
    return a.exec();

}
