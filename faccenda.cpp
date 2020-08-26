#include "faccenda.h"

unsigned short int Faccenda::_pesoFaccenda=60; // => 1 punto ogni 60 minuti

Faccenda::Faccenda(int tempoStimato): _tempoStimato(tempoStimato) {}

Faccenda::~Faccenda() {}

string Faccenda::generaNota() const {
    return "Il tempo per svolgere questo incarico è stimato in "+std::to_string(_tempoStimato)+" minuti";
}

void Faccenda::exportXml(QXmlStreamWriter & xmlOutput) const
{
    Incarico::exportXml(xmlOutput);
    xmlOutput.writeTextElement("tempoStimato", QString::fromStdString(std::to_string(_tempoStimato)));
}

unsigned short int Faccenda::calcolaPunteggio() const{
    return controlloSoglia(_tempoStimato/_pesoFaccenda);
}
