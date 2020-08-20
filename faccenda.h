#ifndef FACCENDA_H
#define FACCENDA_H

#include "incarico.h"

class Faccenda: virtual public Incarico {
private:
    int _tempoStimato; // minuti per effettuare la faccenda
    static unsigned short int _pesoFaccenda;
public:
    //Faccenda(string nome,int tempoStimato,Inquilino * incaricato=nullptr,bool svolto=false): Incarico(nome,incaricato,svolto), _tempoStimato(tempoStimato) {}
    virtual ~Faccenda()=0;
    virtual string generaNota() const;
    // virtual import
    virtual unsigned short int calcolaPunteggio() const;
};

#endif // FACCENDA_H
