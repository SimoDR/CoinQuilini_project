#include "inquilino.h"

Inquilino::Inquilino(const string& user, const string& pw) : _user(user), _password(pw), _creditoDebito(0), _punteggio(0) {}

void Inquilino::modifica(const string& user, const string& pw)
{
    _user = user;
    _password = pw;
}
void Inquilino::setCD(const double& cd)
{
    _creditoDebito = _creditoDebito + cd;
}
void Inquilino::setPunteggio(const unsigned short int & punti)
{
    _punteggio += punti;
    if (_punteggio > _puntiMax)
        _punteggio = _puntiMax;
    else if (_punteggio < _puntiMin)
        _punteggio = _puntiMin;
}
unsigned short int Inquilino::isAdmin() const
{
    return 0;
}
bool Inquilino::puoPosporre() const
{
    return _punteggio >= _sogliaPosponi;
}

double Inquilino::getCreditoDebito() const{
    return _creditoDebito;
}

unsigned short int Inquilino::getPunteggio() const{
    return _punteggio;
}

unsigned short int Inquilino::_puntiMin = 0;
unsigned short int Inquilino::_puntiMax = 100;
unsigned short int Inquilino::_sogliaPosponi = 40;