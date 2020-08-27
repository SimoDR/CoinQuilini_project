#include "bolletta.h"

Bolletta::Bolletta(const std::string & nome, float importo, const Data &dataLimite, Inquilino *incaricato, bool svolto):
    Incarico(nome,incaricato,svolto), Pagamento(importo), _dataLimite(dataLimite) {}

void Bolletta::setDataLimite(const Data& dataLimite)
{
    _dataLimite=dataLimite;
}

Bolletta* Bolletta::clone() const {return new Bolletta(*this);}

bool Bolletta::posponi(const Data& d) const
{
    return d < _dataLimite ? true : false;
}

std::string Bolletta::getLabel() const {return "Bolletta";}

void Bolletta::exportXml(QXmlStreamWriter & xmlOutput,string data) const
{
    xmlOutput.writeStartElement(QString::fromStdString("BOLLETTA"));
    Pagamento::exportXml(xmlOutput,data);
    xmlOutput.writeTextElement("dataLimite", QString::fromStdString(_dataLimite.dataToString()));
    xmlOutput.writeEndElement();
}

std::string Bolletta::generaNota() const
{
    return "||BOLLETTA//"
            + Pagamento::generaNota() + "//" + _dataLimite.dataToString()
            + "//" + "A pagare e morire si fa sempre in tempo!";
}

void Bolletta::importXml(QXmlStreamReader & xmlInput, vector<string> & parametri)
{
    Pagamento::importXml(xmlInput,parametri);

    string dataLimite;

    assignWithXml(xmlInput, "dataLimite", dataLimite);

    Data diPartenza=parametri[10];
    Data daRaggiungere(dataLimite);
    int scostamento=Data(diPartenza).differenza(dataLimite);

    parametri[9]=std::to_string(scostamento);
    parametri[1]="Bolletta";
}
