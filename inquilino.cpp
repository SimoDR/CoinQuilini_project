#include "inquilino.h"

Inquilino::Inquilino(const string& user, const string& pw) : _user(user), _password(pw), _creditoDebito(0), _punteggio(0) {}

void Inquilino::modifica(const string& user, const string& pw)
{
    _user = user;
    _password = pw;
}
void Inquilino::setCD(float cd)
{
    _creditoDebito += cd;
}
void Inquilino::setPunteggio(short int punti)
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

float Inquilino::getCreditoDebito() const{
    return _creditoDebito;
}
std::string Inquilino::getNome() const
{
    return _user;
}

bool Inquilino::isLogged(const std::string &user, const std::string &pw) const
{
    if (user==_user &&pw==_password)
        return true;
    return false;
}

std::string Inquilino::getLabel() const
{
    return "INQUILINO";
}

void Inquilino::exportXml(QXmlStreamWriter & xmlOutput) const
{
    xmlOutput.writeStartElement(QString::fromStdString(getLabel()));
    xmlOutput.writeTextElement("nome", QString::fromStdString(_user));
    xmlOutput.writeTextElement("password", QString::fromStdString(_password));
    xmlOutput.writeEndElement();
}

unsigned short int Inquilino::getPunteggio() const{
    return _punteggio;
}

unsigned short int Inquilino::_puntiMin = 0;
unsigned short int Inquilino::_puntiMax = 100;
unsigned short int Inquilino::_sogliaPosponi = 40;
