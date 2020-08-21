#include "pulizia.h"

unsigned short int Pulizia::_pesoPulizia=3; // => 3 punti ogni stanza pulita

Pulizia* Pulizia::clone() const {return new Pulizia(*this);}

bool Pulizia::posponi(const Data d) const{
    return true;
}

string Pulizia::generaNota() const {
    string s1="Devi pulire ";
    string s2=" stanze!";
    return s1+std::to_string(_stanzeDaPulire)+s2;
}
unsigned short int Pulizia::calcolaPunteggio() const{
    unsigned short int p=_stanzeDaPulire*_pesoPulizia;
    controlloSoglia(p);
    return p;
}

