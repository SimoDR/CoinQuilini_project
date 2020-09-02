#ifndef SPAZZATURA_H
#define SPAZZATURA_H

#include "faccenda.h"

class Spazzatura: public Faccenda
{
private:
    static unsigned short int _pesoSpazzatura;
    string _cosaButtare;

public:
    Spazzatura(const string& nome="spazzatura", const string & cosaButtare="rifiuto",int tempoStimato=10,
               Inquilino * incaricato=nullptr,bool svolto=false);
    virtual ~Spazzatura() {}
    virtual Spazzatura* clone() const;

    // get
    virtual string getLabel() const;
    virtual string generaNota() const;

    virtual bool posponi (const Data &) const;
    virtual unsigned short int calcolaPunteggio() const;

    // input/output
    static void importXml(QXmlStreamReader & xmlInput, vector<string> & parametri);
    virtual void exportXml(QXmlStreamWriter & xmlOutput,string data) const;
};

#endif // SPAZZATURA_H
