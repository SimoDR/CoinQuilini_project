#include "admin.h"

Admin::Admin(string user, string pw) : Inquilino(user, pw) {}
unsigned short int Admin::isAdmin() const
{
    return 1;
}
bool Admin::puoposporre()
{
    return true;
}

std::string Admin::getLabel() const
{
    return "ADMIN";
}
