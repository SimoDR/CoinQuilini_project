#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent), _listainquilini(new ListaInquilini)
{
}

bool Controller::login(const QString & user, const QString & pw)
{
    //try {
    //se trova utente apre mainwindow
    if (_listainquilini->checkCredenziali(user.toStdString(), pw.toStdString()))
    {
        Mainwindow* mainwindow=new Mainwindow(nullptr, this, user);
        setParent(mainwindow);
        mainwindow->show();
        return true;
    }
    else {
        QMessageBox nomatch;
        nomatch.setText("Utente o password errati");
        nomatch.exec();
        return false;
    }
    //ritorna messaggio di errore
    //catch()

    //}
}

vector<string> Controller::getInquilini()
{
    return _listainquilini->inquilini();
}

void Controller::rimuoviInquilino(unsigned int pos)
{
    _listainquilini->rimuovi(pos);
}

vector<std::string> Controller::getInquilinoPos(unsigned int pos)
{
    return _listainquilini->getCredenziali(pos);
}

void Controller::aggiungiInquilino(const QString & user, const QString & pw)
{
    _listainquilini->creaInserisci(user.toStdString(), pw.toStdString());
}

void Controller::modificaInquilino(const QString &user, const QString & pw, unsigned int pos)
{
    _listainquilini->modifica(user.toStdString(), pw.toStdString(), pos);
}

void Controller::checkAdmin(unsigned int pos)
{
    _listainquilini->checkAdmin(pos);
}

unsigned short Controller::isAdmin(const std::string & user) const
{
   return _listainquilini->isAdmin(user);
}


void Controller::creaNuovoIncarico(vector<std::string> parametri)
{

}
