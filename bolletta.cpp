#include "bolletta.h"

Bolletta* Bolletta::clone() const {return new Bolletta(*this);}

bool Bolletta::posponi(const Data d) const
{
    return d < _dataLimite ? true : false;
}
