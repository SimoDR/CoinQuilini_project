#ifndef CALENDARIO_H
#define CALENDARIO_H
#include "data.h"
//#include "dList.h"

class Calendario
{
private:
    class Giorno
    {
        Data _dataDelGiorno;
        //vector<Incarico*> _incarichiDelGiorno;


    };

    //dList<Giorno> _giorni;
    //dList<Giorno>::iterator _iteratoreCorrente;


// iterator iteratoreFromData(iterator iteratoreIniziale, Data inCuiInserire) // serve a convertire una data in input (es: la data
                                                                              // in cui si vuole inserire un incarico) nell'
                                                                              // iteratore che punta al giorno della data. L'iteratore
                                                                              // iniziale sarà _iteratoreCorrente per l'inserimento
                                                                              // di un incarico normale, l'iteratore restituito dalla
                                                                              // chiamata precedente nel caso di un incarico ricorrente



public:
    Calendario();


//    incarico * trovaIncarico (Data dataIncarico, int indiceIncarico) // il controller gli passa la data dell'incarico e la sua
                                                                       // posizione nella lista dell'interfaccia, questo metodo
                                                                       // ritorna il puntatore all'incarico stesso. Probabilmente
                                                                       // tra le varie robe invocherà
                                                                       // iteratoreFromData(_iteratoreCorrente,dataIncarico)

//    bool insert(incarico * incaricoDaInserire, data dataInCuiInserire) // chiamato dal controller
                                                                         //
                                                                         //
                                                                         //

//    creaAggiungi(vector<string> (parametri), data)
//    bool remove(incarico*, data)
//    bool insertrec(incarico *, data inizio, int cadenza, data datafine (o numerooccorrenze))
//    importacalendario(fileXML)
//    esportacalendario()
//    iterator *getCurrent()

//    vector<sring> getspecifiche(incarico *)
};

#endif // CALENDARIO_H
