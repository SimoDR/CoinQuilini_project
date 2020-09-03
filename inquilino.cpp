#include "inquilino.h"

Inquilino::Inquilino(const string& user, const string& pw, float credeb, unsigned short int punteggio) :
    _user(user), _password(pw), _creditoDebito(credeb),
    _punteggio(punteggio > _puntiMax ? _puntiMax : punteggio) {}

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
    xmlOutput.writeTextElement("creditodebito", QString::fromStdString(std::to_string(_creditoDebito)));
    xmlOutput.writeTextElement("punteggio", QString::fromStdString(std::to_string(_punteggio)));
    xmlOutput.writeEndElement();
}

unsigned short int Inquilino::getPunteggio() const{
    return _punteggio;
}

std::string Inquilino::showPunteggio() const
{
    string messaggio="PUNTEGGIO\n\nPunti: "+std::to_string(_punteggio)+"\n"
            + "Facoltà di posporre: ";
    if (_punteggio >= _sogliaPosponi) messaggio+="si";
    else messaggio+="no";
    return messaggio;
}

std::string Inquilino::showCreDeb() const
{
    string messaggio="BILANCIO\n\n";

    if(_creditoDebito!=0){
        messaggio+="Sei in ";

        if (_creditoDebito < 0) messaggio+="debito";
        else messaggio+="credito";

        messaggio+=" verso la casa\n";
    }

    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << _creditoDebito;
    std::string money = stream.str();

    return messaggio=messaggio+"Saldo: "+money+" €";
}

unsigned short int Inquilino::_puntiMin = 0;
unsigned short int Inquilino::_puntiMax = 100;
unsigned short int Inquilino::_sogliaPosponi = 40;
