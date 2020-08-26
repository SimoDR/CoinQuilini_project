#include "cucina.h"

double Cucina::_pesoCucina=1.5; // => 1.5^(numeroCommensali) punti ogni pasto

Cucina::Cucina(const std::string & nome, int tempoStimato, unsigned short numeroCommensali, Inquilino *incaricato, bool svolto):
    Incarico(nome,incaricato,svolto), Faccenda(tempoStimato), _numeroCommensali(numeroCommensali) {}

Cucina* Cucina::clone() const {return new Cucina(*this);}

string Cucina::generaNota() const {
    return "Forza chef! Devi cucinare per "+std::to_string(_numeroCommensali)+" persone!";
}
unsigned short int Cucina::calcolaPunteggio() const{
    return controlloSoglia(std::pow(_pesoCucina,_numeroCommensali));
}

void Cucina::exportXml(QXmlStreamWriter & xmlOutput) const
{
    xmlOutput.writeStartElement(QString::fromStdString("CUCINA"));
    Faccenda::exportXml(xmlOutput);
    xmlOutput.writeTextElement("numeroCommensali", QString::fromStdString(std::to_string(_numeroCommensali)));
    xmlOutput.writeEndElement();
}
