#include "calendario.h"

dList<Giorno>::iterator Calendario::iteratoreFromData(dList<Giorno>::iterator iteratoreIniziale, const Data& inCuiInserire)
{
    //se non c'è il giorno, crealo

}

Calendario::Calendario()
{

}

bool Calendario::insert(Incarico * daInserire, const Data & dataInCuiInserire, int numeroOccorrenze, int cadenzaIncarico)
{
    iteratoreIniziale=_iteratoreCorrente;
    while(numeroOccorrenze>0)
    {
        Inquilino * incaricato=ottieniIncaricato(); //da fare tramite buffer
        daInserire->setIncaricato(incaricato);
        dList<Giorno>::iterator iteratoreInCuiInserire=iteratoreFromData(iteratoreIniziale, dataInCuiInserire);
        *iteratoreInCuiInserire._incarichiDelGiorno.push_back(daInserire);
        dataInCuiInserire=dataInCuiInserire+cadenzaIncarico;
        iteratoreIniziale=iteratoreInCuiInserire;
        numeroOccorrenze--;
    }

}


