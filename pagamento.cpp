#include "pagamento.h"

double Pagamento::_pesoPagamento=30; // => l'incarico vale 1 punto ogni 30 euro di importo

void Pagamento::setImporto(const double& x){
    _importo=x;
}

Pagamento::~Pagamento() {}

string Pagamento::generaNota() const {
    string s1="L'importo di questa spesa è: ";
    string s2=" €";
    return s1+std::to_string(_importo)+s2;
}

unsigned short int Pagamento::calcolaPunteggio() const{
    unsigned short int p=_importo/_pesoPagamento;
    controlloSoglia(p);
    return p;
}
