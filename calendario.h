#ifndef CALENDARIO_H
#define CALENDARIO_H
#include "data.h"
#include "dList.h"
#include "incarico.h"
#include "listainquilini.h"
#include<map>
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
        void stampaGiornata() //DEBUG
        {
            cout<<_dataDelGiorno<<": ";
            for(vector<Incarico*>::iterator it=_incarichiDelGiorno.begin(); it!=_incarichiDelGiorno.end(); ++it)
                cout<<(*it)->getNome()<<" ("<<(*it)->getIncaricato()->getNome()<<") ";
            cout<<endl;
        }

    };



    dList<Giorno> _giorni;
    dList<Giorno>::iterator _iteratoreCorrente;


    // serve a convertire una data in input (es: la data
    // in cui si vuole inserire un incarico) nell'
    // iteratore che punta al giorno della data. L'iteratore
    // iniziale sarà _iteratoreCorrente per l'inserimento
    // di un incarico normale, l'iteratore restituito dalla
    // chiamata precedente nel caso di un incarico ricorrente
    dList<Giorno>::iterator iteratoreFromData(dList<Giorno>::iterator, const Data&);

    bool checkIteratore(dList<Giorno>::iterator) const; //ritorna true sse è pte

    dList<Giorno>::iterator inizializzaCalendario(const Data&);




public:
    class BufferInquilini //DA METTERE PRIVATA
    {
    public: //DA TOGLIERE
        friend class Calendario;

        //campi dati
        vector<Inquilino*> _inquilini;
        vector<Inquilino*>::iterator _index;

        void stampaBuffer() //debug
        {
            for(vector<Inquilino*>::iterator it=_inquilini.begin(); it!=_inquilini.end(); ++it)
                cout<<(*it)->getNome()<<endl;
        }

        //metodi
        BufferInquilini(const vector<Inquilino*>& listaInquilini);
        void avanza();
        vector<Inquilino*> trovaMinimi(dList<Giorno>::iterator iteratoreMinim0);
        Inquilino * restituisciIlMinimo(dList<Giorno>::iterator iteratoreMinimo);

    };
     BufferInquilini _buffer; //da mettere privato

    void stampaGiorni() //DEBUG
    {
        for(dList<Giorno>::iterator it=_giorni.begin(); it!=_giorni.end(); ++it)
            it->stampaGiornata();

    }

    Calendario(const Data&, const vector<Inquilino*>& listaInquilini);
    void aggiungiAlBuffer(Inquilino* nuovoInquilino);
    void rimuoviDalBuffer(unsigned int pos);
    Inquilino * ottieniIncaricato(dList<Giorno>::iterator iteratoreIniziale);
    void incrementaData();
    const Data& getDataDiOggi() const //debug
    {
        return _iteratoreCorrente->_dataDelGiorno;
    }


    Incarico * trovaIncarico (const Data& dataIncarico, int indiceIncarico);
    // il controller gli passa la data dell'incarico e la sua
    // posizione nella lista dell'interfaccia, questo metodo
    // ritorna il puntatore all'incarico stesso. Probabilmente
    // tra le varie robe invocherà
    // iteratoreFromData(_iteratoreCorrente,dataIncarico)

    bool insert(Incarico *, Data&, int, int);

    bool remove(Incarico * daRimuovere, const Data& dataIncarico);

    bool posponiIncarico(Incarico * daPosporre, unsigned int quantoPosporre,const Data& dataIncarico);

    //    importacalendario(fileXML)
    //    esportacalendario()
    //    iterator *getCurrent()

    //    vector<sring> getspecifiche(incarico *)
};

#endif // CALENDARIO_H
