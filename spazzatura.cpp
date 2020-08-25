#include "spazzatura.h"

unsigned short int Spazzatura::_pesoSpazzatura=3; // => 3 punti ogni incarico spazzatura assolto

Spazzatura* Spazzatura::clone() const {return new Spazzatura(*this);}

string Spazzatura::generaNota() const {
    string s1="Oggi tocca a ";
    return s1;
    //return s1+_cosaButtare;
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
