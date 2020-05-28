#include "Incarico.h"

// COSTANTI PER CALCOLO PUNTEGGIO
unsigned int Incarico::_sogliaMax=10; // max punteggio attribuibile a un incarico

double Pagamento::_pesoPagamento=30; //30 euro
unsigned short int Faccenda::_pesoFaccenda=3600; // ogni 1 h (3600 sec) ci si aggiudica un punto
unsigned short int Spesa::_pesoSpesa=10; //1 punto ogni 10 articoli comprati
unsigned short int Pulizia::_pesoPulizia=3;
double Cucina::_pesoCucina=1.5;
unsigned short int Spazzatura::_pesoSpazzatura=3;

// Implementazione Incarico

unsigned short int& Incarico::controlloSoglia(unsigned short int & x) const{
	if (x >_sogliaMax) x = _sogliaMax;
	return x;
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
	string s1="Lillone! Devi sborsare ";
	string s2=" sacchi!";
	return s1+std::to_string(_importo)+s2;
}

unsigned short int Pagamento::calcolaPunteggio() const{
	return _importo/_pesoPagamento;
}

// ...

// Implementazione Bolletta
Bolletta* Bolletta::clone() const {return new Bolletta(*this);}

// Implementazione Spesa
Spesa* Spesa::clone() const {return new Spesa(*this);}
unsigned short int Spesa::calcolaPunteggio() const{
	return 60/_pesoSpesa; //al posto del numero bisogna mettere gli elementi rimossi dalla lista_spesa perché acquistati
}

string Spesa::generaNota() const {
	return "La lista della spesa è... "; // da definire
}

// Implementazione Pulizia
Pulizia* Pulizia::clone() const {return new Pulizia(*this);}
string Pulizia::generaNota() const {
	string s1="Ei, Cenerentola! Devi pulire ";
	string s2=" stanze!";
	return s1+std::to_string(_stanzeDaPulire)+s2;
}

// Implementazione Cucina
Cucina* Cucina::clone() const {return new Cucina(*this);}
string Cucina::generaNota() const {
	string s1="Ei, Canavacciuolo! Devi preparare da mangiare per ";
	string s2=" persone!";
	return s1+std::to_string(_numeroCommensali)+s2;
}

// Implementazione Spazzatura
Spazzatura* Spazzatura::clone() const {return new Spazzatura(*this);}
string Spazzatura::generaNota() const {return "Oggi bisogna buttare via ...";}