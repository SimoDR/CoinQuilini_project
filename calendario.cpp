#include "calendario.h"

dList<Calendario::Giorno>::iterator Calendario::iteratoreFromData(dList<Giorno>::iterator iteratoreIniziale, const Data& inCuiInserire)
{
    bool trovato=false;
    while(!trovato)
    {

        if(iteratoreIniziale==_giorni.end() || iteratoreIniziale->_dataDelGiorno>inCuiInserire) //il giorno non c'è, bisogna crearlo
        {
            iteratoreIniziale=_giorni.insert(iteratoreIniziale,Giorno(inCuiInserire));
            trovato=true;
        }
        else if(iteratoreIniziale->_dataDelGiorno<inCuiInserire ) //non ho ancora raggiunto il giorno
        {

            ++iteratoreIniziale;
        }
        else if(iteratoreIniziale->_dataDelGiorno==inCuiInserire)//trovato, ritorna semplicemente
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

dList<Calendario::Giorno>::iterator Calendario::inizializzaCalendario(const Data& odierna)
{
    _giorni.insertBack(Giorno(odierna));
    return _giorni.begin();
}

Calendario::Calendario(const Data& odierna, const vector<Inquilino *> &listaInquilini): _iteratoreCorrente(inizializzaCalendario(odierna)), _buffer(listaInquilini) {}

void Calendario::aggiungiAlBuffer(Inquilino *nuovoInquilino)
{
    _buffer._inquilini.push_back(nuovoInquilino);
    _buffer._index=_buffer._inquilini.begin();
}

void Calendario::rimuoviInquilino(unsigned int pos) //da Debuggare
{
    bool trovato=false;
    unsigned int cont=0;
    cout<<pos<<" pos"<<endl;


    Inquilino * daRimuovere=nullptr;
    for(vector<Inquilino*>::iterator i=_buffer._inquilini.begin();i!=_buffer._inquilini.end() && !trovato; ++i)
    {
        cout<<pos<<" pos"<<endl;
        cout<<cont<<" cont"<<endl;

        if (cont==pos)
        {
            daRimuovere=*i;
            cout<<daRimuovere->getNome()<<" da rimuovere"<<endl;
            _buffer._inquilini.erase(i);
            trovato=true;
        }

        cont++;
    }
    cout<<"+*+*+*+*"<<endl;
    _buffer.stampaBuffer();
    cout<<"+*+*+*+*"<<endl;

    _buffer._index=_buffer._inquilini.begin();

    Incarico * daRiassegnare=nullptr;

    for(dList<Giorno>::iterator x=_iteratoreCorrente; x!=_giorni.end(); ++x) //riassegnamento automatico per ogni incarico che era dell'inquilino che se ne va
    {
        for(vector<Incarico*>::iterator y=(*x)._incarichiDelGiorno.begin(); y!=(*x)._incarichiDelGiorno.end(); ++y) //imposto a nullptr tutti gli incaricati da rimuovere della giornata
        {
            if((*y)->getIncaricato()==daRimuovere)
            {
                daRiassegnare=*y;
                daRiassegnare->setIncaricato(nullptr);

            }
        }
        for(vector<Incarico*>::iterator y=(*x)._incarichiDelGiorno.begin(); y!=(*x)._incarichiDelGiorno.end(); ++y) //riassegno tutti gli incaricati impostati a nullptr
        {
            if((*y)->getIncaricato()==nullptr)
            {
                daRiassegnare=*y;
                daRiassegnare->setIncaricato(ottieniIncaricato(x));
                _buffer.avanza();
            }
        }
    }

}

Inquilino * Calendario:: ottieniIncaricato(dList<Calendario::Giorno>::iterator iteratoreIniziale)
{
    return _buffer.restituisciIlMinimo(iteratoreIniziale);

}

void Calendario::incrementaData()
{
    Data dataOdierna=_iteratoreCorrente->_dataDelGiorno;
    dList<Giorno>::iterator giornoSuccessivo=++_iteratoreCorrente;
    if(_iteratoreCorrente->_incarichiDelGiorno.empty()) //se non ci sono incarichi nel giorno odierno
    {
        giornoSuccessivo=_giorni.remove(_iteratoreCorrente);
    }
    if(giornoSuccessivo==_giorni.end() || giornoSuccessivo->_dataDelGiorno!=dataOdierna+1)//se il nodo successivo non corrisponde al giorno successivo del calendario oppure è pte
        _iteratoreCorrente=_giorni.insert(giornoSuccessivo,Giorno(dataOdierna+1));

}

Incarico *Calendario::trovaIncarico(const Data &dataIncarico, int indiceIncarico)
{
    dList<Giorno>::iterator giornoIncarico=iteratoreFromData(_iteratoreCorrente,dataIncarico);

    int indice=0;
    for(vector<Incarico*>::iterator it=giornoIncarico->_incarichiDelGiorno.begin(); it!=giornoIncarico->_incarichiDelGiorno.end(); ++it)
    {
        if(indice==indiceIncarico)
        {
            return *it;
        }
        indice++;
    }

}





void Calendario::insert(Incarico * daInserire, Data & dataInCuiInserire, int numeroOccorrenze, int cadenzaIncarico)
{
    bool assegnato=false;
    if(numeroOccorrenze==1 && daInserire->getIncaricato()!=nullptr) //è già stato assegnato
        assegnato=true;


    dList<Giorno>::iterator iteratoreIniziale=_iteratoreCorrente;

    Inquilino * incaricato=nullptr;
    dList<Giorno>::iterator iteratoreInCuiInserire;
    while(numeroOccorrenze>0)
    {

        iteratoreInCuiInserire=iteratoreFromData(iteratoreIniziale, dataInCuiInserire);

        if(!assegnato) incaricato=ottieniIncaricato(iteratoreInCuiInserire);

        //cout<<incaricato->getNome()<<": incaricato"<<endl; //debug

        cout<<daInserire->getNome()<<endl; //debug
        _buffer.avanza();

        if(!assegnato) daInserire->setIncaricato(incaricato);


        iteratoreInCuiInserire->_incarichiDelGiorno.push_back(daInserire->clone());

        dataInCuiInserire=dataInCuiInserire+cadenzaIncarico;
        iteratoreIniziale=iteratoreInCuiInserire;
        numeroOccorrenze--;
    }


}

void Calendario::remove(Incarico *daRimuovere, const Data &dataIncarico)
{
    bool rimosso=false;
    dList<Giorno>::iterator giornoIncarico=iteratoreFromData(_iteratoreCorrente,dataIncarico);
    for(vector<Incarico*>::iterator it=giornoIncarico->_incarichiDelGiorno.begin(); it!=giornoIncarico->_incarichiDelGiorno.end() && !rimosso; ++it)
    {
        if(daRimuovere==*it)
        {
            giornoIncarico->_incarichiDelGiorno.erase(it);
            rimosso=true;
        }
    }

    if(giornoIncarico->_incarichiDelGiorno.empty()) //se ora non c'è più neanche un incarico, tolgo il giorno perchè non serve più
        _giorni.remove(giornoIncarico);
}

void Calendario::posponiIncarico(Incarico * daPosporre, unsigned int quantoPosporre, const Data& dataIncarico)
{


    Data dataInCuiInserire=dataIncarico+quantoPosporre;
    bool possibilePosporre=daPosporre->posponi(dataInCuiInserire);


    if (possibilePosporre)
    {
       remove(daPosporre,dataIncarico); //rimuovo da dov'è
       dList<Giorno>::iterator iteratoreInCuiInserire=iteratoreFromData(_iteratoreCorrente, dataInCuiInserire);
       iteratoreInCuiInserire->_incarichiDelGiorno.push_back(daPosporre->clone());
       int decurtazione=daPosporre->calcolaPunteggio()/2;
       daPosporre->getIncaricato()->setPunteggio(decurtazione);

       showMessage(QString::fromStdString("Incarico posposto con successo! Tuttavia ti sono stati decurtati "+std::to_string(decurtazione)+" punti"));
    }
    else
        showMessage(QString::fromStdString("Impossibile posporre! L'incarico ha delle limitazioni che impediscono di posporlo al giorno "+dataInCuiInserire.dataToString()));
}

void Calendario::setCredito(Pagamento * p, vector<Inquilino*> & lista)
{
    if (p->getSvolto()){
        p->getIncaricato()->setCD(p->getImporto());
        double quota = p->getImporto() / lista.size();
        for(vector<Inquilino*>::iterator it=lista.begin(); it!=lista.end(); ++it)
        {
            (*it)->setCD(-quota);
        }
    }
}

void Calendario::checkIncarichiSvolti()
{
    for(vector<Incarico*>::iterator it=_iteratoreCorrente->_incarichiDelGiorno.begin(); it!=_iteratoreCorrente->_incarichiDelGiorno.end(); ++it)
    {
        if(!((*it)->getSvolto())) //se non è stato svolto
        {
            (*it)->getIncaricato()->setPunteggio((*it)->calcolaPunteggio());
            //MESSAGGIO: NON L'HAI SVOLTO!!
        }
        else
        {
            (*it)->getIncaricato()->setPunteggio((*it)->calcolaPunteggio());
        }
    }
}



Calendario::Giorno::Giorno(Data dataDelGiorno): _dataDelGiorno(dataDelGiorno) {}






Calendario::BufferInquilini::BufferInquilini(const vector<Inquilino *>& listaInquilini): _inquilini(listaInquilini), _index(_inquilini.begin()) {}

void Calendario::BufferInquilini::avanza()
{
    _index++;
    if(_index==_inquilini.end()) _index=_inquilini.begin();
}

vector<Inquilino *> Calendario::BufferInquilini::trovaMinimi(dList<Calendario::Giorno>::iterator iteratoreMinimo) //restituisce l'inquilino (o più di uno) che ha meno incarichi già programmati in una determinata data
{
    map<Inquilino*,int> coppie;
    map<Inquilino*,int>::iterator mitt;



    cout<<"-------"<<endl;
    for(vector<Inquilino*>::iterator it=_inquilini.begin(); it!=_inquilini.end(); ++it) //aggiungo gli inquilini, tutti con frequenza 0
    {
        coppie[*it]=0;
        cout<<(*it)->getNome()<<" stocazzo"<<endl;

    }
    cout<<"-------"<<endl;

    cout<<"*****"<<endl;
    for(map<Inquilino*,int>::iterator mit=coppie.begin(); mit!=coppie.end(); ++mit) //debug
    {
        cout<<(*mit).first->getNome()<<endl;
    }
    cout<<"*****"<<endl;



    vector<Inquilino*> finaliZero;
    vector<Inquilino*> minimiFinali;
    bool zero=false;



        for(vector<Incarico*>::iterator it=iteratoreMinimo->_incarichiDelGiorno.begin(); it!=iteratoreMinimo->_incarichiDelGiorno.end(); ++it)
        {
            cout<<(**it).getNome()<<" nome incarico"<<endl;

            if((**it).getIncaricato()) //se non è nullptr, cioè se non è da riassegnare
            {
                cout<<"stocazzo1"<<endl;
            mitt=coppie.find((**it).getIncaricato());
            cout<<(*mitt).first->getNome()<<": trovato"<<endl; //debug

            mitt->second++; //aumento la frequenza dell'inquilino trovato
            }
            cout<<"stocazzo"<<endl;


        }

        int minimo=INT_MAX;
        for(map<Inquilino*,int>::iterator mit=coppie.begin(); mit!=coppie.end(); ++mit)
        {
            if(mit->second<minimo)
                minimo=mit->second;
        }


        cout<<"Minimo="<<minimo<<endl; //debug


        for(map<Inquilino*,int>::iterator mit=coppie.begin(); mit!=coppie.end(); ++mit)
        {

            if(mit->second==0)
            {
                finaliZero.push_back(mit->first);
                cout<<mit->first->getNome()<<" "<<mit->second<<" : minimi finali"<<endl; //debug
                zero=true;
            }
            else if(mit->second==minimo && !zero)
            {
                minimiFinali.push_back(mit->first);
                 cout<<mit->first->getNome()<<" "<<mit->second<<" : minimi finali"<<endl; //debug
            }
        }


    return zero ? finaliZero : minimiFinali;

}

Inquilino * Calendario::BufferInquilini::restituisciIlMinimo(dList<Calendario::Giorno>::iterator iteratoreMinimo)
{
    vector<Inquilino*> minimi=trovaMinimi(iteratoreMinimo);
    cout<<"--------"<<endl;
    for(vector<Inquilino*>::iterator it=minimi.begin(); it!=minimi.end(); ++it) //DEBUG
        cout<<(*it)->getNome()<<": minimi trovati"<<endl;
    cout<<(*_index)->getNome()<<": indice"<<endl;
    cout<<"--------"<<endl;

    bool trovato=false;
    while(!trovato)
    {
        for(vector<Inquilino*>::iterator j=minimi.begin(); j!=minimi.end(); ++j)
        {
            if(*_index==*j)
            {
                trovato=true;
            }
        }
        if(!trovato) avanza();
     }
    cout<<(*_index)->getNome()<<" ";
    return *_index;

}

void Calendario::exportXml() const //salva solo gli incarichi del calendario, non il buffer (che viene creato nuovo a partire dalla lista inquilini)
{
    QFile file("calendario.xml");
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlOutput(&file);
    xmlOutput.setAutoFormatting(true);
    xmlOutput.writeStartDocument();
    xmlOutput.writeStartElement("CALENDARIO");


    for(dList<Giorno>::const_iterator x=_giorni.cbegin(); x!=_giorni.cend(); ++x)
    {
        for(vector<Incarico*>::const_iterator y=(*x)._incarichiDelGiorno.cbegin(); y!=(*x)._incarichiDelGiorno.cbegin(); ++y)
        {
            xmlOutput.writeTextElement("DATA", QString::fromStdString((x->_dataDelGiorno).dataToString()));
            (*y)->exportXml(xmlOutput);
        }
    }

    xmlOutput.writeEndElement();
    xmlOutput.writeEndDocument();
    file.close();
}



