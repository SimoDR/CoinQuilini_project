#include "spazzatura.h"

unsigned short int Spazzatura::_pesoSpazzatura=3; // => 3 punti ogni incarico spazzatura assolto

Spazzatura* Spazzatura::clone() const {return new Spazzatura(*this);}

string Spazzatura::generaNota() const {
    string s1="Oggi tocca a ";
    return s1;
    //return s1+_cosaButtare;
}

unsigned short int Spazzatura::calcolaPunteggio() const{
    unsigned short int p=_pesoSpazzatura;
    controlloSoglia(p);
    return p;
}
