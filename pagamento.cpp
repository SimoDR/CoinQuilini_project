#include "pagamento.h"

double Pagamento::_pesoPagamento=30; // => l'incarico vale 1 punto ogni 30 euro di importo

Pagamento::Pagamento(const std::string& nome, float importo, Inquilino *incaricato, bool svolto):
    Incarico(nome,incaricato,svolto),_importo(importo) {}

void Pagamento::setImporto(double x){
    _importo=x;
}

double Pagamento::getImporto() const
{
    return _importo;
}

Pagamento::~Pagamento() {}

string Pagamento::generaNota() const {
    return "L'importo di questa spesa è: "+std::to_string(_importo)+" €";
}

unsigned short int Pagamento::calcolaPunteggio() const{
    return controlloSoglia(_importo/_pesoPagamento);
}

void Pagamento::exportXml(QXmlStreamWriter & xmlOutput) const
{
    Incarico::exportXml(xmlOutput);
    xmlOutput.writeTextElement("importo", QString::fromStdString(std::to_string(_importo)));
}

void Pagamento::importXml(QXmlStreamReader & xmlInput, vector<string> & parametri)
{
    Incarico::importXml(xmlInput,parametri);

    string importo;

    assignWithXml(xmlInput, "importo", importo);

    parametri[8]=importo;

}
