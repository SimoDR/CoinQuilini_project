#include "controller.h"
#include "login.h"




Controller::Controller(QObject *parent) : QObject(parent), _listaInquilini(ListaInquilini()), _calendario(Data::unixDateToData(std::chrono::system_clock::now()),_listaInquilini.getInquilini())
{
    buildLogin();
}



bool Controller::login(const QString & user, const QString & pw)
{
    if (_listaInquilini.checkCredenziali(user.toStdString(), pw.toStdString()))
    {
        Mainwindow * mainwindow= new Mainwindow(nullptr, this, user);
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
 * 12- svolto
 * 13- CosaButtare
 *
 *
 * Se l'incarico da creare non prevede uno dei campi, questi verranno indicati con il carattere speciale "\0" e quindi ignorati
 * */


void Controller::creaNuovoIncarico(vector<std::string> parametri)
{
    _calendario.creaNuovoIncarico(parametri,false);
}



void Controller::rimuoviIncarico(const Data &dataIncarico, int indiceIncarico)
{
    _calendario.remove(_calendario.trovaIncarico(dataIncarico,indiceIncarico),dataIncarico);
}

void Controller::posponiIncarico(const Data &dataIncarico, int indiceIncarico, unsigned int quantoPosporre, unsigned int posizioneInquilinoRichiedente) //DA GESTIRE PUNTEGGI??
{
    Inquilino * richiedente=_listaInquilini.getInquilino(posizioneInquilinoRichiedente);
    if(richiedente->puoPosporre())
    {

        _calendario.posponiIncarico(_calendario.trovaIncarico(dataIncarico,indiceIncarico),quantoPosporre,dataIncarico);
    }
    else
    {
        //MESSAGGIO: NON PUOI POSPORRE!
        showMessage(QString::fromStdString("Spiacente: non hai i requisiti sufficienti per posporre questo incarico!"));

    }

}

void Controller::riassegnaIncarico(const Data &dataIncarico, int indiceIncarico, string nomeInquilino)
{
    Incarico * daRiassegnare=_calendario.trovaIncarico(dataIncarico,indiceIncarico);
    Inquilino * nuovoIncaricato=_listaInquilini.getInquilino(nomeInquilino);
    daRiassegnare->setIncaricato(nuovoIncaricato);
}

void Controller::setIncaricoSvolto(const Data & dataIncarico, int indiceIncarico)
{
    Incarico * svolto=_calendario.trovaIncarico(dataIncarico,indiceIncarico);
    svolto->setSvolto();
}

void Controller::incrementaGiorno()
{
    _calendario.checkIncarichiSvolti(false);
    _calendario.incrementaData();

}

void Controller::checkIncarichiSvoltiIeri()
{
    _calendario.checkIncarichiSvolti(true);
}

vector<std::string> Controller::incarichiGiorno(string dataGiorno, vector<std::string> & incaricati)
{
    vector<string> tipiIncarichi;
    Data giorno(dataGiorno);
    _calendario.incarichiGiorno(giorno,tipiIncarichi,incaricati);
    return tipiIncarichi;
}






vector<string> Controller::getInquilini()
{
    return _listaInquilini.inquilini();
}

void Controller::rimuoviInquilino(unsigned int pos)
{
    _calendario.rimuoviInquilino(pos);
    _listaInquilini.rimuovi(pos);


}

vector<std::string> Controller::getInquilinoPos(unsigned int pos)
{
    return _listaInquilini.getCredenziali(pos);
}

void Controller::aggiungiInquilino(const QString & user, const QString & pw)
{
    _listaInquilini.creaInserisci("INQUILINO", user.toStdString(), pw.toStdString());
    _calendario.aggiungiAlBuffer(_listaInquilini.getInquilino(user.toStdString()));

}

void Controller::modificaInquilino(const QString &user, const QString & pw, unsigned int pos)
{
    _listaInquilini.modifica(user.toStdString(), pw.toStdString(), pos);
    //da sistemare per _calendario? Forse non serve
}

void Controller::checkAdmin(unsigned int pos)
{
    _listaInquilini.checkAdmin(pos);
}

unsigned short Controller::isAdmin(const std::string & user) const
{
    return _listaInquilini.isAdmin(user);
}

void Controller::buildLogin()
{
    Login * login(new Login(this));
    login->show();
}

void Controller::buildNota(const QDate & data, unsigned int pos)
{
    Incarico* i= _calendario.trovaIncarico((data.toString("d/M/yyyy")).toStdString(),pos);
    showMessage(QString::fromStdString(i->generaNota()));
}
