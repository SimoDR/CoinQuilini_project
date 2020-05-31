#ifndef INQUILINO
#define INQUILINO

#include <iostream>
#include <string>
using std::string;

class Inquilino
{
private:
    string _user;
    string _password;
    double _creditoDebito;
    short int _punteggio;
    static unsigned short int _puntiMin;
    static unsigned short int _puntiMax;
    static unsigned short int _sogliaPosponi;
    static short int _puntiMin;
    static short int _puntiMax;
    static short int _sogliaPosponi;

public:
    Inquilino(const string&, const string&);        //utente da nome e pw
    void modifica(const string&, const string&); //modifica username e/o password
    void setCD(const double&);            //modifica il credito/debito aggiungendo (o togliendo se negativo)
    void setPunteggio(const unsigned short int&);  //modifica il punteggio aggiungendo (o togliendo se negativo)
    virtual unsigned short int isAdmin() const;   //ritorna un intero che indica la categoria dell'utente (0 per Inquilino)
    bool puoPosporre() const; //bool indica se l'inquilino può o no posporre
    double getCreditoDebito() const;
    unsigned short int getPunteggio() const;

    void modifica(string, string); //modifica username e/o password
    void setCD(double);            //modifica il credito/debito aggiungendo (o togliendo se negativo)
    void setPunteggio(short int);  //modifica il punteggio aggiungendo (o togliendo se negativo)
    virtual unsigned short isAdmin();   //ritorna un intero che indica la categoria dell'utente (0 per Inquilino)
    virtual bool puoPosporre(); //bool indica se l'inquilino può o no posporre
    string getNome() const;
    bool isLogged(string &, string &) const;
};

#endif#endif
