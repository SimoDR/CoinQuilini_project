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
    Cucina(const string & nome="cucina",int tempoStimato=60,unsigned short int numeroCommensali=4,Inquilino * incaricato=nullptr,bool svolto=false);
    virtual ~Cucina() {}
    virtual Cucina* clone() const;

    virtual string generaNota() const;
    virtual unsigned short int calcolaPunteggio() const;
    virtual void exportXml(QXmlStreamWriter&,string data) const;
    virtual string getLabel() const;
    static void importXml(QXmlStreamReader & xmlInput, vector<string> & parametri);
};

#endif // CUCINA_H
