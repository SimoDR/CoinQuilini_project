#ifndef PULIZIA_H
#define PULIZIA_H

#include "faccenda.h"

class Pulizia: public Faccenda
{
private:
    unsigned short int _stanzeDaPulire; //eccezioni: limitare numero delle camere
    static unsigned short int _pesoPulizia;
public:
    //Pulizia(string nome,int tempoStimato,unsigned short int stanzeDaPulire,Inquilino * incaricato=nullptr,bool svolto=false):
    //	Faccenda(nome,tempoStimato,incaricato,svolto), _stanzeDaPulire(stanzeDaPulire) {}
    virtual ~Pulizia() {}
    virtual Pulizia* clone() const;
    virtual bool posponi (const Data d=Data()) const;
    virtual string generaNota() const;
    // virtual import
    virtual unsigned short int calcolaPunteggio() const;
};

#endif // PULIZIA_H
