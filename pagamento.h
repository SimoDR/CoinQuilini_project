#ifndef PAGAMENTO_H
#define PAGAMENTO_H

#include "incarico.h"
#include <iomanip>
#include <sstream>

class Pagamento: virtual public Incarico
{
private:
    float _importo;
    static unsigned short int _pesoPagamento;

public:
    Pagamento(float importo);
    Pagamento() {}
    virtual ~Pagamento()=0;

    // get
    float getImporto() const;
    virtual string generaNota() const;

    virtual unsigned short int calcolaPunteggio() const;

    // input/output
    static void importXml(QXmlStreamReader & xmlInput, vector<string> & parametri);
    virtual void exportXml(QXmlStreamWriter & xmlOutput,string data) const;
};

#endif // PAGAMENTO_H
