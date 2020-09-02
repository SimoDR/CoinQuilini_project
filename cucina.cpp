#include "cucina.h"

float Cucina::_pesoCucina=1.45; // => 1.45^(numeroCommensali) punti ogni pasto

Cucina::Cucina(const std::string & nome, int tempoStimato, unsigned short numeroCommensali, Inquilino *incaricato, bool svolto): Faccenda(nome,incaricato,svolto, tempoStimato), _numeroCommensali(numeroCommensali) {}

Cucina* Cucina::clone() const {return new Cucina(*this);}

bool Cucina::posponi(const Data & d) const
{
    return Incarico::posponi(d) && _numeroCommensali>6;
}

string Cucina::generaNota() const
{
    return "CUCINA\n\n"+Incarico::generaNota()+"\n"+Faccenda::generaNota()+
            "\nPunteggio: "+std::to_string(calcolaPunteggio())+" punti \n"+
            "Numero commensali: "+std::to_string(_numeroCommensali)+"\n\n"+"Forza chef: mettiti ai fornelli!";
}
unsigned short int Cucina::calcolaPunteggio() const
{
    return controlloSoglia(std::pow(_pesoCucina,_numeroCommensali));
}

void Cucina::exportXml(QXmlStreamWriter & xmlOutput,string data) const
{
    xmlOutput.writeStartElement(QString::fromStdString("CUCINA"));
    Faccenda::exportXml(xmlOutput,data);
    xmlOutput.writeTextElement("numeroCommensali", QString::fromStdString(std::to_string(_numeroCommensali)));
    xmlOutput.writeEndElement();
}

std::string Cucina::getLabel() const {return "Cucina";}

void Cucina::importXml(QXmlStreamReader & xmlInput, vector<string> & parametri)
{
    Faccenda::importXml(xmlInput,parametri);

    string numeroCommensali;

    assignWithXml(xmlInput, "numeroCommensali", numeroCommensali);

    parametri[6]=numeroCommensali;
    parametri[1]="Cucina";

}
