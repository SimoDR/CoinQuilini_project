#ifndef PULIZIA_H
#define PULIZIA_H

#include "faccenda.h"

class Pulizia: public Faccenda
{
private:
    unsigned short int _stanzeDaPulire;
    static unsigned short int _pesoPulizia;
public:
    Pulizia(const string& nome,int tempoStimato,unsigned short int stanzeDaPulire,Inquilino * incaricato=nullptr,bool svolto=false);
    virtual ~Pulizia() {}
    virtual Pulizia* clone() const;
    virtual bool posponi (const Data& d=Data()) const;
    virtual string generaNota() const;
    virtual void setDataLimite(const Data&) {}
    virtual void exportXml(QXmlStreamWriter & xmlOutput,string data) const;
    virtual string getLabel() const;
    static void importXml(QXmlStreamReader & xmlInput, vector<string> & parametri);
    virtual unsigned short int calcolaPunteggio() const;
};

#endif // PULIZIA_H
