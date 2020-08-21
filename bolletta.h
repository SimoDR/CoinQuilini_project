#ifndef BOLLETTA_H
#define BOLLETTA_H

#include "pagamento.h"

class Bolletta: public Pagamento{
private:
    Data _dataLimite;
public:
    Bolletta(string nome,double importo,const Data& dataLimite,Inquilino * incaricato=nullptr,bool svolto=false):
        Incarico(nome,incaricato,svolto), Pagamento(nome,importo,incaricato,svolto), _dataLimite(dataLimite) {}
    virtual ~Bolletta() {}
    virtual Bolletta* clone() const;
    virtual bool posponi (const Data d=Data()) const;
    // virtual import //da definire opportunamente
};

#endif // BOLLETTA_H
