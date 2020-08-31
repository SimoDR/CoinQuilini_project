#ifndef ADMIN
#define ADMIN
#include "inquilino.h"

class Admin : public Inquilino 
{
    friend class ListaInquilini;
    public:
        Admin(const string&, const string&, float=0, unsigned short=0);
        virtual unsigned short int isAdmin() const;
        virtual bool puoposporre() const;
        virtual std::string getLabel() const;
};

#endif
