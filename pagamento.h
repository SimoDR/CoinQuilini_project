#ifndef PAGAMENTO_H
#define PAGAMENTO_H

#include "incarico.h"

class Pagamento: virtual public Incarico
{
private:
    float _importo;
    static unsigned short int _pesoPagamento;

public:
    Pagamento(float importo);
    void setImporto(double);
    double getImporto() const;
    virtual ~Pagamento()=0;
    virtual string generaNota() const;
    virtual void exportXml(QXmlStreamWriter & xmlOutput) const;
    static void importXml(QXmlStreamReader & xmlInput, vector<string> & parametri);
    virtual unsigned short int calcolaPunteggio() const;
};

#endif // PAGAMENTO_H
