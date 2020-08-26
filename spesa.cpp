#include "spesa.h"

unsigned short int Spesa::_pesoSpesa=10; // => 1 punto ogni 10 articoli comprati
vector<string> Spesa::_listaSpesa;

Spesa::Spesa(const std::string& nome, double importo, int tempoStimato, unsigned short numeroArticoli, Inquilino *incaricato, bool svolto):
    Incarico(nome,incaricato,svolto), Pagamento(importo), Faccenda(tempoStimato), _numeroArticoli(numeroArticoli) {}

Spesa* Spesa::clone() const {return new Spesa(*this);}

bool Spesa::posponi(const Data& d) const
{
    return true;
}

string Spesa::generaNota() const
{
    if ( ! getSvolto() ){

        //debug: non smart da rivedere
        string elenco="";
        for (vector<string>::const_iterator cit = _listaSpesa.begin() ; cit != _listaSpesa.end(); cit++){
            elenco+=*cit+" ";
        }
        return elenco;
    }
    else{
        return "Spesa di "+std::to_string(_numeroArticoli)+" articoli";
    }
}

void Spesa::exportXml(QXmlStreamWriter & xmlOutput) const
{
    xmlOutput.writeStartElement(QString::fromStdString("SPESA"));
    Faccenda::exportXml(xmlOutput);
    xmlOutput.writeTextElement("numeroArticoli", QString::fromStdString(std::to_string(_numeroArticoli)));
    xmlOutput.writeEndElement();
}

//ricordarsi di aggiornare _articoli quando viene conclusa una spesa


unsigned short int Spesa::calcolaPunteggio() const
{
    return controlloSoglia(_numeroArticoli/_pesoSpesa);
}

void Spesa::setArticoli()
{
    _numeroArticoli=_listaSpesa.size();
}

vector<string> Spesa::getListaSpesa() const
{
    return _listaSpesa;
}

void Spesa::aggiungiListaSpesa(const std::string & x)
{
    _listaSpesa.push_back(x);
    setArticoli();
}

void Spesa::rimuoviListaSpesa(const string& x)
{
    bool tolto=false;
    for (auto it = _listaSpesa.begin() ; it != _listaSpesa.end() && !tolto; it++){
        if(*it==x){
            _listaSpesa.erase(it);
            tolto=true;
            setArticoli();
        }
    }
}

void Spesa::svuotaListaSpesa()
{
    _listaSpesa.clear();
}
