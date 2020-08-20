#include "faccenda.h"

unsigned short int Faccenda::_pesoFaccenda=60; // => 1 punto ogni 60 minuti

Faccenda::~Faccenda() {}

string Faccenda::generaNota() const {
    string s1="Il tempo per svolgere questo incarico è stimato in ";
    string s2=" minuti";
    return s1+std::to_string(_tempoStimato)+s2;
}
unsigned short int Faccenda::calcolaPunteggio() const{
    return _tempoStimato/_pesoFaccenda;
}
