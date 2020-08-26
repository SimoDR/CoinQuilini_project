#ifndef PAGAMENTO_H
#define PAGAMENTO_H

#include "incarico.h"

class Pagamento: virtual public Incarico
{
private:
    double _importo;
    static double _pesoPagamento;

public:
    Pagamento(const string& nome,double importo,Inquilino * incaricato=nullptr,bool svolto=false);
    Pagamento() {}
    void setImporto(double);
    double getImporto() const;
    virtual ~Pagamento()=0;
    virtual string generaNota() const;
    virtual void exportXml(QXmlStreamWriter & xmlOutput) const;
    void importXml(QXmlStreamReader & xmlInput, vector<string> & parametri);
    virtual unsigned short int calcolaPunteggio() const;
};

#endif // PAGAMENTO_H
