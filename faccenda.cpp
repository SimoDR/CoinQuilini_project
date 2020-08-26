#include "faccenda.h"

unsigned short int Faccenda::_pesoFaccenda=60; // => 1 punto ogni 60 minuti

Faccenda::Faccenda(const std::string& nome, int tempoStimato, Inquilino *incaricato, bool svolto):
    Incarico(nome,incaricato,svolto), _tempoStimato(tempoStimato) {}

Faccenda::~Faccenda() {}

string Faccenda::generaNota() const {
    return "Il tempo per svolgere questo incarico è stimato in "+std::to_string(_tempoStimato)+" minuti";
}

void Faccenda::exportXml(QXmlStreamWriter & xmlOutput) const
{
    Incarico::exportXml(xmlOutput);
    xmlOutput.writeTextElement("tempoStimato", QString::fromStdString(std::to_string(_tempoStimato)));
}

void Faccenda::importXml(QXmlStreamReader & xmlInput, vector<string> & parametri)
{

    Incarico::importXml(xmlInput,parametri);
    string tempoStimato;

    assignWithXml(xmlInput, "tempoStimato", tempoStimato);

    parametri[4]=tempoStimato;

}

unsigned short int Faccenda::calcolaPunteggio() const{
    return controlloSoglia(_tempoStimato/_pesoFaccenda);
}
