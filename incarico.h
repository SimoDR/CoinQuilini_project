// file incarico.h
// interfaccia di incarico

#ifndef INCARICO_H
#define INCARICO_H

#include<string>
#include "inquilino.h"
#include "data.h"
using std::string;

class Incarico
{
private:
	string _nome;
    Inquilino* _incaricato;
    bool _svolto=false;
	static unsigned int _sogliaMax;

protected:
	void controlloSoglia(unsigned short int &) const; // bisogna gestire eccezioni che possono causare l'overflow del punteggio (es. mille commensali)

public:
	//Incarico(string nome,Inquilino * incaricato=nullptr,bool svolto=false): _nome(nome),_incaricato(incaricato),_svolto(svolto) {} //da sistemare
	void setNome(const string&);
    void setIncaricato(Inquilino *);
	bool getSvolto() const;
    void setSvolto();
    virtual ~Incarico() = 0;
	virtual Incarico* clone() const =0;
    virtual bool posponi (const Data d=Data()) const;
    virtual string generaNota() const =0;
	// virtual import //da definire opportunamente
	virtual unsigned short int calcolaPunteggio() const=0;
};

#endif
