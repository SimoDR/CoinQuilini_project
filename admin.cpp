#include "admin.h"

Admin::Admin(const string& user, const string& pw, float credeb, unsigned short punteggio) : Inquilino(user, pw, credeb, punteggio) {}

unsigned short int Admin::isAdmin() const
{
    return 1;
}

void Admin::exportXml(QXmlStreamWriter &xmlOutput) const
{
    Inquilino::exportXml(xmlOutput);
}

std::string Admin::getLabel() const
{
    return "ADMIN";
}
