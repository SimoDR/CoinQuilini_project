#ifndef SPESA_H
#define SPESA_H

#include "faccenda.h"
#include "pagamento.h"
#include <vector>
using std::string;

class Spesa: public Pagamento, public Faccenda
{
private:
    static unsigned short int _pesoSpesa;
    unsigned short int _numeroArticoli;

public:
    Spesa(const string& nome="spesa",float importo=0,int tempoStimato=60,
          unsigned short int numeroArticoli=0,Inquilino * incaricato=nullptr,bool svolto=false);
    virtual ~Spesa() {};
    virtual Spesa* clone() const;

    // get
    virtual string getLabel() const;
    virtual string generaNota() const;

    virtual bool posponi (const Data &) const;
    virtual unsigned short int calcolaPunteggio() const;

    // input/output
    static void importXml(QXmlStreamReader & xmlInput, vector<string> & parametri);
    void exportXml(QXmlStreamWriter & xmlOutput,string data) const;
};

#endif // SPESA_H
