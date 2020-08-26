#include "incarico.h"
#include "inquilino.h"
#include<math.h>

// Implementazione Incarico

Incarico::Incarico(const std::string& nome, Inquilino *incaricato, bool svolto):
    _nome(nome),_incaricato(incaricato),_svolto(svolto) {}

unsigned short int Incarico::_sogliaMax=10; // max punteggio attribuibile a un incarico
unsigned short int Incarico::_sogliaMin=1;  // min punteggio attribuibile a un incarico

unsigned short int Incarico::controlloSoglia(int x){
    if (x > _sogliaMax) x = _sogliaMax;
    else if (x < _sogliaMin) x = _sogliaMin;
    return x;
}

void Incarico::setNome(const string& s){
    _nome=s;
}

void Incarico::setIncaricato(Inquilino * i){
    _incaricato = i;
}

Inquilino *Incarico::getIncaricato() const
{
    return _incaricato;
}

bool Incarico::getSvolto() const{
    return _svolto;
}

void Incarico::setSvolto(){
    _svolto=true;
}

Incarico::~Incarico() {}

bool Incarico::posponi (const Data& d) const{
    return false; //un incarico non è posponibile di default
}

std::string Incarico::generaNota() const
//debug-feature simbolo di separazione ha bisogno di essere salvato in un campo statico (e non essere usato)
{
    return _nome + "//" + (_incaricato ? _incaricato->getNome() : "xxx" ) + "//" + (_svolto ? "Y" : "N") ;
}

void Incarico::exportXml(QXmlStreamWriter & xmlOutput) const
{
    xmlOutput.writeTextElement("nome", QString::fromStdString(_nome));
    xmlOutput.writeTextElement("nomeIncaricato", QString::fromStdString(_incaricato->getNome()));
    xmlOutput.writeTextElement("svolto", _svolto ? "si" : "no");
}

void Incarico::importXml(QXmlStreamReader & xmlInput, vector<string> & parametri)
{
    string nome,incaricato,svolto;

    assignWithXml(xmlInput, "nome", nome);
    assignWithXml(xmlInput, "nomeIncaricato", incaricato);
    assignWithXml(xmlInput, "svolto", svolto);

    parametri[0]=nome;
    parametri[1]=incaricato;
    parametri[12]=incaricato;
}



