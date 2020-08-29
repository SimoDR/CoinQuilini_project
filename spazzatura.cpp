#include "spazzatura.h"

unsigned short int Spazzatura::_pesoSpazzatura=3; // => 3 punti ogni incarico spazzatura assolto

Spazzatura::Spazzatura(const std::string& nome, const std::string & cosaButtare, int tempoStimato, Inquilino *incaricato, bool svolto):
    Incarico(nome,incaricato,svolto), Faccenda(tempoStimato), _cosaButtare(cosaButtare) {}

Spazzatura* Spazzatura::clone() const {return new Spazzatura(*this);}

string Spazzatura::generaNota() const {
    return "SPAZZATURA\n\n"+Faccenda::generaNota()+"\nPunteggio: "+std::to_string(calcolaPunteggio())+" punti \n"+"Tipologia rifiuto: " + _cosaButtare+"\n\n"+"Liberiamoci di questa spazzatura!";
}

void Spazzatura::exportXml(QXmlStreamWriter &xmlOutput,string data) const
{
    xmlOutput.writeStartElement(QString::fromStdString("SPAZZATURA"));
    Faccenda::exportXml(xmlOutput,data);
    xmlOutput.writeTextElement("cosaButtare", QString::fromStdString(_cosaButtare));
    xmlOutput.writeEndElement();

}

void Spazzatura::importXml(QXmlStreamReader & xmlInput, vector<string> & parametri)
{
    Faccenda::importXml(xmlInput,parametri);

    string cosaButtare;
    assignWithXml(xmlInput, "cosaButtare", cosaButtare);

    parametri[13]=cosaButtare;
    parametri[1]="Spazzatura";

}

std::string Spazzatura::getLabel() const {return "Spazzatura";}

unsigned short int Spazzatura::calcolaPunteggio() const{
    return controlloSoglia(_pesoSpazzatura);
}
