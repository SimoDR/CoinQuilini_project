#include "faccenda.h"

unsigned short int Faccenda::_pesoFaccenda=60; // => 1 punto ogni 60 minuti

Faccenda::Faccenda(std::string nome, int tempoStimato, Inquilino *incaricato, bool svolto):
    Incarico(nome,incaricato,svolto), _tempoStimato(tempoStimato) {}

Faccenda::~Faccenda() {}

string Faccenda::generaNota() const {
    string s1="Il tempo per svolgere questo incarico è stimato in ";
    string s2=" minuti";
    return s1+std::to_string(_tempoStimato)+s2;
}

void Faccenda::exportXml(QXmlStreamWriter & xmlOutput) const
{
    Incarico::exportXml(xmlOutput);
    xmlOutput.writeTextElement("tempoStimato", QString::fromStdString(std::to_string(_tempoStimato)));
}

unsigned short int Faccenda::calcolaPunteggio() const{
    return _tempoStimato/_pesoFaccenda;
}
