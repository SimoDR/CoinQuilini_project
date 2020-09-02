#ifndef ADMIN
#define ADMIN
#include "inquilino.h"

class Admin : public Inquilino 
{
    friend class ListaInquilini;
    public:
        Admin(const string&, const string&, float=0, unsigned short=0);

        //get
        virtual std::string getLabel() const;

        virtual unsigned short int isAdmin() const;

        virtual void exportXml(QXmlStreamWriter&) const;
};

#endif
