#include "controller.h"


Controller::Controller(QObject *parent) : QObject(parent), _listaInquilini(ListaInquilini()), _calendario(Data("20/08/2020"),_listaInquilini.getInquilini()) {}
//DA METTERE DATA ODIERNA

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
 * 12- svolto
 *
 *
 * Se l'incarico da creare non prevede uno dei campi, questi verranno indicati con il carattere speciale "\0" e quindi ignorati
 * */


void Controller::creaNuovoIncarico(vector<std::string> parametri)
{

    string nomeIncarico="\0";
    if(parametri[0]!="\0") nomeIncarico=parametri[0];

    string tipoIncarico="\0";
    if(parametri[1]!="\0") tipoIncarico=parametri[1];

    string nomeIncaricato="\0";
    if(parametri[2]!="\0") nomeIncaricato=parametri[2];

    int cadenzaIncarico=0;
    if(parametri[3]!="\0") cadenzaIncarico=std::stoi(parametri[3]);

    int tempoStimato=0;
    if(parametri[4]!="\0") tempoStimato=std::stoi(parametri[4]);

    unsigned short int stanzeDaPulire;
    if(parametri[5]!="\0") stanzeDaPulire=std::stoi(parametri[5]);


    unsigned short int numeroCommensali;
    if(parametri[6]!="\0") numeroCommensali=std::stoi(parametri[6]);

    unsigned short int numeroArticoli;
    if(parametri[7]!="\0") numeroArticoli=std::stoi(parametri[7]);

    int importo=0;
    if(parametri[8]!="\0") importo=std::stoi(parametri[8]);

    Data dataLimite;
    if(parametri[9]!="\0") dataLimite=parametri[9];

    Data dataInizio;
    if(parametri[10]!="\0") dataInizio=parametri[10];

    try{
    if(dataInizio<_calendario.getDataDiOggi())
        throw new std::invalid_argument("Attenzione! La data di inserimento dell'incarico dev'essere successiva alla data di oggi");
    }
    catch (std::invalid_argument *e)
    {
       showMessage(QString::fromStdString(e->what()));
    }

    int numeroOccorrenze=1;
    if(parametri[11]!="\0") numeroOccorrenze=std::stoi(parametri[11]);

    try{
    if(numeroOccorrenze==0)
        throw new std::invalid_argument("Attenzione! Le occorrenze devono essere almeno una (incarico semplice)");
    }
    catch (std::invalid_argument *e)
    {
       showMessage(QString::fromStdString(e->what()));
    }


    bool svolto=false;
    if(parametri[12]!="\0")
    {
        if(parametri[12]=="si")
            svolto=true;
        else svolto=false;
    }


    Incarico * i=nullptr;

    if (tipoIncarico=="Pulizia")
        i=new Pulizia(nomeIncarico,tempoStimato,stanzeDaPulire);
    else if(tipoIncarico=="Spesa")
        i=new Spesa(nomeIncarico,importo,tempoStimato,numeroArticoli);
    else if(tipoIncarico=="Spazzatura")
        i=new Spazzatura(nomeIncarico,tempoStimato);
    else if(tipoIncarico=="Cucina")
        i=new Cucina(nomeIncarico,tempoStimato,numeroCommensali);
    else if(tipoIncarico=="Bolletta")
        i=new Bolletta(nomeIncarico,importo,dataLimite); //partecipanti????

    if(numeroOccorrenze==1 && nomeIncaricato!="\0") //assegnazione manuale dell'incaricato essendo evento singolo
        i->setIncaricato(_listaInquilini.getInquilino(nomeIncaricato));
    if(svolto) //per l'import
        i->setSvolto();

    _calendario.insert(i,dataInizio,numeroOccorrenze,cadenzaIncarico);

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
    _calendario.checkIncarichiSvolti();
    _calendario.incrementaData();

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
