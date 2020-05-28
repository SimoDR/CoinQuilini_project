#include <iostream>
#include "dList.h"

using namespace std;

int main()
{
    dList<int> lista;
    dList<int>::iterator i = lista.begin();
    auto j=lista.insert(i, 3);
    cout << *(j) << endl;
    dList<int>::iterator l = lista.end();
    auto m=lista.insert(l, 6);
    for (dList<int>::const_iterator c = lista.cbegin(); c != lista.cend(); ++c)
        std::cout << *c << ' ';
    std::cout << std::endl;


    lista.insert(l, 7);
    for (dList<int>::const_iterator c = lista.cbegin(); c != lista.cend(); ++c)
        std::cout << *c << ' ';
    std::cout << std::endl;
    //non dovrebbe venire 3 7 6?

}
