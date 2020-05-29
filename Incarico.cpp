#include "Incarico.h"
#include<math.h>

// COSTANTI PER CALCOLO PUNTEGGIO
unsigned int Incarico::_sogliaMax=10; // max punteggio attribuibile a un incarico

double Pagamento::_pesoPagamento=30; //30 euro
unsigned short int Faccenda::_pesoFaccenda=3600; // ogni 1 h (3600 sec) ci si aggiudica un punto
unsigned short int Spesa::_pesoSpesa=10; //1 punto ogni 10 articoli comprati
unsigned short int Pulizia::_pesoPulizia=3;
double Cucina::_pesoCucina=1.5;
unsigned short int Spazzatura::_pesoSpazzatura=3;

// Implementazione Incarico

void Incarico::controlloSoglia(unsigned short int & x) const{
	if (x >_sogliaMax) x = _sogliaMax;
}
void Incarico::setNome(const string& s){
	_nome=s;
}
//#include "Inquilino"
/*void Incarico::setIncaricato(Inquilino *){
	_incaricato = i;
}*/
void Incarico::setSvolto(){
	_svolto=true;
}
bool Incarico::getSvolto() const{
	return _svolto;
}

Incarico::~Incarico() {}

// Implementazione Faccenda

Faccenda::~Faccenda() {}
string Faccenda::generaNota() const {
	string s1="Il tempo per svolgere questo incarico è stimato in ";
	return s1+std::to_string(_tempoStimato); // usare metodi dataora
}
unsigned short int Faccenda::calcolaPunteggio() const{
	return _tempoStimato/_pesoFaccenda;
}

// Implementazione Pagamento

Pagamento::~Pagamento() {}
void Pagamento::setImporto(const double& x){
	_importo=x;
}
string Pagamento::generaNota() const {
	string s1="Lillone! L'importo da pagare è: ";
	string s2=" sacchi!";
	return s1+std::to_string(_importo)+s2;
}

unsigned short int Pagamento::calcolaPunteggio() const{
	unsigned short int p=_importo/_pesoPagamento;
	controlloSoglia(p);
	return p;
}

// ...

// Implementazione Bolletta
Bolletta* Bolletta::clone() const {return new Bolletta(*this);}

// Implementazione Spesa
Spesa* Spesa::clone() const {return new Spesa(*this);}

string Spesa::generaNota() const {
	if ( !getSvolto() ){
		return "La lista della spesa è... "; // chiama stampaLista Spesa 
	}
	else{
		return Pagamento::generaNota();
	}
}

//ricordarsi di aggiornare _articoli quando viene conclusa una spesa

unsigned short int Spesa::calcolaPunteggio() const{
		unsigned short int p=_articoli/_pesoSpesa; 
		controlloSoglia(p);
		return p;
}



// Implementazione Pulizia
Pulizia* Pulizia::clone() const {return new Pulizia(*this);}
string Pulizia::generaNota() const {
	string s1="Ei, Cenerentola! Devi pulire ";
	string s2=" stanze!";
	return s1+std::to_string(_stanzeDaPulire)+s2;
}
unsigned short int Pulizia::calcolaPunteggio() const{
	unsigned short int p=_stanzeDaPulire*_pesoPulizia;
	controlloSoglia(p);
	return p;
}

// Implementazione Cucina
Cucina* Cucina::clone() const {return new Cucina(*this);}
string Cucina::generaNota() const {
	string s1="Ei, Canavacciuolo! Devi preparare da mangiare per ";
	string s2=" persone!";
	return s1+std::to_string(_numeroCommensali)+s2;
}
unsigned short int Cucina::calcolaPunteggio() const{
	unsigned short int p=std::pow(_pesoCucina,_numeroCommensali);
	controlloSoglia(p);
	return p;
}

// Implementazione Spazzatura
Spazzatura* Spazzatura::clone() const {return new Spazzatura(*this);}
string Spazzatura::generaNota() const {return "Oggi bisogna buttare via ...";}
unsigned short int Spazzatura::calcolaPunteggio() const{
	unsigned short int p=_pesoSpazzatura;
	controlloSoglia(p);
	return p;
}