#include "calendario.h"

dList<Giorno>::iterator Calendario::iteratoreFromData(dList<Giorno>::iterator iteratoreIniziale, const Data& inCuiInserire)
{
    bool trovato=false;
    while(!trovato)
    {
        if(*iteratoreIniziale._dataDelGiorno>inCuiInserire) //il giorno non c'è, bisogna crearlo
        {
            _giorni.insert(iteratoreIniziale,Giorno(inCuiInserire));
            trovato=true;
        }
        else if(*iteratoreIniziale._dataDelGiorno<inCuiInserire ) //non ho ancora raggiunto il giorno
        {
            ++iteratoreIniziale;
        }
        else //trovato, ritorna semplicemente
        {
            trovato=true;
        }
    }

    return iteratoreIniziale;
}

Calendario::Calendario()
{

}

bool Calendario::insert(Incarico * daInserire, const Data & dataInCuiInserire, int numeroOccorrenze, int cadenzaIncarico)
{
    dList<Giorno>::iterator iteratoreIniziale=_iteratoreCorrente;
    while(numeroOccorrenze>0)
    {
        Inquilino * incaricato=ottieniIncaricato(); //da fare tramite buffer DA FARE
        daInserire->setIncaricato(incaricato);
        dList<Giorno>::iterator iteratoreInCuiInserire=iteratoreFromData(iteratoreIniziale, dataInCuiInserire);
        *iteratoreInCuiInserire._incarichiDelGiorno.push_back(daInserire);
        dataInCuiInserire=dataInCuiInserire+cadenzaIncarico;
        iteratoreIniziale=iteratoreInCuiInserire;
        numeroOccorrenze--;
    }

}



Calendario::Giorno::Giorno(Data dataDelGiorno): _dataDelGiorno(dataDelGiorno) {}




Calendario::BufferInquilini::BufferInquilini()
{

}
