#include "spazzatura.h"

unsigned short int Spazzatura::_pesoSpazzatura=3; // => 3 punti ogni incarico spazzatura assolto

Spazzatura::Spazzatura(const std::string& nome, std::string cosaButtare, int tempoStimato, Inquilino *incaricato, bool svolto):
    Incarico(nome,incaricato,svolto), Faccenda(tempoStimato), _cosaButtare(cosaButtare) {}

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
    return controlloSoglia(_pesoSpazzatura);
}
