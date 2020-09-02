#include "faccenda.h"

unsigned short int Faccenda::_pesoFaccenda=60; // => 1 punto ogni 60 minuti di tempo stimato per svolgere l'incarico

Faccenda::Faccenda(int tempoStimato): _tempoStimato(tempoStimato) {}

Faccenda::~Faccenda() {}

string Faccenda::generaNota() const {
    return  "Tempo stimato: " + std::to_string(_tempoStimato) +
            (_tempoStimato > 1 ? +" minuti" : " minuto");
}

void Faccenda::exportXml(QXmlStreamWriter & xmlOutput,string data) const
{
    Incarico::exportXml(xmlOutput,data);
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
