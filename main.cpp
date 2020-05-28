#include <iostream>
#include<vector>
#include "calendario.h"
using std::cout;
using std::endl;

int main()
{
    Data prova_addizione(29,2,2020);
    cout<<"Prova addizione: "<<prova_addizione<<" + "<<" 257 giorni = "<<prova_addizione+257<<endl;
    cout<<endl;

    Data prova_aggiungi_mesi(31,01,2020);
    cout<<"Prova aggiungi mesi: "<<prova_aggiungi_mesi<<" + "<<" 1 mese = "<<prova_aggiungi_mesi.aggiungiMesi(1)<<endl;
    cout<<endl;

    cout<<"Prova eccezione: creazione giorno 29/2/2021: "<<endl;
    Data prova_eccezione(29,2,2021);
    cout<<endl;

    cout<<"Prova creazione giorno 28/2/2021 da stringa: "<<endl;
    Data prova_da_stringa("28/2/2021");
    cout<<prova_da_stringa<<endl;

    cout<<"Prova confronti: "<<endl;
    Data minore("21/04/2109");
    Data maggiore("21/05/2109");
    cout<<(minore<maggiore)<<endl;
    cout<<(minore>maggiore)<<endl;
    cout<<(minore==maggiore)<<endl;

}
