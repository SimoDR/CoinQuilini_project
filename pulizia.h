#ifndef PULIZIA_H
#define PULIZIA_H

#include "faccenda.h"

class Pulizia: public Faccenda
{
private:
    unsigned short int _stanzeDaPulire;
    static unsigned short int _pesoPulizia;

public:
    Pulizia(const string& nome="pulizia",int tempoStimato=60,unsigned short int stanzeDaPulire=2,
            Inquilino * incaricato=nullptr,bool svolto=false);
    virtual ~Pulizia() {}
    virtual Pulizia* clone() const;

    // get
    virtual string getLabel() const;
    virtual string generaNota() const;

    virtual bool posponi (const Data &) const;
    virtual unsigned short int calcolaPunteggio() const;

    // input/output
    static void importXml(QXmlStreamReader & xmlInput, vector<string> & parametri);
    virtual void exportXml(QXmlStreamWriter & xmlOutput,string data) const;
};

#endif // PULIZIA_H
