#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent), _listaInquilini(ListaInquilini())
{
}

bool Controller::login(const QString & user, const QString & pw)
{
    if (_listaInquilini.checkCredenziali(user.toStdString(), pw.toStdString()))
    {
        Mainwindow * mainwindow= new Mainwindow(nullptr, this, user);
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
}

vector<string> Controller::getInquilini()
{
    return _listaInquilini.inquilini();
}

void Controller::rimuoviInquilino(unsigned int pos)
{
    _listaInquilini.rimuovi(pos);
}

vector<std::string> Controller::getInquilinoPos(unsigned int pos)
{
    return _listaInquilini.getCredenziali(pos);
}

void Controller::aggiungiInquilino(const QString & user, const QString & pw)
{
    _listaInquilini.creaInserisci(user.toStdString(), pw.toStdString());
}

void Controller::modificaInquilino(const QString &user, const QString & pw, unsigned int pos)
{
    _listaInquilini.modifica(user.toStdString(), pw.toStdString(), pos);
}

void Controller::checkAdmin(unsigned int pos)
{
    _listaInquilini.checkAdmin(pos);
}

unsigned short Controller::isAdmin(const std::string & user) const
{
   return _listaInquilini.isAdmin(user);
}


void Controller::creaNuovoIncarico(vector<std::string> parametri)
{

}
