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
 * 7- numeroArticoli
 * 8- Importo
 * 9- DataLimite
 * 10- DataInizio
 * 11- numeroOccorrenze
 * [11..parametri.size] -Partecipanti
 * ..
 *
 *
 * */


void Controller::creaNuovoIncarico(vector<std::string> parametri)
{
    string nomeIncarico=parametri[0];
    string tipoIncarico=parametri[1];
    string nomeIncaricato=parametri[2]; //DA SISTEMARE
    int cadenzaIncarico=std::stoi(parametri[3]);
    int tempoStimato=std::stoi(parametri[4]);
    unsigned short int stanzeDaPulire=std::stoi(parametri[5]);
    unsigned short int numeroCommensali=std::stoi(parametri[6]);
    unsigned short int numeroArticoli=std::stoi(parametri[7]);
    int importo=std::stoi(parametri[8]);
    Data * dataLimite=new Data(parametri[9]);
    Data * dataInizio=new Data(parametri[10]);
    int numeroOccorrenze=std::stoi(parametri[11]);

    for(std::vector<string>::size_type i=12;i<parametri.size();i++)
    {

    }

    Incarico * i=nullptr;

    if (tipoIncarico=="Pulizia")
        i=new Pulizia(nomeIncarico,stanzeDaPulire);
    else if(tipoIncarico=="Spesa")
        i=new Spesa(nomeIncarico,importo,tempoStimato,numeroArticoli);
    else if(tipoIncarico=="Spazzatura")
        i=new Spazzatura(nomeIncarico,tempoStimato);
    else if(tipoIncarico=="Cucina")
        i=new Cucina(nomeIncarico,tempoStimato,numeroCommensali);
    else if(tipoIncarico=="Bolletta")
        i=new Bolletta(nomeIncarico,importo,dataLimite); //partecipanti


    bool successo=insert(i,dataInizio,numeroOccorrenze,cadenzaIncarico);

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
