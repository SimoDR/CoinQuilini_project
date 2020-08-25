// file ListaSpesa.h
// interfaccia di ListaSpesa

#ifndef LISTASPESA_H
#define LISTASPESA_H

#include<iostream>
#include<string>
#include<vector>
using std::string;
using std::vector;

class ListaSpesa{
    friend class Spesa;
private:
	vector<string> _listaSpesa;
    ListaSpesa();
};

#endif
