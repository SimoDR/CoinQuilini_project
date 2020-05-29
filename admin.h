#ifndef ADMIN
#define ADMIN
#include "inquilino.h"

class Admin : public Inquilino 
{
    public:
        Admin(string, string);
        virtual unsigned short isAdmin();
        virtual bool puoposporre();
};

#endif