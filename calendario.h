#ifndef CALENDARIO_H
#define CALENDARIO_H
#include "data.h"
#include "dList.h"
#include "incarico.h"
#include "spesa.h"
#include "cucina.h"
#include "pulizia.h"
#include "spazzatura.h"
#include "bolletta.h"
#include "listainquilini.h"

#include<map>
#include"pagamento.h"
using std::map;

class Calendario
{
private:
    class Giorno
    {
        friend class Calendario;
        Data _dataDelGiorno;
        vector<Incarico*> _incarichiDelGiorno;
        Giorno(Data delGiorno);
    };


    dList<Giorno> _giorni;
    dList<Giorno>::iterator _iteratoreCorrente;
    vector<string> _nonSvoltiImport;


    dList<Giorno>::iterator iteratoreFromData(dList<Giorno>::iterator, const Data&);
    bool checkIteratore(dList<Giorno>::const_iterator) const; //ritorna true sse è pte
    dList<Giorno>::iterator inizializzaCalendario(const Data&);

    class BufferInquilini 
    {

        friend class Calendario;

        vector<Inquilino*> _inquilini;
        vector<Inquilino*>::iterator _index;

        BufferInquilini(const vector<Inquilino*>& listaInquilini);
        //non serve distruttore perchè gli inquilini vengono eliminati con la delete dalla listaInquilini (essendo condivisi)
        void avanza();
        Inquilino * getInquilino(string nome) const;
        vector<Inquilino*> trovaMinimi(dList<Giorno>::iterator iteratoreMinim0);
        Inquilino * restituisciIlMinimo(dList<Giorno>::iterator iteratoreMinimo);

    };

    BufferInquilini _buffer;

public:

    Calendario(const Data&, const vector<Inquilino*>& listaInquilini);
    ~Calendario();
    void aggiungiAlBuffer(Inquilino* nuovoInquilino);
    void rimuoviInquilino(unsigned int pos);
    Inquilino * ottieniIncaricato(dList<Giorno>::iterator iteratoreIniziale);
    void incrementaData();
    const Data& getDataDiOggi() const;
    Incarico * trovaIncarico(const Data& dataIncarico, unsigned int indiceIncarico, bool=false);
    void insert(Incarico *, Data, int, int, int, bool);
    void remove(const Data& dataIncarico,unsigned int indiceIncarico);
    void posponiIncaricoCalendario(unsigned int indiceIncarico, unsigned int quantoPosporre,const Data& dataIncarico);
    void checkIncarichiSvolti() const;
    void checkIncarichiSvoltiPassato() const;
    void setCredito(Pagamento*, vector<Inquilino*> &) const;
    void exportXml() const;
    void importXml();
    void creaNuovoIncarico(const vector<string>& parametri,bool import);
    void incarichiGiorno(const Data & giorno, vector<std::string> & tipiIncarichi, vector<string> & incaricati) const;
    void removeIncarichiPassatiInquilino(Inquilino * );
};

#endif // CALENDARIO_H
