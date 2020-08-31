#include "admin.h"

Admin::Admin(const string& user, const string& pw, float credeb, unsigned short punteggio) : Inquilino(user, pw, credeb, punteggio) {}
unsigned short int Admin::isAdmin() const
{
    return 1;
}
bool Admin::puoposporre() const
{
    return true;
}

std::string Admin::getLabel() const
{
    return "ADMIN";
}
