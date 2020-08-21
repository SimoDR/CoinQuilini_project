// Listaspesa.cpp

#include "listaspesa.h"

void ListaSpesa::aggiungiListaSpesa(const string& x){
	_listaSpesa.push_back(x);
}

void ListaSpesa::rimuoviListaSpesa(const string& x){
	bool tolto=false;
	for (auto it = _listaSpesa.begin() ; it != _listaSpesa.end() && !tolto; it++){
		if(*it==x){
			_listaSpesa.erase(it);
			tolto=true;
		}
	}
}

ostream& operator<<(ostream& os, const ListaSpesa& ls){
	int i=1;
	for (vector<string>::const_iterator cit = ls._listaSpesa.begin() ; cit != ls._listaSpesa.end(); cit++){
		os<<i<<")"<<*cit<<endl;
		i++;
	}
	return os; 
}
