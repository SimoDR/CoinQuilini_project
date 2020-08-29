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
        void stampaGiornata() //DEBUG
        {
            cout<<_dataDelGiorno<<": ";
            for(vector<Incarico*>::iterator it=_incarichiDelGiorno.begin(); it!=_incarichiDelGiorno.end(); ++it)
            {

                cout<<(*it)->getNome()<<" ("<<(*it)->getIncaricato()->getNome()<<") ";
//                if(dynamic_cast<Bolletta*>(*it))
//                {
//                    cout<<(*it)->generaNota()<<endl;
//                }
            }
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
        Inquilino * getInquilino(string nome) const;
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
    ~Calendario();
    void aggiungiAlBuffer(Inquilino* nuovoInquilino);
    void rimuoviInquilino(unsigned int pos);
    Inquilino * ottieniIncaricato(dList<Giorno>::iterator iteratoreIniziale);
    void incrementaData();
    const Data& getDataDiOggi() const //debug
    {
        return _iteratoreCorrente->_dataDelGiorno;
    }


    Incarico * trovaIncarico(const Data& dataIncarico, unsigned int indiceIncarico);
    // il controller gli passa la data dell'incarico e la sua
    // posizione nella lista dell'interfaccia, questo metodo
    // ritorna il puntatore all'incarico stesso. Probabilmente
    // tra le varie robe invocherà
    // iteratoreFromData(_iteratoreCorrente,dataIncarico)


    void insert(Incarico *, Data, int, int, int, bool);

    void remove(Incarico * daRimuovere, const Data& dataIncarico);

    void posponiIncarico(Incarico * daPosporre, unsigned int quantoPosporre,const Data& dataIncarico);

    void checkIncarichiSvolti();

    void setCredito(Pagamento*, vector<Inquilino*> &);

    void exportXml() const;

    void importXml();

    void creaNuovoIncarico(const vector<string>& parametri,bool import);

    void incarichiGiorno(const Data & giorno, vector<std::string> & tipiIncarichi, vector<string> & incaricati) const;


    //    importacalendario(fileXML)
    //    esportacalendario()
    //    iterator *getCurrent()

    //    vector<sring> getspecifiche(incarico *)
};

#endif // CALENDARIO_H
