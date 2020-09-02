#ifndef INQUILINO
#define INQUILINO

#include <iostream>
#include <string>
#include <QXmlStreamWriter>
#include <iomanip>
#include <sstream>

using std::string;

class Inquilino
{
friend class ListaInquilini;
private:
    string _user;
    string _password;
    float _creditoDebito;
    unsigned short int _punteggio;
    static unsigned short int _puntiMin;
    static unsigned short int _puntiMax;
    static unsigned short int _sogliaPosponi;

public:
    Inquilino(const string&, const string&, float credeb=0, unsigned short int punteggio=0);        //utente da nome e pw
    virtual ~Inquilino() {}

    //set
    void modifica(const string&, const string&); //modifica username e/o password
    void setCD(float);            //modifica il credito/debito aggiungendo (o togliendo se negativo)
    void setPunteggio(short int);  //modifica il punteggio aggiungendo (o togliendo se negativo)

    //get
    float getCreditoDebito() const;
    unsigned short int getPunteggio() const;
    string getNome() const;
    string showPunteggio() const;
    string showCreDeb() const;
    virtual std::string getLabel() const;

    virtual unsigned short int isAdmin() const;   //ritorna un intero che indica la categoria dell'utente (0 per Inquilino)
    bool puoPosporre() const; //bool indica se l'inquilino può o no posporre
    bool isLogged(const string &, const string &) const;

    //OUTPUT
    void exportXml(QXmlStreamWriter&) const;
};

#endif
