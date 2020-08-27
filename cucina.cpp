#include "cucina.h"

double Cucina::_pesoCucina=1.5; // => 1.5^(numeroCommensali) punti ogni pasto

Cucina::Cucina(const std::string & nome, int tempoStimato, unsigned short numeroCommensali, Inquilino *incaricato, bool svolto):
    Incarico(nome,incaricato,svolto), Faccenda(tempoStimato), _numeroCommensali(numeroCommensali) {}

Cucina* Cucina::clone() const {return new Cucina(*this);}

string Cucina::generaNota() const {
    return "||CUCINA//"+Faccenda::generaNota()+"//"+std::to_string(_numeroCommensali)+"//"+"Forza chef: mettiti ai fornelli!";
}
unsigned short int Cucina::calcolaPunteggio() const{
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
