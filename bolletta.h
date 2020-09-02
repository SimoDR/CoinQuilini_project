#ifndef BOLLETTA_H
#define BOLLETTA_H

#include "pagamento.h"

class Bolletta: public Pagamento
{
private:
    Data _dataLimite;

public:
    Bolletta(const string & nome="bolletta",float importo=0,const Data& dataLimite=Data(),Inquilino * incaricato=nullptr,bool svolto=false);
    virtual ~Bolletta() {}
    virtual Bolletta* clone() const;

    // set
    virtual void setDataLimite(const Data&);

    //get
    virtual string getLabel() const;
    virtual string generaNota() const;

    virtual bool posponi (const Data&) const;

    // input/output
    static void importXml(QXmlStreamReader & xmlInput, vector<string> & parametri);
    virtual void exportXml(QXmlStreamWriter&,string data) const;
};

#endif // BOLLETTA_H
