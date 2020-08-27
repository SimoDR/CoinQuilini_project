#include "pulizia.h"

unsigned short int Pulizia::_pesoPulizia=3; // => 3 punti ogni stanza pulita

Pulizia::Pulizia(const std::string& nome, int tempoStimato, unsigned short stanzeDaPulire, Inquilino *incaricato, bool svolto):
    Incarico(nome,incaricato,svolto), Faccenda(tempoStimato), _stanzeDaPulire(stanzeDaPulire) {}

Pulizia* Pulizia::clone() const {return new Pulizia(*this);}

bool Pulizia::posponi(const Data& d) const{
    return true;
}

string Pulizia::generaNota() const {
    return "||PULIZIA//"+Faccenda::generaNota()+"//"+std::to_string(_stanzeDaPulire)+"//"+"Cenerentola tocca a te!";
}
unsigned short int Pulizia::calcolaPunteggio() const{
    return controlloSoglia(_stanzeDaPulire*_pesoPulizia);
}

void Pulizia::exportXml(QXmlStreamWriter & xmlOutput,string data) const
{
    xmlOutput.writeStartElement(QString::fromStdString("PULIZIA"));
    Faccenda::exportXml(xmlOutput,data);
    xmlOutput.writeTextElement("stanzeDaPulire", QString::fromStdString(std::to_string(_stanzeDaPulire)));
    xmlOutput.writeEndElement();
}

std::string Pulizia::getLabel() const {return "Pulizia";}

void Pulizia::importXml(QXmlStreamReader & xmlInput, vector<string> & parametri)
{
    Faccenda::importXml(xmlInput,parametri);

    string stanzeDaPulire;

    assignWithXml(xmlInput, "stanzeDaPulire", stanzeDaPulire);

    parametri[5]=stanzeDaPulire;
    parametri[1]="Pulizia";

}
