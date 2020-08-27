#ifndef BOLLETTA_H
#define BOLLETTA_H

#include "pagamento.h"

class Bolletta: public Pagamento{
private:
    Data _dataLimite;
public:
    Bolletta(const string & nome,float importo,const Data& dataLimite=Data(),Inquilino * incaricato=nullptr,bool svolto=false);
    virtual ~Bolletta() {}
    virtual void setDataLimite(const Data&);
    virtual Bolletta* clone() const;
    virtual bool posponi (const Data& d=Data()) const;
    virtual string getLabel() const;
    virtual void exportXml(QXmlStreamWriter&,string data) const;
    virtual string generaNota() const;
    static void importXml(QXmlStreamReader & xmlInput, vector<string> & parametri);
};

#endif // BOLLETTA_H
