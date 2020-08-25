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
    static vector<string> _listaSpesa;
    unsigned short int _numeroArticoli;
public:
    Spesa(string nome,double importo,int tempoStimato,unsigned short int numeroArticoli=0,Inquilino * incaricato=nullptr,bool svolto=false):
        Incarico(nome,incaricato,svolto),Pagamento(nome,importo,incaricato,svolto),Faccenda(nome,tempoStimato,incaricato,svolto), _numeroArticoli(numeroArticoli) {}
    virtual ~Spesa() {};
    virtual Spesa* clone() const;
    virtual bool posponi (const Data d=Data()) const;
    virtual string generaNota() const;
    void exportXml(QXmlStreamWriter & xmlOutput) const;
    virtual unsigned short int calcolaPunteggio() const;
    // virtual import
    vector<string> getListaSpesa() const;
    void aggiungiListaSpesa(const string&);
    void rimuoviListaSpesa(const string&);
    void svuotaListaSpesa();
    void setArticoli();
};

#endif // SPESA_H
