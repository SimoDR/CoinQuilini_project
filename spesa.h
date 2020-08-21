#ifndef SPESA_H
#define SPESA_H

#include "faccenda.h"
#include "pagamento.h"

class Spesa: public Pagamento, public Faccenda
{
private:
    static unsigned short int _pesoSpesa;
    unsigned short int _numeroArticoli;
public:
    Spesa(string nome,double importo,int tempoStimato,unsigned short int numeroArticoli,Inquilino * incaricato=nullptr,bool svolto=false):
        Incarico(nome,incaricato,svolto),Pagamento(nome,importo,incaricato,svolto),Faccenda(nome,tempoStimato,incaricato,svolto), _numeroArticoli(numeroArticoli) {}
    virtual ~Spesa() {};
    virtual Spesa* clone() const;
    void setArticoli(const unsigned short int &);
    virtual bool posponi (const Data d=Data()) const;
    virtual string generaNota() const;
    virtual unsigned short int calcolaPunteggio() const;
    // virtual import
};

#endif // SPESA_H
