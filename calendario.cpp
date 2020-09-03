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



bool Calendario::checkIteratore(dList<Calendario::Giorno>::const_iterator iteratoreDaControllare) const
{
    if(iteratoreDaControllare==_giorni.end())
        return true;
    else return false;
}



dList<Calendario::Giorno>::iterator Calendario::inizializzaCalendario(const Data& odierna)
{
    dList<Calendario::Giorno>::iterator iteratoreInCuiInserire=iteratoreFromData(_giorni.begin(),odierna);
    return iteratoreInCuiInserire;
}



void Calendario::aggiungiAlBuffer(Inquilino *nuovoInquilino)
{
    _buffer._inquilini.push_back(nuovoInquilino);
    _buffer._index=_buffer._inquilini.begin();
}



void Calendario::rimuoviInquilino(unsigned int pos) //da Debuggare
{
    bool trovato=false;
    unsigned int cont=0;

    Inquilino * daRimuovere=nullptr;
    vector<Inquilino*>::iterator i=_buffer._inquilini.begin();
    while(i!=_buffer._inquilini.end() && !trovato)
    {
        if (cont==pos)
        {
            daRimuovere=*i;
            _buffer._inquilini.erase(i);
            trovato=true;
        }
        else
        {
            ++i;
            cont++;
        }
    }

    removeIncarichiPassatiInquilino(daRimuovere);
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
    // delete daRimuovere; non serve, cancello in listaInquilini


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



const Data &Calendario::getDataDiOggi() const
{
    return _iteratoreCorrente->_dataDelGiorno;
}



Incarico *Calendario::trovaIncarico(const Data &dataIncarico, unsigned int indiceIncarico, bool passato)
{
    dList<Giorno>::iterator giornoIncarico;
    if(passato) giornoIncarico=iteratoreFromData(_giorni.begin(),dataIncarico);
    else giornoIncarico=iteratoreFromData(_iteratoreCorrente,dataIncarico);

    bool trovato=false;
    unsigned int indice=0;
    vector<Incarico*>::const_iterator cit=giornoIncarico->_incarichiDelGiorno.begin();
    while(cit!=giornoIncarico->_incarichiDelGiorno.end() && !trovato)
    {
        if(indice==indiceIncarico)
        {
            trovato=true;
        }
        else
        {
            indice++;
            ++cit;
        }
    }
    return *cit;
}



void Calendario::insert(Incarico * daInserire, Data  dataInCuiInserire, int numeroOccorrenze, int cadenzaIncarico, int scostamentoDataLimite, bool import)
{
    bool assegnato=false;
    if(daInserire->getIncaricato()!=nullptr) //è già stato assegnato
        assegnato=true;


    dList<Giorno>::iterator iteratoreIniziale=_iteratoreCorrente;
    dList<Giorno>::iterator iteratoreInizialeImport=_giorni.begin();

    Inquilino * incaricato=nullptr;
    dList<Giorno>::iterator iteratoreInCuiInserire;
    while(numeroOccorrenze>0)
    {
        if(import) iteratoreInCuiInserire=iteratoreFromData(iteratoreInizialeImport, dataInCuiInserire);
        else iteratoreInCuiInserire=iteratoreFromData(iteratoreIniziale, dataInCuiInserire);

        if(!assegnato) incaricato=ottieniIncaricato(iteratoreInCuiInserire);
        _buffer.avanza();

        if(!assegnato) daInserire->setIncaricato(incaricato);

        daInserire->setDataLimite(dataInCuiInserire+scostamentoDataLimite);

        if(import && daInserire->getSvolto()==false && iteratoreInCuiInserire->_dataDelGiorno<_iteratoreCorrente->_dataDelGiorno) //se non è stato svolto, è import ed è nel passato
        {
            daInserire->getIncaricato()->setPunteggio(-daInserire->calcolaPunteggio()); //tolgo punti all'interessato
            daInserire->setSvolto(); //imposto svolto che così non sia rilevabile alla prossima apertura
            _nonSvoltiImport.push_back(daInserire->getIncaricato()->getNome()); //segno nome
            _nonSvoltiImport.push_back(daInserire->getLabel()); //tipo incarico
            _nonSvoltiImport.push_back(iteratoreInCuiInserire->_dataDelGiorno.dataToString()); //data dell'incarico
            _nonSvoltiImport.push_back(std::to_string(daInserire->calcolaPunteggio())); //punti sottratti
        }

        iteratoreInCuiInserire->_incarichiDelGiorno.push_back(daInserire->clone());

        dataInCuiInserire=dataInCuiInserire+cadenzaIncarico;
        if(!import) iteratoreIniziale=iteratoreInCuiInserire;
        else iteratoreInizialeImport=iteratoreInCuiInserire;
        numeroOccorrenze--;
    }
    delete daInserire;


}



void Calendario::remove(const Data &dataIncarico, unsigned int indiceIncarico)
{
    bool passato=false;
    if(dataIncarico<_iteratoreCorrente->_dataDelGiorno) passato=true;
    dList<Giorno>::iterator giornoIncarico;
    if(passato) giornoIncarico=iteratoreFromData(_giorni.begin(),dataIncarico);
    else giornoIncarico=iteratoreFromData(_iteratoreCorrente,dataIncarico);

    bool rimosso=false;
    unsigned int pos=0;
    bool isEmpty=false;
    Incarico * daRimuovere=nullptr;
    vector<Incarico*>::iterator it=giornoIncarico->_incarichiDelGiorno.begin();
    while(!rimosso && it!=giornoIncarico->_incarichiDelGiorno.end()  )
    {
        if(pos==indiceIncarico)
        {
            isEmpty=giornoIncarico->_incarichiDelGiorno.empty();
            daRimuovere=*it;
            it=giornoIncarico->_incarichiDelGiorno.erase(it);
            rimosso=true;
        }
        else {
            ++it;
            pos++;
        }

    }
    delete daRimuovere;

    if(isEmpty) //se ora non c'è più neanche un incarico, tolgo il giorno perchè non serve più
        _giorni.remove(giornoIncarico);
}



void Calendario::posponiIncaricoCalendario(unsigned int indiceIncarico, unsigned int quantoPosporre, const Data& dataIncarico)
{
    Data dataInCuiInserire=dataIncarico+quantoPosporre;

    Incarico * daPosporre=trovaIncarico(dataIncarico,indiceIncarico);
    bool possibilePosporre=daPosporre->posponi(dataInCuiInserire);
    if(daPosporre->getSvolto())
        showMessage("Attenzione! Non è possibile posporre un incarico già svolto");
    else {

        if (possibilePosporre)
        {
            Incarico * cloned=daPosporre->clone();
            remove(dataIncarico,indiceIncarico); //rimuovo da dov'è
            dList<Giorno>::iterator iteratoreInCuiInserire=iteratoreFromData(_iteratoreCorrente, dataInCuiInserire);
            iteratoreInCuiInserire->_incarichiDelGiorno.push_back(cloned);
            int decurtazione=
                cloned->calcolaPunteggio()/2+quantoPosporre > (cloned->calcolaPunteggio())/2 ?
                    (cloned->calcolaPunteggio())/2 : cloned->calcolaPunteggio()/2+quantoPosporre;
            cloned->getIncaricato()->setPunteggio(-decurtazione);

            showSuccess(QString::fromStdString("Incarico posposto con successo! Tuttavia ti sono stati decurtati "+std::to_string(decurtazione)+(decurtazione>1 ? " punti" : "punto")));
        }
        else
            showMessage(QString::fromStdString("Impossibile posporre! L'incarico ha delle limitazioni che impediscono di posporlo al giorno "+dataInCuiInserire.dataToString()));

    }
}



void Calendario::setCredito(Pagamento * p, vector<Inquilino*> & lista) const
{
    if (p->getSvolto()){
        p->getIncaricato()->setCD(p->getImporto());
        float quota = p->getImporto() / lista.size();
        for(vector<Inquilino*>::iterator it=lista.begin(); it!=lista.end(); ++it)
        {
            (*it)->setCD(-quota);
        }
    }
}



void Calendario::checkIncarichiSvolti() const
{
    string inadempienti="Attenzione: è scattata la mezzanotte e alcuni inquilini non hanno svolto gli incarichi assegnati per ieri. A costoro verranno decurtati dei punti: \n";

    bool almenoUno=false;

    for(vector<Incarico*>::iterator it=_iteratoreCorrente->_incarichiDelGiorno.begin(); it!=_iteratoreCorrente->_incarichiDelGiorno.end(); ++it)
    {
        if(!((*it)->getSvolto())) //se non è stato svolto
        {
            almenoUno=true;
            inadempienti.append((*it)->getIncaricato()->getNome());
            inadempienti.append(" non ha svolto l'incarico ");
            inadempienti.append((*it)->getLabel());
            inadempienti.append(" (-"+std::to_string((*it)->calcolaPunteggio())+ ((*it)->calcolaPunteggio() > 1 ? +" punti)" : " punto)"));
            inadempienti.append(".\n");
            (*it)->getIncaricato()->setPunteggio(-(*it)->calcolaPunteggio());
            (*it)->setSvolto();
        }
        else
        {
            (*it)->getIncaricato()->setPunteggio((*it)->calcolaPunteggio()); //da togliere
        }
    }
    string details="I sopracitati incarichi sono ora impostati come svolti. Sara' compito degli inquilini calendarizzarli nuovamente.";
    if(almenoUno)
    {
        showMessage(QString::fromStdString(inadempienti),QString::fromStdString(details));
    }
}



void Calendario::checkIncarichiSvoltiPassato()
{
    string inadempienti;
    inadempienti="Attenzione: alcuni inquilini non hanno svolto gli incarichi assegnati nei giorni scorsi. A costoro verranno decurtati dei punti: \n\n";
    vector<string>::const_iterator cit=_nonSvoltiImport.begin();
    bool almenoUno=false;
    while(cit!=_nonSvoltiImport.end())
    {
        almenoUno=true;
        inadempienti.append(*cit);
        ++cit;
        inadempienti.append(" non ha svolto l'incarico ");
        inadempienti.append(*cit);
        ++cit;
        inadempienti.append(" programmato per il giorno ");
        inadempienti.append(*cit);
        ++cit;
        inadempienti.append(" (-"+ *cit + (std::stoi(*cit) > 1 ? +" punti)" : " punto)"));
        inadempienti.append(".\n");
        ++cit;
    }
    string details="I sopracitati incarichi sono ora impostati come svolti. Sara' compito degli inquilini calendarizzarli nuovamente.";
    if(almenoUno)
    {
        showMessage(QString::fromStdString(inadempienti),QString::fromStdString(details));
    }
    _nonSvoltiImport.clear();
}



Calendario::Giorno::Giorno(Data dataDelGiorno): _dataDelGiorno(dataDelGiorno) {}



Calendario::BufferInquilini::BufferInquilini(const vector<Inquilino *>& listaInquilini): _inquilini(listaInquilini), _index(_inquilini.begin()) {}





void Calendario::BufferInquilini::avanza()
{
    _index++;
    if(_index==_inquilini.end()) _index=_inquilini.begin();
}



Inquilino * Calendario::BufferInquilini::getInquilino(std::string nome) const
{
    vector<Inquilino*>::const_iterator cit;
    for(cit=_inquilini.begin(); cit!=_inquilini.end(); ++cit)
    {
        if((*cit)->getNome()==nome)
            return *cit;
    }
    return nullptr; //non trovato
}



vector<Inquilino *> Calendario::BufferInquilini::trovaMinimi(dList<Calendario::Giorno>::iterator iteratoreMinimo)  //restituisce l'inquilino (o più di uno) che ha meno incarichi già programmati in una determinata data
{
    map<Inquilino*,int> coppie;
    map<Inquilino*,int>::iterator mitt;

    for(vector<Inquilino*>::iterator it=_inquilini.begin(); it!=_inquilini.end(); ++it) //aggiungo gli inquilini, tutti con frequenza 0
    {
        coppie[*it]=0;

    }

    vector<Inquilino*> finaliZero;
    vector<Inquilino*> minimiFinali;
    bool zero=false;

    for(vector<Incarico*>::iterator it=iteratoreMinimo->_incarichiDelGiorno.begin(); it!=iteratoreMinimo->_incarichiDelGiorno.end(); ++it)
    {

        if((**it).getIncaricato()) //se non è nullptr, cioè se non è da riassegnare
        {
            mitt=coppie.find((**it).getIncaricato());
            mitt->second++; //aumento la frequenza dell'inquilino trovato
        }
    }

    int minimo=INT_MAX;
    for(map<Inquilino*,int>::iterator mit=coppie.begin(); mit!=coppie.end(); ++mit)
    {
        if(mit->second<minimo)
            minimo=mit->second;
    }

    for(map<Inquilino*,int>::iterator mit=coppie.begin(); mit!=coppie.end(); ++mit)
    {

        if(mit->second==0)
        {
            finaliZero.push_back(mit->first);
            zero=true;
        }
        else if(mit->second==minimo && !zero)
        {
            minimiFinali.push_back(mit->first);
        }
    }

    return zero ? finaliZero : minimiFinali;
}



Inquilino * Calendario::BufferInquilini::restituisciIlMinimo(dList<Calendario::Giorno>::iterator iteratoreMinimo)
{
    vector<Inquilino*> minimi=trovaMinimi(iteratoreMinimo);

    bool trovato=false;
    while(!trovato)
    {
        for(vector<Inquilino*>::iterator j=minimi.begin(); j!=minimi.end(); ++j)
        {
            if(*_index==*j)
                trovato=true;
        }
        if(!trovato) avanza();
    }
    return *_index;

}



Calendario::Calendario(const Data& odierna, const vector<Inquilino *> &listaInquilini): _iteratoreCorrente(inizializzaCalendario(odierna)) ,_buffer(listaInquilini)
{
    importXml();
}



Calendario::~Calendario()
{
    exportXml();
    for(dList<Giorno>::iterator x=_giorni.begin(); x!=_giorni.end(); ++x)
    {
        for(vector<Incarico*>::iterator y=(*x)._incarichiDelGiorno.begin(); y!=(*x)._incarichiDelGiorno.end(); ++y)
        {
            delete *y;
        }
    }
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
        for(vector<Incarico*>::const_iterator y=(*x)._incarichiDelGiorno.cbegin(); y!=(*x)._incarichiDelGiorno.end(); ++y)
        {
            (*y)->exportXml(xmlOutput,(x->_dataDelGiorno).dataToString());
        }
    }

    xmlOutput.writeEndElement();
    xmlOutput.writeEndDocument();
    file.close();
}



void Calendario::importXml()
{
    QFile file("calendario.xml");
    try {
        if (file.open(QFile::ReadOnly | QFile::Text))
        {
            QXmlStreamReader xmlInput(&file);
            if (xmlInput.readNextStartElement())
            {
                if (xmlInput.name() == "CALENDARIO")
                {             
                    while(xmlInput.readNextStartElement())
                    {
                        vector<string> parametri(14,"\0");

                        if (xmlInput.name() == "SPESA") {
                            Spesa::importXml(xmlInput,parametri);
                        }
                        if (xmlInput.name() == "CUCINA") {
                            Cucina::importXml(xmlInput,parametri);
                        }
                        if (xmlInput.name() == "PULIZIA") {
                            Pulizia::importXml(xmlInput,parametri);
                        }
                        if (xmlInput.name() == "SPAZZATURA") {
                            Spazzatura::importXml(xmlInput,parametri);
                        }
                        if (xmlInput.name() == "BOLLETTA") {
                            Bolletta::importXml(xmlInput,parametri);
                        }

                        creaNuovoIncarico(parametri,true);
                        xmlInput.skipCurrentElement();
                    }

                }
                else
                    throw new std::runtime_error("Errore durante l'import del calendario");
            }
            else
                throw new std::runtime_error("Errore durante l'import del calendario");

            file.close();
        }
        else
            throw new std::runtime_error("Calendario non trovato");
    }
    catch(std::runtime_error * e)
    {
        showMessage(QString::fromStdString(e->what()));
    }

}



void Calendario::creaNuovoIncarico(const vector<string>& parametri,bool import)
{
    string nomeIncarico="\0";
    if(parametri[0]!="\0") nomeIncarico=parametri[0];

    string tipoIncarico="\0";
    if(parametri[1]!="\0") tipoIncarico=parametri[1];

    string nomeIncaricato="\0";
    if(parametri[2]!="\0") nomeIncaricato=parametri[2];

    int cadenzaIncarico=0;
    if(parametri[3]!="\0") cadenzaIncarico=std::stoi(parametri[3]);

    int tempoStimato=0;
    if(parametri[4]!="\0") tempoStimato=std::stoi(parametri[4]);

    unsigned short int stanzeDaPulire=0;
    if(parametri[5]!="\0") stanzeDaPulire=std::stoi(parametri[5]);

    unsigned short int numeroCommensali=0;
    if(parametri[6]!="\0") numeroCommensali=std::stoi(parametri[6]);

    unsigned short int numeroArticoli=0;
    if(parametri[7]!="\0") numeroArticoli=std::stoi(parametri[7]);

    float importo=0;
    if(parametri[8]!="\0") importo= std::stof(parametri[8]);

    int scostamento=0;
    if(parametri[9]!="\0") scostamento=std::stoi(parametri[9]);

    Data dataInizio;
    if(parametri[10]!="\0") dataInizio=parametri[10];

    if(!import) {
        try{
            if(dataInizio<getDataDiOggi())
                throw new std::invalid_argument("Attenzione! La data di inserimento dell'incarico dev'essere successiva alla data di oggi");
        }
        catch (std::invalid_argument *e)
        {
            showMessage(QString::fromStdString(e->what()));
        }
    }

    int numeroOccorrenze=1;
    if(parametri[11]!="\0") numeroOccorrenze=std::stoi(parametri[11]);


    try{
        if(numeroOccorrenze==0)
            throw new std::invalid_argument("Attenzione! Le occorrenze devono essere almeno una (incarico semplice)");
    }
    catch (std::invalid_argument *e)
    {
        showMessage(QString::fromStdString(e->what()));
    }


    bool svolto=false;
    if(parametri[12]!="\0")
    {
        if(parametri[12]=="si")
            svolto=true;
        else svolto=false;
    }

    string cosaButtare="\0";
    if(parametri[13]!="\0") cosaButtare=parametri[13];

    Incarico * i=nullptr;

    if (tipoIncarico=="Pulizia")
        i=new Pulizia(nomeIncarico,tempoStimato,stanzeDaPulire);
    else if(tipoIncarico=="Spesa")
        i=new Spesa(nomeIncarico,importo,tempoStimato,numeroArticoli);
    else if(tipoIncarico=="Spazzatura")
        i=new Spazzatura(nomeIncarico,cosaButtare,tempoStimato);
    else if(tipoIncarico=="Cucina")
        i=new Cucina(nomeIncarico,tempoStimato,numeroCommensali);
    else if(tipoIncarico=="Bolletta")
        i=new Bolletta(nomeIncarico,importo);

    if(nomeIncaricato!="\0") //assegnazione manuale dell'incaricato
    {
        i->setIncaricato(_buffer.getInquilino(nomeIncaricato));        
    }

    if(svolto) //per l'import
        i->setSvolto();

    insert(i,dataInizio,numeroOccorrenze,cadenzaIncarico,scostamento,import);
}



void Calendario::incarichiGiorno(const Data & giorno, vector<std::string> & tipiIncarichi, vector<string> & incaricati) const
{
    dList<Giorno>::const_iterator iteratoreIniziale=_giorni.begin();
    bool trovato=false;
    try{
        while(!trovato)
        {
            if(iteratoreIniziale==_giorni.end() || iteratoreIniziale->_dataDelGiorno>giorno) //il giorno non c'è
            {
                break;
                throw new std::runtime_error("Attenzione! Giorno non presente.");
            }
            else if(iteratoreIniziale->_dataDelGiorno<giorno ) //non ho ancora raggiunto il giorno
            {
                ++iteratoreIniziale;
            }
            else if(iteratoreIniziale->_dataDelGiorno==giorno)//trovato, ritorna semplicemente
            {
                trovato=true;
            }
        }
    }
    catch(std::runtime_error * e)
    {
        showMessage(QString::fromStdString(e->what()));
    }

    if(trovato)
    {
        for(vector<Incarico*>::const_iterator cit=iteratoreIniziale->_incarichiDelGiorno.begin(); cit!=iteratoreIniziale->_incarichiDelGiorno.end(); ++cit)
        {
            incaricati.push_back((*cit)->getIncaricato()->getNome());
            tipiIncarichi.push_back((*cit)->getLabel());
        }
    }
}



void Calendario::removeIncarichiPassatiInquilino(Inquilino * daRimuovere)
{
    dList<Giorno>::iterator x=_giorni.begin();
    Incarico * toDelete=nullptr;
    while(x!=_iteratoreCorrente)
    {
        vector<Incarico*>::iterator y=(*x)._incarichiDelGiorno.begin();
        while(y!=(*x)._incarichiDelGiorno.end())
        {
            if((*y)->getIncaricato()==daRimuovere)
            {
                toDelete=*y;
                y=(*x)._incarichiDelGiorno.erase(y);
                delete toDelete;
            }
            else
            {
                ++y;
            }
        }

        if((*x)._incarichiDelGiorno.empty()) //se dopo aver eliminato gli incarichi della giornata il giorno è vuoto, lo elimino
        {
            x=_giorni.remove(x);
        }
        else
        {
            ++x;
        }
    }
}

