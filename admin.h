#ifndef ADMIN
#define ADMIN
#include "inquilino.h"

class Admin : public Inquilino 
{
    friend class ListaInquilini;
    public:
        Admin(string, string);
        virtual unsigned short int isAdmin() const;
        virtual bool puoposporre();
        virtual std::string getLabel() const;
};

#endif
