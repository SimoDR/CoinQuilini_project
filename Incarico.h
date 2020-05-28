// file incarico.h
// interfaccia di incarico

#ifndef INCARICO_H
#define INCARICO_H

#include<string>
using std::string;


class Incarico{
private:
	string _nome;
	//Inquilino* _incaricato; // serve #include "Inquilino.h"
	bool _svolto;
	static unsigned int _sogliaMax;
	unsigned short int& controlloSoglia(unsigned short int &) const; // bisogna gestire eccezioni che possono causare l'overflow del punteggio (es. mille commensali)

public:
	void setNome(const string&);
	//void setIncaricato(Inquilino *);
	void setSvolto();
	virtual ~Incarico()=0;
	virtual Incarico* clone() const =0;
	//virtual data posponi (data) const; // serve #include "Data.h"
	virtual string generaNota() const=0;
	// virtual import //da definire opportunamente
	//virtual calcolaPunteggio();
};

class Pagamento: virtual public Incarico{
private:
	double _importo;
	static double _pesoPagamento;
public:
	void setImporto(const double&);
	virtual ~Pagamento()=0;
	//virtual data posponi (data) const; // serve #include "Data.h"
	virtual string generaNota() const;
	// virtual import //da definire opportunamente
	//virtual double setCredito() const; //??? da definire
	//virtual calcolaPunteggio();
};

class Bolletta: public Pagamento{
private:
	//Data _dataLimite; //serve #include "Data.h"
	//vector<Inquilino> _partecipanti; //serve Inquilino.h 
public:
	virtual ~Bolletta() {} 
	virtual Bolletta* clone() const;
	//virtual data posponi (data) const; // serve #include "Data.h"
	// virtual import //da definire opportunamente
	//virtual double setCredito() const; //??? da definire
	//virtual calcolaPunteggio();
};

class Faccenda: virtual public Incarico {
private:
	int _tempoStimato; //secondi
	static unsigned short int _pesoFaccenda;
public:
	virtual ~Faccenda()=0;
	//virtual data posponi (data) const; 
	virtual string generaNota() const;
	// virtual import
	//virtual calcolaPunteggio();
};

class Spesa: public Pagamento, public Faccenda{
private:
	static unsigned short int _pesoSpesa;
public:
	virtual ~Spesa(); //???
	virtual Spesa* clone() const;
	//virtual data posponi (data) const; 
	virtual string generaNota() const;
	// virtual import
	virtual double setCredito() const; //??? da definire
	//virtual calcolaPunteggio();

};

class Pulizia: public Faccenda{
private:
	unsigned short int _stanzeDaPulire; //eccezioni: limitare numero delle camere
	static unsigned short int _pesoPulizia; 
public:
	virtual ~Pulizia() {}
	virtual Pulizia* clone() const;
	//virtual data posponi (data) const; 
	virtual string generaNota() const;
	// virtual import
	//virtual calcolaPunteggio();


};
class Cucina: public Faccenda{
private:
	unsigned short int _numeroCommensali; //eccezioni: limitare numero commensali
	static double _pesoCucina;
public:
	virtual ~Cucina() {}
	virtual Cucina* clone() const;
	//virtual data posponi (data) const; 
	virtual string generaNota() const;
	// virtual import
	//virtual calcolaPunteggio();

};

class Spazzatura: public Faccenda{
private:
	static unsigned short int _pesoSpazzatura;
public:
	virtual ~Spazzatura() {}
	virtual Spazzatura* clone() const;
	//virtual data posponi (data) const; 
	virtual string generaNota() const;
	// virtual import
	//virtual calcolaPunteggio();
};


#endif