#ifndef ADMIN
#define ADMIN
#include "inquilino.h"

class Admin : public Inquilino 
{
    public:
        Admin(const string&, const string&);
        virtual unsigned short int isAdmin() const;
};

#endif