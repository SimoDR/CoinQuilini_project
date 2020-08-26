#ifndef SPAZZATURA_H
#define SPAZZATURA_H

#include "faccenda.h"

class Spazzatura: public Faccenda
{
private:
    static unsigned short int _pesoSpazzatura;
    string _cosaButtare;

public:
    Spazzatura(const string& nome, string cosaButtare,int tempoStimato, Inquilino * incaricato=nullptr,bool svolto=false);
    virtual ~Spazzatura() {}
    virtual Spazzatura* clone() const;
    virtual string generaNota() const;
    virtual void exportXml(QXmlStreamWriter & xmlOutput) const;
    void importXml(QXmlStreamReader & xmlInput, vector<string> & parametri);
    virtual string getLabel() const;
    virtual unsigned short int calcolaPunteggio() const;
};

#endif // SPAZZATURA_H
