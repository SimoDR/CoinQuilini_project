// file ListaSpesa.h
// interfaccia di ListaSpesa

#ifndef LISTASPESA_H
#define LISTASPESA_H

#include<iostream>
#include<string>
#include<vector>
using std::string;
using std::vector;
using std::ostream;
using std::endl;

class ListaSpesa;
ostream& operator<<(ostream&, const ListaSpesa&);

class ListaSpesa{
	//friend class Spesa;
	friend ostream& operator<<(ostream&, const ListaSpesa&);
private:
	vector<string> _listaSpesa;
	//ListaSpesa(); // Quando viene attivato (L'incarico) Spesa viene 
					// creata un'unica ListaSpesa
	//~ListaSpesa();
public:
	void aggiungiListaSpesa(const string&);
	void rimuoviListaSpesa(const string&);
	//export/import;
};

#endif