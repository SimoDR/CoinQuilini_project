#include "data.h"


unsigned short int Data::_maxMesi=12;

unsigned short int Data:: _minMesi=1;

unsigned short int Data::_minAnni=1980;

unsigned short int Data::_maxAnni=9999;

unsigned short int Data:: _minGiorni=1;


Data::Data(unsigned short int giorno,unsigned short int mese,unsigned short int anno): _giornoCorrente(giorno), _meseCorrente(mese), _annoCorrente(anno), _maxGiorni(31)
{
    try {
        checkLimiti();
    } catch(std::domain_error * exc) {
        cout<<exc->what()<<endl;
    }
}

Data::Data(std::string inputString)
{
    try {
        parsingDaStringa(inputString);
    } catch (std::invalid_argument * exc) {
        cout<<exc->what()<<endl;
    }

    try {
        checkLimiti();
    } catch(std::domain_error * exc) {
        cout<<exc->what()<<endl;
    }

}


void Data::setMaxGiorni()
{
    if (_meseCorrente==1 || _meseCorrente==3 || _meseCorrente==5 || _meseCorrente==7 || _meseCorrente==8 || _meseCorrente==10 || _meseCorrente==12)
        _maxGiorni=31;
    else if(_meseCorrente==2)
    {
        if (isBisestile())
            _maxGiorni=29;
        else
            _maxGiorni=28;
    }
    else if(_meseCorrente==4 || _meseCorrente==6 || _meseCorrente==9 || _meseCorrente==11)
        _maxGiorni=30;
}

bool Data::isBisestile() const
{
    unsigned short int ultimeDueCifre=_annoCorrente%100;
    if(ultimeDueCifre==0 && _annoCorrente%400==0) return true;
    else if (ultimeDueCifre!=0 && ultimeDueCifre%4==0) return true;
    else return false;
}

void Data::checkLimiti()
{
    setMaxGiorni();
    if(_giornoCorrente>_maxGiorni || _giornoCorrente<_minGiorni)
    {
        throw new OutOfBoundException("giorno");
    }
    if(_meseCorrente>_maxMesi || _meseCorrente<_minMesi)
    {
        throw new OutOfBoundException("mese");
    }
    if(_annoCorrente<_minAnni || _annoCorrente>_maxAnni)
        throw new OutOfBoundException("anno");
}

void Data::aggiustaLimiti()
{
    if(_meseCorrente<=_maxMesi && _meseCorrente>=_minMesi) setMaxGiorni();

    if(_meseCorrente<_minMesi) _meseCorrente=_minMesi;
    else if(_meseCorrente>_maxMesi)
    {
        _meseCorrente=_meseCorrente-_maxMesi;
        _annoCorrente++;
        aggiustaLimiti();
    }

    if(_giornoCorrente<_minGiorni) _giornoCorrente=_minGiorni;
    else if(_giornoCorrente>_maxGiorni)
    {
        _giornoCorrente=_giornoCorrente-_maxGiorni;
        _meseCorrente++;
        aggiustaLimiti();
    }

    if(_annoCorrente<_minAnni) _annoCorrente=_minAnni;
    else if(_annoCorrente>_maxAnni)
    {
        throw new OutOfBoundException("anno");
    }

}

void Data::parsingDaStringa(string inputString)
{
    short int barFound=0;
    string stringGiorno;
    string stringMese;
    string stringAnno;
    for(string::iterator it=inputString.begin(); it!=inputString.end(); ++it)
    {
        if(*it=='/')
            barFound++;
        else
        {
            if(barFound==0)
                stringGiorno=stringGiorno+(*it);
            if(barFound==1)
                stringMese=stringMese+(*it);
            if(barFound==2)
                stringAnno=stringAnno+(*it);
        }
    }
    if(stringGiorno.empty() || stringMese.empty() || stringAnno.empty())
        throw new std::invalid_argument("Parametri inseriti non correttamente");
    else
    {
        std::stringstream streamGiorno(stringGiorno);
        std::stringstream streamMese(stringMese);
        std::stringstream streamAnno(stringAnno);

        streamGiorno >> _giornoCorrente;
        streamMese >> _meseCorrente;
        streamAnno >> _annoCorrente;
    }
}

const Data& Data::operator+(unsigned short addendo)
{
    _giornoCorrente=_giornoCorrente+addendo;
    aggiustaLimiti();
    return *this;
}

const Data &Data::aggiungiSettimane(unsigned short numero)
{
    for(unsigned short int i=0;i<numero;i++)
    {
        this->operator+(7);
        aggiustaLimiti();
    }
    return *this;
}

const Data &Data::aggiungiMesi(unsigned short numero)
{
    for(unsigned short int i=0;i<numero;i++)
    {
        this->operator+(30);
        aggiustaLimiti();
    }
    return *this;
}

const Data &Data::aggiungiAnni(unsigned short numero)
{
    for(unsigned short int i=0;i<numero;i++)
    {
        _annoCorrente++;
        aggiustaLimiti();
    }
    return *this;
}


std::ostream& operator<<(std::ostream& os,const Data& d)
{
    os<<d._giornoCorrente<<"/"<<d._meseCorrente<<"/"<<d._annoCorrente;
    return os;
}
