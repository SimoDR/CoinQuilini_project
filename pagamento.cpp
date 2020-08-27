#include "pagamento.h"

unsigned short int Pagamento::_pesoPagamento=30; // => l'incarico vale 1 punto ogni 30 euro di importo

Pagamento::Pagamento(float importo): _importo(importo) {}

void Pagamento::setImporto(double x){
    _importo=x;
}

double Pagamento::getImporto() const
{
    return _importo;
}

Pagamento::~Pagamento() {}

string Pagamento::generaNota() const {
    return Incarico::generaNota()+"//"+std::to_string(_importo);
}

unsigned short int Pagamento::calcolaPunteggio() const{
    return controlloSoglia(_importo/_pesoPagamento);
}

void Pagamento::exportXml(QXmlStreamWriter & xmlOutput,string data) const
{
    Incarico::exportXml(xmlOutput,data);
    xmlOutput.writeTextElement("importo", QString::fromStdString(std::to_string(_importo)));
}

void Pagamento::importXml(QXmlStreamReader & xmlInput, vector<string> & parametri)
{
    Incarico::importXml(xmlInput,parametri);

    string importo;

    assignWithXml(xmlInput, "importo", importo);

    parametri[8]=importo;

}
