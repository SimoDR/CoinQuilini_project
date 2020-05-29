#include "admin.h"

Admin::Admin(string user, string pw) : Inquilino(user, pw) {}
unsigned short Admin::isAdmin()
{
    return 1;
}
bool Admin::puoposporre()
{
    return true;
}
