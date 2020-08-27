#include "data.h"

unsigned short int Data::_maxMesi = 12;

unsigned short int Data::_minMesi = 1;

unsigned short int Data::_minAnni = 1980;

unsigned short int Data::_maxAnni = 9999;

unsigned short int Data::_minGiorni = 1;

Data::Data(unsigned short int giorno, unsigned short int mese, unsigned short int anno) : _giornoCorrente(giorno), _meseCorrente(mese), _annoCorrente(anno), _maxGiorni(31)
{
    try
    {
        checkLimiti();
    }
    catch(std::domain_error * e)
    {
        showMessage(QString::fromStdString(e->what()));
    }
}

std::string Data::dataToString() const
{
    string daRitornare=std::to_string(_giornoCorrente)+"/"+std::to_string(_meseCorrente)+"/"+std::to_string(_annoCorrente);
    return daRitornare;
}

Data::Data(std::string inputString)
{
    try
    {
        parsingDaStringa(inputString);
    }
    catch (std::invalid_argument *e)
    {
        showMessage(QString::fromStdString(e->what()));
    }

    try
    {
        checkLimiti();
    }
    catch (std::domain_error *e)
    {
        showMessage(QString::fromStdString(e->what()));
    }
}

void Data::setMaxGiorni()
{
    if (_meseCorrente == 1 || _meseCorrente == 3 || _meseCorrente == 5 || _meseCorrente == 7 || _meseCorrente == 8 || _meseCorrente == 10 || _meseCorrente == 12)
        _maxGiorni = 31;
    else if (_meseCorrente == 2)
    {
        if (isBisestile())
            _maxGiorni = 29;
        else
            _maxGiorni = 28;
    }
    else if (_meseCorrente == 4 || _meseCorrente == 6 || _meseCorrente == 9 || _meseCorrente == 11)
        _maxGiorni = 30;
}

bool Data::isBisestile() const
{
    unsigned short int ultimeDueCifre = _annoCorrente % 100;
    if (ultimeDueCifre == 0 && _annoCorrente % 400 == 0)
        return true;
    else if (ultimeDueCifre != 0 && ultimeDueCifre % 4 == 0)
        return true;
    else
        return false;
}

void Data::checkLimiti()
{

    setMaxGiorni();
    if (_giornoCorrente > _maxGiorni || _giornoCorrente < _minGiorni)
    {
        throw new OutOfBoundException("giorno");
    }
    if (_meseCorrente > _maxMesi || _meseCorrente < _minMesi)
    {
        throw new OutOfBoundException("mese");
    }
    if (_annoCorrente < _minAnni || _annoCorrente > _maxAnni)
        throw new OutOfBoundException("anno");


}

void Data::aggiustaLimiti()
{

    if (_meseCorrente <= _maxMesi && _meseCorrente >= _minMesi)
        setMaxGiorni();

    if (_meseCorrente < _minMesi)
        _meseCorrente = _minMesi;
    else if (_meseCorrente > _maxMesi)
    {
        _meseCorrente = _meseCorrente - _maxMesi;
        _annoCorrente++;
        aggiustaLimiti();
    }

    if (_giornoCorrente < _minGiorni)
        _giornoCorrente = _minGiorni;
    else if (_giornoCorrente > _maxGiorni)
    {
        _giornoCorrente = _giornoCorrente - _maxGiorni;
        _meseCorrente++;
        aggiustaLimiti();
    }

    if (_annoCorrente < _minAnni)
        _annoCorrente = _minAnni;

    else if (_annoCorrente > _maxAnni)
    {
        throw new OutOfBoundException("anno");
    }


}

void Data::parsingDaStringa(string inputString)
{
    short int barFound = 0;
    string stringGiorno;
    string stringMese;
    string stringAnno;
    for (string::iterator it = inputString.begin(); it != inputString.end(); ++it)
    {
        if (*it == '/')
            barFound++;
        else
        {
            if (barFound == 0)
                stringGiorno = stringGiorno + (*it);
            if (barFound == 1)
                stringMese = stringMese + (*it);
            if (barFound == 2)
                stringAnno = stringAnno + (*it);
        }
    }


    if (stringGiorno.empty() || stringMese.empty() || stringAnno.empty())
        throw new std::invalid_argument("Parametri inseriti non correttamente");
    else
    {
        _giornoCorrente = stoi(stringGiorno);
        _meseCorrente = stoi(stringMese);
        _annoCorrente = stoi(stringAnno);
    }



}

Data Data::operator+(unsigned short addendo) const
{
    Data daRitornare(*this);
    daRitornare._giornoCorrente = _giornoCorrente + addendo;
    daRitornare.aggiustaLimiti();
    return daRitornare;
}

int Data::differenza(const Data & daRaggiungere) const
{
    Data diPartenza(*this);
    int count=0;
    while(diPartenza<daRaggiungere)
    {
        diPartenza=diPartenza+1;
        count++;
    }
    return count;
}







bool Data::operator<(const Data & d) const
{
    if (_annoCorrente<d._annoCorrente)
        return true;
    else if(_annoCorrente>d._annoCorrente)
        return false;
    else // _annoCorrente==d._annoCorrente
    {
        if (_meseCorrente<d._meseCorrente)
            return true;
        else if(_meseCorrente>d._meseCorrente)
            return false;
        else // _meseCorrente==d._meseCorrente
        {
            if (_giornoCorrente<d._giornoCorrente)
                return true;
            else if(_giornoCorrente>d._giornoCorrente)
                return false;
            else // _giornoCorrente==d._giornoCorrente
                return false;
        }
    }
}

bool Data::operator>(const Data & d) const
{
    if (_annoCorrente>d._annoCorrente)
        return true;
    else if(_annoCorrente<d._annoCorrente)
        return false;
    else // _annoCorrente==d._annoCorrente
    {
        if (_meseCorrente>d._meseCorrente)
            return true;
        else if(_meseCorrente<d._meseCorrente)
            return false;
        else // _meseCorrente==d._meseCorrente
        {
            if (_giornoCorrente>d._giornoCorrente)
                return true;
            else if(_giornoCorrente<d._giornoCorrente)
                return false;
            else // _giornoCorrente==d._giornoCorrente
                return false;
        }
    }
}

bool Data::operator==(const Data & d) const
{
    return _annoCorrente==d._annoCorrente && _meseCorrente==d._meseCorrente && _giornoCorrente==d._giornoCorrente;
}

bool Data::operator !=(const Data & d) const
{
    return _annoCorrente!=d._annoCorrente || _meseCorrente!=d._meseCorrente || _giornoCorrente!=d._giornoCorrente;
}



std::ostream &operator<<(std::ostream &os, const Data &d)
{
    os << d._giornoCorrente << "/" << d._meseCorrente << "/" << d._annoCorrente;
    return os;
}


