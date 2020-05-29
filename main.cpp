#include <iostream>
#include "dList.h"

using namespace std;

int main()
{
    //prova 1: popfront e back, insert, remove anche con liste vuote e con un nodo
    dList<int> lista;
    dList<int>::iterator i1 = lista.begin();
    auto j1=lista.insert(i1, 3);
    cout << *(j1) << endl;
    dList<int>::iterator l = lista.end();
    auto m=lista.insert(l, 6);
    cout << lista;
    lista.remove(lista.begin());
    lista.popBack();
    cout << lista;

//prova 2
    dList<int> list(5,7);
    cout << list;
    auto i=--list.end();
    auto j = list.insert(i, 9);
    cout << "valore appena inserito:" << *j << endl;
    cout << list;
    auto k = list.remove(j);
    cout << "valore successivo a quello appena rimosso:" << *k << endl;
    cout << list;

//test bySimo
    dList<char> simo(5,'s');
    for(dList<char>::iterator it = simo.begin(); it!= simo.end(); ++it)
        cout<<*it<<" ";
    cout<<endl;
    dList<char>::iterator ultimo=simo.end();
    dList<char>::iterator ritornato=simo.insert(ultimo,'z');
    for(dList<char>::iterator it = simo.begin(); it!= simo.end(); ++it)
        cout<<*it<<" ";
    cout<<endl;
    cout<<*ritornato<<endl;
    cout<<endl;
//
    simo.insert(simo.begin(),'a');
    simo.insert(simo.begin(),'b');

    for(dList<char>::iterator it = simo.begin(); it!= simo.end(); ++it)
        cout<<*it<<" ";
    cout<<endl;
    dList<char>::iterator r=simo.remove(simo.begin());
    cout<<simo;
    for(dList<char>::iterator it = simo.begin(); it!= simo.end(); ++it)
        cout<<*it<<" ";
    cout<<endl;
    cout<<*r<<endl;
    ++++++++++++r;
    cout<<*simo.remove(r)<<endl;
    for(dList<char>::iterator it = simo.begin(); it!= simo.end(); ++it)
        cout<<*it<<" ";
    cout<<endl;


    

}
