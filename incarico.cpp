#include "incarico.h"
#include "inquilino.h"
#include<math.h>

unsigned short int Incarico::_sogliaMax=10; // max punteggio attribuibile a un incarico
unsigned short int Incarico::_sogliaMin=2;  // min punteggio attribuibile a un incarico

Incarico::Incarico(const std::string& nome, Inquilino *incaricato, bool svolto):
    _nome(nome),_incaricato(incaricato),_svolto(svolto) {}

Incarico::~Incarico() {}

void Incarico::setIncaricato(Inquilino * i)
{
    _incaricato = i;
}

void Incarico::setSvolto()
{
    _svolto=true;
}

void Incarico::setDataLimite(const Data &) {}

Inquilino *Incarico::getIncaricato() const
{
    return _incaricato;
}

bool Incarico::getSvolto() const
{
    return _svolto;
}

unsigned short int Incarico::controlloSoglia(int x)
{
    if (x > _sogliaMax) x = _sogliaMax;
    else if (x < _sogliaMin) x = _sogliaMin;
    return x;
}

bool Incarico::posponi (const Data& d) const
{
    return d > Data::unixDateToData(std::chrono::system_clock::now());
}

std::string Incarico::generaNota() const
{
    return "Nome: " + _nome + "\n" + "Incaricato: " + (_incaricato ? _incaricato->getNome() : "xxx" )
            + "\n" + "Stato: " + (_svolto ? "svolto" : "non svolto");
}

void Incarico::exportXml(QXmlStreamWriter & xmlOutput, string data) const
{
    xmlOutput.writeTextElement("data", QString::fromStdString(data));
    xmlOutput.writeTextElement("nome", QString::fromStdString(_nome));
    xmlOutput.writeTextElement("nomeIncaricato", QString::fromStdString(_incaricato->getNome()));
    xmlOutput.writeTextElement("svolto", _svolto ? "si" : "no");
}

void Incarico::importXml(QXmlStreamReader & xmlInput, vector<string> & parametri)
{
    string nome,incaricato,svolto,data;

    assignWithXml(xmlInput, "data", data);
    assignWithXml(xmlInput, "nome", nome);
    assignWithXml(xmlInput, "nomeIncaricato", incaricato);
    assignWithXml(xmlInput, "svolto", svolto);

    parametri[0]=nome;
    parametri[2]=incaricato;
    parametri[12]=svolto;
    parametri[10]=data;
}
