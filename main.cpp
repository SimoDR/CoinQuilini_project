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
    lista.remove(lista.begin());
    lista.popBack();
     
       for (dList<int>::const_iterator c = lista.cbegin(); c != lista.cend(); ++c)
        std::cout << *c << ' ';
    std::cout << std::endl; 

//prova 2

    dList<int> list(5,7);

    for (dList<int>::const_iterator c = list.cbegin(); c != list.cend(); ++c)
        std::cout << *c << ' ';
    std::cout << std::endl;     
   
    for(dList<int>::iterator i = list.begin(); i != list.end(); ++i)
    if (i==--list.end())
        auto j = list.insert(i, 9);
    cout << "valore appena inserito:" << *j << endl; 

    for (dList<int>::const_iterator c = list.cbegin(); c != list.cend(); ++c)
        std::cout << *c << ' ';
    std::cout << std::endl;

    auto k = list.remove(j);
    cout << "valore successivo a quello appena rimosso:" << *k << endl;

    for (dList<int>::const_iterator c = list.cbegin(); c != list.cend(); ++c)
        std::cout << *c << ' ';
    std::cout << std::endl;

    

}