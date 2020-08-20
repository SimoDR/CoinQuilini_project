#ifndef CUCINA_H
#define CUCINA_H

#include "faccenda.h"
#include<math.h>

class Cucina: public Faccenda
{
private:
    unsigned short int _numeroCommensali; //eccezioni: limitare numero commensali
    static double _pesoCucina;
public:
    //Cucina(string nome,int tempoStimato,unsigned short int numeroCommensali,Inquilino * incaricato=nullptr,bool svolto=false):
    //	Faccenda(nome,tempoStimato,incaricato,svolto), _numeroCommensali(numeroCommensali) {}
    virtual ~Cucina() {}
    virtual Cucina* clone() const;
    virtual string generaNota() const;
    // virtual import
    virtual unsigned short int calcolaPunteggio() const;

};

#endif // CUCINA_H
