#ifndef CALENDARIO_H
#define CALENDARIO_H
#include "data.h"

class Calendario
{
private:
    class Giorno
    {
        Data _dataDelGiorno;
        vector<Incarico*> _incarichiDelGiorno;


    }

    dList<Giorno> _giorni;
    dList<Giorno>::iterator _giornoCorrente;

public:
    Calendario();
};

#endif // CALENDARIO_H
