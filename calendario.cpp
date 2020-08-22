#include "calendario.h"

dList<Calendario::Giorno>::iterator Calendario::iteratoreFromData(dList<Giorno>::iterator iteratoreIniziale, const Data& inCuiInserire)
{
    bool trovato=false;
    while(!trovato)
    {
        if(checkIteratore(iteratoreIniziale)) //se è pte
        {
            iteratoreIniziale=_giorni.insert(iteratoreIniziale,Giorno(inCuiInserire));
            trovato=true;
        }
        else if(iteratoreIniziale->_dataDelGiorno>inCuiInserire) //il giorno non c'è, bisogna crearlo
        {
            _giorni.insert(iteratoreIniziale,Giorno(inCuiInserire));
            trovato=true;
        }
        else if(iteratoreIniziale->_dataDelGiorno<inCuiInserire ) //non ho ancora raggiunto il giorno
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

bool Calendario::checkIteratore(dList<Calendario::Giorno>::iterator iteratoreDaControllare) const
{
    if(iteratoreDaControllare==_giorni.end())
        return true;
    else return false;
}

Calendario::Calendario(const vector<Inquilino *> &listaInquilini): _iteratoreCorrente(_giorni.end()), _buffer(listaInquilini) {}

void Calendario::aggiungiAlBuffer(Inquilino *nuovoInquilino)
{
    _buffer._inquilini.push_back(nuovoInquilino);
    _buffer._index=_buffer._inquilini.begin();
}

void Calendario::rimuoviDalBuffer(unsigned int pos)
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

Inquilino * Calendario:: ottieniIncaricato(dList<Calendario::Giorno>::iterator iteratoreIniziale, bool pte)
{
    return _buffer.restituisciIlMinimo(iteratoreIniziale,pte);

}



bool Calendario::insert(Incarico * daInserire, Data & dataInCuiInserire, int numeroOccorrenze, int cadenzaIncarico)
{
    dList<Giorno>::iterator iteratoreIniziale=_iteratoreCorrente;
    bool pte=checkIteratore(_iteratoreCorrente);
    bool vuoti=checkIteratore(_giorni.begin()); //se _giorni è vuota
    if(!vuoti)
    {
        pte=false;
        iteratoreIniziale=_giorni.begin();
    }
    while(numeroOccorrenze>0)
    {

        Inquilino * incaricato=ottieniIncaricato(iteratoreIniziale,pte);
        _buffer.avanza();

        daInserire->setIncaricato(incaricato);

        dList<Giorno>::iterator iteratoreInCuiInserire=iteratoreFromData(iteratoreIniziale, dataInCuiInserire);
        iteratoreInCuiInserire->_incarichiDelGiorno.push_back(daInserire->clone());

        dataInCuiInserire=dataInCuiInserire+cadenzaIncarico;
        iteratoreIniziale=iteratoreInCuiInserire;
        numeroOccorrenze--;
    }
    return true;

}



Calendario::Giorno::Giorno(Data dataDelGiorno): _dataDelGiorno(dataDelGiorno) {}






Calendario::BufferInquilini::BufferInquilini(const vector<Inquilino *> &listaInquilini): _inquilini(listaInquilini), _index(_inquilini.begin()) {}

void Calendario::BufferInquilini::avanza()
{
    _index++;
    if(_index==_inquilini.end()) _index=_inquilini.begin();
}

vector<Inquilino *> Calendario::BufferInquilini::trovaMinimi(dList<Calendario::Giorno>::iterator iteratoreMinimo,bool pte) //restituisce l'inquilino (o più di uno) che ha meno incarichi già programmati in una determinata data
{
    map<Inquilino*,int> coppie;
    map<Inquilino*,int>::iterator mit;


    for(vector<Inquilino*>::iterator it=_inquilini.begin(); it!=_inquilini.end(); ++it) //aggiungo gli inquilini, tutti con frequenza 0
    {
        coppie[*it]=0;
    }

//    cout<<"*****"<<endl;
//    for(map<Inquilino*,int>::iterator mit=coppie.begin(); mit!=coppie.end(); ++mit) //debug
//    {
//        cout<<(*mit).first->getNome()<<endl;
//    }

    int minimo=INT_MAX;
//    cout<<"*****"<<endl;

    vector<Inquilino*> minimiFinali;

    if(!pte) {
        for(vector<Incarico*>::iterator it=iteratoreMinimo->_incarichiDelGiorno.begin(); it!=iteratoreMinimo->_incarichiDelGiorno.end(); ++it)
        {

            mit=coppie.find((**it).getIncaricato());
            mit->second++;
            if(minimo<mit->second)
                minimo=mit->second;
        }

        for(map<Inquilino*,int>::iterator mit=coppie.begin(); mit!=coppie.end(); ++mit)
        {
            if(mit->second==minimo)
                minimiFinali.push_back(mit->first);
        }
    }
    else //se è pte
    {
        for(map<Inquilino*,int>::iterator mit=coppie.begin(); mit!=coppie.end(); ++mit)
        {
            minimiFinali.push_back(mit->first);
        }
    }

    return minimiFinali;

}

Inquilino * Calendario::BufferInquilini::restituisciIlMinimo(dList<Calendario::Giorno>::iterator iteratoreMinimo,bool pte)
{
    vector<Inquilino*> minimi=trovaMinimi(iteratoreMinimo,pte);
//    cout<<"--------"<<endl;
//    for(vector<Inquilino*>::iterator it=minimi.begin(); it!=minimi.end(); ++it) //DEBUG
//        cout<<(*it)->getNome()<<endl;

    vector<Inquilino*>::iterator j=minimi.begin();

        while(j!=minimi.end())
        {
            if(*_index==*j)
            {
                //cout<<(*_index)->getNome()<<" ";
                return *_index;
            }
            else ++j;
        }


}
