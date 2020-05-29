#include "ListaSpesa.h"
#include<iostream>

using std::cout;
using std::endl;


int main(){
	ListaSpesa lista;
	lista.aggiungiListaSpesa("fichi secchi");
	lista.aggiungiListaSpesa("asparagi");
	lista.aggiungiListaSpesa("banane");
	cout<<lista<<"****"<<endl;
	lista.rimuoviListaSpesa("mela");
	lista.rimuoviListaSpesa("banane");
	cout<<lista;
}