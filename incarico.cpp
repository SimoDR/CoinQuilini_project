#include "incarico.h"
#include "inquilino.h"
#include<math.h>

// Implementazione Incarico

unsigned int Incarico::_sogliaMax=10; // max punteggio attribuibile a un incarico

void Incarico::controlloSoglia(unsigned short int & x) const{
    if (x >_sogliaMax) x = _sogliaMax;
}
void Incarico::setNome(const string& s){
    _nome=s;
}

void Incarico::setIncaricato(Inquilino * i){
    _incaricato = i;
}

Inquilino *Incarico::getIncaricato() const
{
    return _incaricato;
}

bool Incarico::getSvolto() const{
    return _svolto;
}

void Incarico::setSvolto(){
    _svolto=true;
}

Incarico::~Incarico() {}

bool Incarico::posponi (const Data d) const{
    return false; //un incarico non è posponibile di default
}
