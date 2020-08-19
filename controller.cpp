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
    //altrimenti ritorna messaggio di errore

    else {
        QMessageBox nomatch;
        nomatch.setText("Utente o password errati");
        nomatch.exec();
        return false;
    }



}

/*
 * PARAMETRI
 * 0- NomeIncarico
 * 1- Tipo
 * 2- Incaricato //eventualmente vuoto
 * 3- Cadenza //se 0 è incarico singolo.
 * 4- TempoStimato
 * 5- StanzeDaPulire
 * 6- NumeroCommensali
 * //7- CosaButtare
 * 7- PesoSpazzatura
 * 8- Importo
 * 9- DataLimite
 * 10- DataInizio
 * 11-Partecipanti
 * ..
 *
 *
 * */

/*
void Controller::creaNuovoIncarico(vector<std::string> parametri)
{
    string NomeIncarico=parametri[0];
    string TipoIncarico=parametri[1];
    string NomeIncaricato=parametri[2];
    int CadenzaIncarico=std::stoi(parametri[3]);
    int TempoStimato=std::stoi(parametri[4]);
    unsigned short int StanzeDaPulire=std::stoi(parametri[5]);
    unsigned short int NumeroCommensali=std::stoi(parametri[6]);
    unsigned short int PesoSpazzatura=std::stoi(parametri[7]);
    int Importo=std::stoi(parametri[8]);
    Data * DataLimite=new Data(parametri[9]);
    Data * DataInizio=new Data(parametri[10]);

    for(std::vector<string>::size_type i=10;i<parametri.size();i++)
    {

   }
    if(TipoIncarico=="Spesa")
        Incarico * i=new Spesa(NomeIncarico,NomeIncarico)

    if (CadenzaIncarico==0) //incarico regolare, assegnazione automatica degli inquilini tra i disponibili nel buffer
    {
        for(int index=0;index<CadenzaIncarico;index++)
        {

        }
    }
    else //incarico singolo, assegnazione automatica o manuale
    {

    }
}
*/

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
    _listaInquilini.creaInserisci("INQUILINO", user.toStdString(), pw.toStdString());
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
