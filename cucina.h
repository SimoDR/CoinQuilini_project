#ifndef CUCINA_H
#define CUCINA_H

#include "faccenda.h"
#include<math.h>

class Cucina: public Faccenda
{
private:
    unsigned short int _numeroCommensali;
    static float _pesoCucina;

public:
    Cucina(const string & nome="cucina",int tempoStimato=60,unsigned short int numeroCommensali=4,
           Inquilino * incaricato=nullptr,bool svolto=false);
    virtual ~Cucina() {}
    virtual Cucina* clone() const;

    // get
    virtual string getLabel() const;
    virtual string generaNota() const;

    virtual bool posponi (const Data &) const;
    virtual unsigned short int calcolaPunteggio() const;

    // input/output
    static void importXml(QXmlStreamReader & xmlInput, vector<string> & parametri);
    virtual void exportXml(QXmlStreamWriter&,string data) const;
};

#endif // CUCINA_H
