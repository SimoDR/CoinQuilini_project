// file incarico.h
// interfaccia di incarico

#ifndef INCARICO_H
#define INCARICO_H

#include<string>
#include "inquilino.h"
#include "data.h"
#include <QXmlStreamWriter>
#include <QFile>
#include "utilities.h"
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
    Incarico(string nome,Inquilino * incaricato=nullptr,bool svolto=false); //da sistemare
	void setNome(const string&);
    string getNome() const {return _nome;} //debug
    void setIncaricato(Inquilino *);
    Inquilino* getIncaricato() const;
	bool getSvolto() const;
    void setSvolto();
    virtual ~Incarico() = 0;
	virtual Incarico* clone() const =0;
    virtual bool posponi (const Data d=Data()) const;
    virtual string generaNota() const =0;

    virtual void exportXml(QXmlStreamWriter&) const;
    virtual void importXml(QXmlStreamReader & xmlInput, vector<string>& parametri); //parametri è il vettore che si passa: vector<string> parametri(12,"\0");
	// virtual import //da definire opportunamente
    virtual unsigned short int calcolaPunteggio() const=0;
};

#endif
