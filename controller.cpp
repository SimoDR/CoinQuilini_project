#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{

}

bool Controller::login(QString user, QString pw) //implementato per debug, poi bisognarà andare nella lista a prendersi i dati degli utenti
{
    //se trova utente apre mainwindow
    if (user=="ranzy" && pw=="cuea")
    {
        Mainwindow* mainwindow=new Mainwindow(nullptr, this, "ranzy");
        setParent(mainwindow);
        mainwindow->show();
        return true;
    }
    //altrimenti ritorna messaggio di errore
    else {
        QMessageBox nomatch;
        nomatch.setText("Utente o password errati");
        nomatch.exec();
        return false;
    }


}
