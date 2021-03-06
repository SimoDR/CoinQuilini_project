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
        _mainwindow= new Mainwindow(nullptr, this, user);
        _mainwindow->show();
        checkIncarichiSvoltiPassato();
        return true;
    }
    //altrimenti ritorna messaggio di errore

    else {
        showMessage("Attenzione! Utente o password errati");
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



void Controller::rimuoviIncarico(const Data &dataIncarico, unsigned int indiceIncarico)
{
    _calendario.remove(dataIncarico,indiceIncarico);
}



void Controller::posponiIncarico(const Data &dataIncarico, unsigned int indiceIncarico, unsigned int quantoPosporre, const std::string &inquilinoRichiedente) //DA GESTIRE PUNTEGGI??
{
    if(dataIncarico<_calendario.getDataDiOggi())
        showMessage("Attenzione! Non è possibile posporre un incarico passato");
    else {
        Inquilino * richiedente=_listaInquilini.getInquilino(inquilinoRichiedente);
        if(richiedente->puoPosporre())
        {
            _calendario.posponiIncaricoCalendario(indiceIncarico,quantoPosporre,dataIncarico);
        }
        else
        {
            //MESSAGGIO: NON PUOI POSPORRE!
            showMessage(QString::fromStdString("Spiacente: non hai i requisiti sufficienti per posporre questo incarico!"));
        }
    }
}



void Controller::riassegnaIncarico(const Data & dataIncarico, unsigned int indiceIncarico, const string & nomeInquilino)
{
    if(dataIncarico<_calendario.getDataDiOggi())
        showMessage("Attenzione! Non è possibile riassegnare un incarico passato");
    else
    {
        Incarico * daRiassegnare=_calendario.trovaIncarico(dataIncarico,indiceIncarico);

        if(daRiassegnare->getSvolto())
            showMessage("Attenzione! Non è possibile riassegnare un incarico già svolto");
        else
        {
            Inquilino * nuovoIncaricato=_listaInquilini.getInquilino(nomeInquilino);
            daRiassegnare->setIncaricato(nuovoIncaricato);
            showSuccess("Incarico riassegnato con successo a "+QString::fromStdString(nuovoIncaricato->getNome()));

        }
    }
}



void Controller::setIncaricoSvolto(const Data & dataIncarico, unsigned int indiceIncarico)
{
    if(dataIncarico<_calendario.getDataDiOggi())
        showMessage("Attenzione! L'incarico è già stato svolto");
    else {
        Incarico * svolto=_calendario.trovaIncarico(dataIncarico,indiceIncarico);

        if(svolto->getSvolto())
            showMessage("Attenzione! L'incarico è già stato svolto");
        else {
            showSuccess("Incarico impostato come svolto");
            // aggiornamento situazione contabile
            Pagamento * pagamento=dynamic_cast<Pagamento*>(svolto);
            if (pagamento){
                // generazione di credito per l'incaricato
                ( pagamento->getIncaricato() )-> setCD(pagamento->getImporto());
                // generazione di debito per tutti gli inquilini
                _listaInquilini.dividiSpese(pagamento->getImporto());
            }

            // aggiornamento punteggi
            svolto->getIncaricato()->setPunteggio( (*svolto).calcolaPunteggio() );

            // incarico segnato come svolto
            svolto->setSvolto();
            //aggiustare soldi
            //aggiustare punteggi
        }
    }
}

void Controller::incrementaGiorno()
{
    _calendario.checkIncarichiSvolti();
    _calendario.incrementaData();

}



void Controller::checkIncarichiSvoltiPassato()
{
    _calendario.checkIncarichiSvoltiPassato();
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
    login->setAttribute(Qt::WA_DeleteOnClose);
    login->setFixedSize(login->sizeHint());
    login->show();
}



std::string Controller::showCdCasa() const
{
    return _listaInquilini.getCdCasa();
}



string Controller::showPunteggio(const QString & nome) const
{
    return (_listaInquilini.getInquilino(nome.toStdString()) ) -> showPunteggio();
}



std::string Controller::showCreDeb(const QString & nome) const
{
    return (_listaInquilini.getInquilino(nome.toStdString()) ) -> showCreDeb();
}



void Controller::buildNota(const QDate & data, unsigned int pos)
{
    Incarico* i= _calendario.trovaIncarico((data.toString("d/M/yyyy")).toStdString(),pos,true);
    showSuccess(QString::fromStdString(i->generaNota()));
}
