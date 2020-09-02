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
    static unsigned short int controlloSoglia(int); // verifica: 2 <= punteggio incarico <= 10

public:
<<<<<<< HEAD
    Incarico(const string& nome="\0",Inquilino * incaricato=nullptr,bool svolto=false);
    virtual ~Incarico() = 0;
    virtual Incarico* clone() const =0;
=======
    Incarico(const string& nome,Inquilino * incaricato,bool svolto);
	void setNome(const string&);
>>>>>>> parent of 08e7a01... refactor sui costruttori della gerarchia di incarichi

    // set
    void setIncaricato(Inquilino *);
    void setSvolto();
    virtual void setDataLimite(const Data&);

    // get
    Inquilino* getIncaricato() const;
	bool getSvolto() const;
    virtual string getLabel() const =0;
    virtual string generaNota() const;

    virtual bool posponi (const Data &) const;
    virtual unsigned short int calcolaPunteggio() const=0;

    // input/output
    static void importXml(QXmlStreamReader & xmlInput, vector<string>& parametri);    //parametri è il vettore che si passa: vector<string> parametri(12,"\0");
    virtual void exportXml(QXmlStreamWriter&, string) const;
};

#endif
