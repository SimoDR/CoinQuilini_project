#ifndef PAGAMENTO_H
#define PAGAMENTO_H

#include "incarico.h"

class Pagamento: virtual public Incarico
{
private:
    double _importo;
    static double _pesoPagamento;

public:
    Pagamento(string nome,double importo,Inquilino * incaricato=nullptr,bool svolto=false);
    Pagamento() {}
    void setImporto(const double&);
    double getImporto() const;
    virtual ~Pagamento()=0;
    virtual string generaNota() const;
    void exportXml(QXmlStreamWriter & xmlOutput) const;
    virtual unsigned short int calcolaPunteggio() const;
};

#endif // PAGAMENTO_H
