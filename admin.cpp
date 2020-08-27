#include "admin.h"

Admin::Admin(const string& user, const string& pw) : Inquilino(user, pw) {}
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
