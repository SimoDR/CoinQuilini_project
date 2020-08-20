#ifndef CALENDARIO_H
#define CALENDARIO_H
#include "data.h"
#include "dList.h"
#include "incarico.h"
#include "listainquilini.h"
#include<map>
using std::map;

typedef  std::pair<Inquilino*,int> tpair;


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

    // serve a convertire una data in input (es: la data
    // in cui si vuole inserire un incarico) nell'
    // iteratore che punta al giorno della data. L'iteratore
    // iniziale sarà _iteratoreCorrente per l'inserimento
    // di un incarico normale, l'iteratore restituito dalla
    // chiamata precedente nel caso di un incarico ricorrente
    dList<Giorno>::iterator iteratoreFromData(dList<Giorno>::iterator, const Data&);



    class BufferInquilini
    {
        friend class Calendario;

        //campi dati
        vector<Inquilino*> _inquilini;
        vector<Inquilino*>::iterator _index;

        //metodi
        BufferInquilini(const vector<Inquilino*>& listaInquilini): _inquilini(listaInquilini), _index(_inquilini.begin()) {}


        void avanza()
        {
            _index++;
            if(_index==_inquilini.end()) _index=_inquilini.begin();
        }



        vector<Inquilino*> trovaMinimi(dList<Giorno>::iterator iteratoreMinimo)
        {
            map<Inquilino*,int> coppie;
            map<Inquilino*,int>::iterator mit;


            for(vector<Inquilino*>::iterator it=_inquilini.begin(); it!=_inquilini.end(); ++it) //aggiungo gli inquilini
            {
                coppie[*it]=0;
            }

            int minimo=INT_MAX;
            for(vector<Incarico*>::iterator it=iteratoreMinimo->_incarichiDelGiorno.begin(); it!=iteratoreMinimo->_incarichiDelGiorno.end(); ++it)
            {
                mit=coppie.find((**it).getIncaricato());
                mit->second++;
                if(minimo<mit->second)
                    minimo=mit->second;
            }

            vector<Inquilino*> minimiFinali;

            for(map<Inquilino*,int>::iterator mit=coppie.begin(); mit!=coppie.end(); ++mit)
            {
                if(mit->second==minimo)
                    minimiFinali.push_back(mit->first);
            }

            return minimiFinali;

        }






        Inquilino * restituisciIlMinimo(dList<Giorno>::iterator iteratoreMinimo)
        {
            vector<Inquilino*> minimi=trovaMinimi(iteratoreMinimo);
            vector<Inquilino*>::iterator j=minimi.begin();
            while(j<minimi.end())
            {
                if(*_index==*j)
                    return *_index;
                j++;
            }
            avanza();
        }

    };

    BufferInquilini _buffer;




public:
    Calendario(const vector<Inquilino*>& listaInquilini): _buffer(listaInquilini) {}

    void aggiungiAlBuffer(Inquilino* nuovoInquilino)
    {
        _buffer._inquilini.push_back(nuovoInquilino);
        _buffer._index=_buffer._inquilini.begin();
    }

    void rimuoviDalBuffer(unsigned int pos)
    {
        unsigned int cont=0;
        vector<Inquilino*>::iterator i;
        for(i=_buffer._inquilini.begin();i!=_buffer._inquilini.end(); ++i) {
            if (cont==pos)
            {
                _buffer._inquilini.erase(i);
                return;
            }

            cont++;
        }
        _buffer._index=_buffer._inquilini.begin();
    }

    Inquilino * ottieniIncaricato(dList<Giorno>::iterator iteratoreIniziale)
    {
        return _buffer.restituisciIlMinimo(iteratoreIniziale);
    }







    // incarico * trovaIncarico (Data dataIncarico, int indiceIncarico) const? // il controller gli passa la data dell'incarico e la sua
    // posizione nella lista dell'interfaccia, questo metodo
    // ritorna il puntatore all'incarico stesso. Probabilmente
    // tra le varie robe invocherà
    // iteratoreFromData(_iteratoreCorrente,dataIncarico)

    bool insert(Incarico *, const Data&, int, int);

    //    creaAggiungi(vector<string> (parametri), data)
    //    bool remove(incarico*, data)
    //    bool insertrec(incarico *, data inizio, int cadenza, data datafine (o numerooccorrenze))
    //    importacalendario(fileXML)
    //    esportacalendario()
    //    iterator *getCurrent()

    //    vector<sring> getspecifiche(incarico *)
};

#endif // CALENDARIO_H
