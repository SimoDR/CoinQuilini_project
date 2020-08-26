#ifndef CUCINA_H
#define CUCINA_H

#include "faccenda.h"
#include<math.h>

class Cucina: public Faccenda
{
private:
    unsigned short int _numeroCommensali;
    static double _pesoCucina;
public:
    Cucina(const string & nome,int tempoStimato,unsigned short int numeroCommensali,Inquilino * incaricato=nullptr,bool svolto=false);
    virtual ~Cucina() {}
    virtual Cucina* clone() const;
    virtual string generaNota() const;
    virtual unsigned short int calcolaPunteggio() const;
    virtual void exportXml(QXmlStreamWriter&) const;
};

#endif // CUCINA_H
