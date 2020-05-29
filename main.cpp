#include <iostream>
#include "dList.h"

using namespace std;

int main()
{
    //prova 1: popfront e back, insert, remove anche con liste vuote e con un nodo
    dList<int> lista;
    dList<int>::iterator i = lista.begin();
    auto j=lista.insert(i, 3);
    cout << *(j) << endl;
    dList<int>::iterator l = lista.end();
    auto m=lista.insert(l, 6);
    cout << lista;
    lista.remove(lista.begin());
    lista.popBack();
    cout << lista;

//prova 2
    dList<int> list(5,7);
    cout << list;
    for(dList<int>::iterator i = list.begin(); i != list.end(); ++i)
    if (i==--list.end())
        auto j = list.insert(i, 9);
    cout << "valore appena inserito:" << *j << endl;
    cout << list;
    auto k = list.remove(j);
    cout << "valore successivo a quello appena rimosso:" << *k << endl;
    cout << list;

    

}
