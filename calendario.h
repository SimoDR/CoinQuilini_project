#ifndef CALENDARIO_H
#define CALENDARIO_H
#include "data.h"
#include "dList.h"
#include "incarico.h"
#include "listainquilini.h"

class Calendario
{
private:
    class Giorno
    {
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
        //campi dati
        vector<Inquilino*> inquilini;
        vector<Inquilino*>::iterator index;

        //metodi
        BufferInquilini(); //aggiungere i coinquilini DA FARE
        void avanza()
        {
             index++;
             if(index==inquilini.end()) index=inquilini.begin();
        }
        vector<Inquilino*> trovaMinimi() const
        {
            //DA FARE
        }
        Inquilino * restituisciIlMinimo(vector<Inquilino*> minimi)
        {
            vector<Inquilino*>::iterator j=minimi.begin();
            while(j<minimi.end())
            {
                 if(*index==*j)
                     return *index;
                 j++;
            }
            avanza();
        }

    };

           BufferInquilini buffer;


public:
    Calendario();


//    incarico * trovaIncarico (Data dataIncarico, int indiceIncarico) const? // il controller gli passa la data dell'incarico e la sua
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
