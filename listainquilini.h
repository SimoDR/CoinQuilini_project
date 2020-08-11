#ifndef LISTAINQUILINI_H
#define LISTAINQUILINI_H

#include "inquilino.h"
#include "admin.h"
#include "dList.h"
#include "vector"
#include <stdexcept>
using std::vector;

class ListaInquilini
{
private:
    dList<Inquilino*> _listaInquilini;
    void aggiungi(Inquilino *);
    bool checkPresenza(const string &) const; //controlla se esiste già un inquilino con l'user selezionato per l'inserimento
public:
    ListaInquilini();
    void rimuovi(unsigned int);
    Inquilino *getInquilino(unsigned int) const;
    Inquilino *getInquilino(const string &) const;
    bool checkCredenziali(const string&,const string &) const;
    void creaInserisci(const string &, const string &);   //crea l'inquilino e lo inserisce nel calendario
    vector<string>inquilini() const;
    vector<std::string> getCredenziali(unsigned int) const;
    void modifica(const string &, const string &, unsigned int);
    void checkAdmin(unsigned int);
    unsigned short int isAdmin(const string &) const;
};

#endif // LISTAINQUILINI_H
