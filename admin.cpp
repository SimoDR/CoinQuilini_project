#include "admin.h"

Admin::Admin(const string& user, const string& pw) : Inquilino(user, pw) {}

unsigned short int Admin::isAdmin() const
{
    return 1;
}
