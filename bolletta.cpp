#include "bolletta.h"

Bolletta::Bolletta(std::string nome, double importo, const Data &dataLimite, Inquilino *incaricato, bool svolto):
    Pagamento(nome,importo,incaricato,svolto), _dataLimite(dataLimite) {}

Bolletta* Bolletta::clone() const {return new Bolletta(*this);}

bool Bolletta::posponi(const Data d) const
{
    return d < _dataLimite ? true : false;
}

void Bolletta::exportXml(QXmlStreamWriter & xmlOutput) const
{
    xmlOutput.writeStartElement(QString::fromStdString("BOLLETTA"));
    Pagamento::exportXml(xmlOutput);
    xmlOutput.writeTextElement("dataLimite", QString::fromStdString(_dataLimite.dataToString()));
    xmlOutput.writeEndElement();
}
