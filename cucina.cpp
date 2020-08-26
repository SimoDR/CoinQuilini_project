#include "cucina.h"

double Cucina::_pesoCucina=1.5; // => 1.5^(numeroCommensali) punti ogni pasto

Cucina::Cucina(std::string nome, int tempoStimato, unsigned short numeroCommensali, Inquilino *incaricato, bool svolto):
    Faccenda(nome,tempoStimato,incaricato,svolto), _numeroCommensali(numeroCommensali) {}

Cucina* Cucina::clone() const {return new Cucina(*this);}

string Cucina::generaNota() const {
    string s1="Forza chef! Devi cucinare per ";
    string s2=" persone!";
    return s1+std::to_string(_numeroCommensali)+s2;
}
unsigned short int Cucina::calcolaPunteggio() const{
    unsigned short int p=std::pow(_pesoCucina,_numeroCommensali);
    controlloSoglia(p);
    return p;
}

void Cucina::exportXml(QXmlStreamWriter & xmlOutput) const
{
    xmlOutput.writeStartElement(QString::fromStdString("CUCINA"));
    Faccenda::exportXml(xmlOutput);
    xmlOutput.writeTextElement("numeroCommensali", QString::fromStdString(std::to_string(_numeroCommensali)));
    xmlOutput.writeEndElement();
}
