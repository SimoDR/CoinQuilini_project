#ifndef FACCENDA_H
#define FACCENDA_H

#include "incarico.h"

class Faccenda: virtual public Incarico {
private:
    int _tempoStimato; // minuti per effettuare la faccenda
    static unsigned short int _pesoFaccenda;
public:
    Faccenda(string nome,int tempoStimato,Inquilino * incaricato=nullptr,bool svolto=false);
    virtual ~Faccenda()=0;
    virtual string generaNota() const;
    virtual void exportXml(QXmlStreamWriter&) const;
    virtual unsigned short int calcolaPunteggio() const;
};

#endif // FACCENDA_H
