#include "inquilino.h"

Inquilino::Inquilino(const string& user, const string& pw) : _user(user), _password(pw), _creditoDebito(0), _punteggio(0) {}

void Inquilino::modifica(string user, string pw)
{
    _user = user;
    _password = pw;
}
void Inquilino::setCD(double cd)
{
    _creditoDebito = _creditoDebito + cd;
}
void Inquilino::setPunteggio(short int punti)
{
    _punteggio = _punteggio + punti;
    if (_punteggio > _puntiMax)
        _punteggio = _puntiMax;
    else if (_punteggio < _puntiMin)
        _punteggio = _puntiMin;
}
unsigned short Inquilino::isAdmin()
{
    return 0;
}
bool Inquilino::puoPosporre()
{
    if (_punteggio >= _sogliaPosponi)
        return true;
    return false;
}

short int Inquilino::_puntiMin = 0;
short int Inquilino::_puntiMax = 0;
short int Inquilino::_sogliaPosponi = 0;