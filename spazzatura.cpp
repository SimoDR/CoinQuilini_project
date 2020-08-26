#include "spazzatura.h"

unsigned short int Spazzatura::_pesoSpazzatura=3; // => 3 punti ogni incarico spazzatura assolto

Spazzatura::Spazzatura(std::string nome, std::string cosaButtare, int tempoStimato, Inquilino *incaricato, bool svolto):
    Faccenda(nome,tempoStimato,incaricato,svolto), _cosaButtare(cosaButtare) {}

Spazzatura* Spazzatura::clone() const {return new Spazzatura(*this);}

string Spazzatura::generaNota() const {
    return "Oggi tocca a " + _cosaButtare;
}

void Spazzatura::exportXml(QXmlStreamWriter &xmlOutput) const
{
    xmlOutput.writeStartElement(QString::fromStdString("SPAZZATURA"));
    Faccenda::exportXml(xmlOutput);
    xmlOutput.writeTextElement("pesoSpazzatura", QString::fromStdString(std::to_string(_pesoSpazzatura)));
    xmlOutput.writeEndElement();

}

unsigned short int Spazzatura::calcolaPunteggio() const{
    unsigned short int p=_pesoSpazzatura;
    controlloSoglia(p);
    return p;
}
