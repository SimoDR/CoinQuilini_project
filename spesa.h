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
    static vector<string> _listaSpesa; //debug
    unsigned short int _numeroArticoli;
public:
    Spesa(const string& nome="spesa",float importo=0,int tempoStimato=60,
          unsigned short int numeroArticoli=0,Inquilino * incaricato=nullptr,bool svolto=false);
    virtual ~Spesa() {};
    virtual bool posponi (const Data &) const;
    virtual Spesa* clone() const;
    virtual string generaNota() const;
    void exportXml(QXmlStreamWriter & xmlOutput,string data) const;
    static void importXml(QXmlStreamReader & xmlInput, vector<string> & parametri);
    virtual string getLabel() const;
    virtual unsigned short int calcolaPunteggio() const;
    vector<string> getListaSpesa() const; //debug
    void aggiungiListaSpesa(const string&); //debug
    void rimuoviListaSpesa(const string&); //debug
    void svuotaListaSpesa(); //debug
    void setArticoli();
};

#endif // SPESA_H
