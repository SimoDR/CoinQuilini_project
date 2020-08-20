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
    Incarico(string nome,Inquilino * incaricato=nullptr,bool svolto=false); //da sistemare
	void setNome(const string&);
    void setIncaricato(const Inquilino *);
	bool getSvolto() const;
    void setSvolto();
    virtual ~Incarico() {}
	virtual Incarico* clone() const =0;
    virtual bool posponi (const Data&) const; // ritorna false di default
    virtual string generaNota() const;
	// virtual import //da definire opportunamente
	virtual unsigned short int calcolaPunteggio() const=0;
};



class Pagamento: virtual public Incarico
{
private:
	double _importo;
	static double _pesoPagamento;

public:
    Pagamento(string nome,double importo,Inquilino * incaricato=nullptr,bool svolto=false);
	void setImporto(const double&);
	virtual ~Pagamento()=0;
	virtual string generaNota() const;
	// virtual import //da definire opportunamente
	//virtual double setCredito() const; //??? da definire
	virtual unsigned short int calcolaPunteggio() const;
};



class Bolletta: public Pagamento{
private:
    Data _dataLimite;
    vector<const Inquilino *> _partecipanti;
public:
    Bolletta(string nome,double importo,const Data& dataLimite,const vector<const Inquilino *>& partecipanti,Inquilino * incaricato=nullptr,bool svolto=false);
	virtual ~Bolletta() {} 
	virtual Bolletta* clone() const;
    virtual bool posponi (const Data&) const;
	// virtual import //da definire opportunamente
	//virtual double setCredito(Pagamento,vector<Inquilino> Inquilini) const; //???
};



class Faccenda: virtual public Incarico {
private:
	int _tempoStimato; //secondi
	static unsigned short int _pesoFaccenda;
public:
    Faccenda(string nome,int tempoStimato,Inquilino * incaricato=nullptr,bool svolto=false);
	virtual ~Faccenda()=0;
	virtual string generaNota() const;
	// virtual import
	virtual unsigned short int calcolaPunteggio() const;
};



class Spesa: public Pagamento, public Faccenda
{
private:
    static unsigned short int _pesoSpesa;
    unsigned short int _numeroArticoli;
public:
    Spesa(string nome,double importo,int tempoStimato,unsigned short int numeroArticoli,Inquilino * incaricato=nullptr,bool svolto=false);
	virtual ~Spesa() {}; //???
	virtual Spesa* clone() const;
    virtual bool posponi (const Data&) const;
	virtual string generaNota() const;
	// virtual import
	//virtual double setCredito() const; //??? da definire
	virtual unsigned short int calcolaPunteggio() const;

};



class Pulizia: public Faccenda
{
private:
	unsigned short int _stanzeDaPulire; //eccezioni: limitare numero delle camere
	static unsigned short int _pesoPulizia; 
public:
    Pulizia(string nome,int tempoStimato,unsigned short int stanzeDaPulire,Inquilino * incaricato=nullptr,bool svolto=false);
	virtual ~Pulizia() {}
	virtual Pulizia* clone() const;
	//virtual bool posponi (const Data&) const; 
	virtual string generaNota() const;
	// virtual import
	virtual unsigned short int calcolaPunteggio() const;
};



class Cucina: public Faccenda
{
private:
	unsigned short int _numeroCommensali; //eccezioni: limitare numero commensali
	static double _pesoCucina;
public:
    Cucina(string nome,int tempoStimato,unsigned short int numeroCommensali,Inquilino * incaricato=nullptr,bool svolto=false);
	virtual ~Cucina() {}
	virtual Cucina* clone() const;
	virtual string generaNota() const;
	// virtual import
	virtual unsigned short int calcolaPunteggio() const;

};



class Spazzatura: public Faccenda
{
private:
	static unsigned short int _pesoSpazzatura;
public:
    Spazzatura(string nome,int tempoStimato,Inquilino * incaricato=nullptr,bool svolto=false);
	virtual ~Spazzatura() {}
	virtual Spazzatura* clone() const;
	virtual string generaNota() const;
	// virtual import
	virtual unsigned short int calcolaPunteggio() const;
};


#endif
