#ifndef SPAZZATURA_H
#define SPAZZATURA_H

#include "faccenda.h"

enum TipologiaRifiuto{secco, umido, plastica, carta, verde, vetro};

class Spazzatura: public Faccenda
{
private:
    static unsigned short int _pesoSpazzatura;
    TipologiaRifiuto _cosaButtare;

public:
    //Cucina(string nome,int tempoStimato,Inquilino * incaricato=nullptr,bool svolto=false):
    //	Faccenda(nome,tempoStimato,incaricato,svolto) {}
    virtual ~Spazzatura() {}
    virtual Spazzatura* clone() const;
    virtual string generaNota() const;
    // virtual import
    virtual unsigned short int calcolaPunteggio() const;
};

#endif // SPAZZATURA_H
