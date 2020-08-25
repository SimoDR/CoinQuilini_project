#include "spesa.h"

unsigned short int Spesa::_pesoSpesa=10; // => 1 punto ogni 10 articoli comprati
vector<string> Spesa::_listaSpesa;

Spesa* Spesa::clone() const {return new Spesa(*this);}

bool Spesa::posponi(const Data d) const
{
    return true;
}

string Spesa::generaNota() const
{
    if ( ! getSvolto() ){

        //non smart da rivedere
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

unsigned short int Spesa::calcolaPunteggio() const
{
    if (_numeroArticoli<_pesoSpesa)
    {
        return Pagamento::calcolaPunteggio();
    }
    else
    {
        unsigned short int p=_numeroArticoli/_pesoSpesa;
        controlloSoglia(p);
        return p;
    }
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
