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
    bool _svolto;
    static unsigned short int _sogliaMax;
    static unsigned short int _sogliaMin;
protected:
    static unsigned short int controlloSoglia(int);
public:
    Incarico(const string& nome,Inquilino * incaricato=nullptr,bool svolto=false);
    Incarico();
	void setNome(const string&);
    string getNome() const {return _nome;} //debug
    void setIncaricato(Inquilino *);
    Inquilino* getIncaricato() const;
	bool getSvolto() const;
    void setSvolto();
    virtual ~Incarico() = 0;
	virtual Incarico* clone() const =0;
    virtual bool posponi (const Data & d=Data()) const;  //debug parametro d non sempre utilizzato
    virtual string generaNota() const =0;

    virtual void exportXml(QXmlStreamWriter&) const;
    virtual void importXml(QXmlStreamReader & xmlInput, vector<string>& parametri); //parametri è il vettore che si passa: vector<string> parametri(12,"\0");
    virtual unsigned short int calcolaPunteggio() const=0;
};

#endif
