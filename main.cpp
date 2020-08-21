//#include <iostream>
//#include<vector>
//#include <QApplication>
//#include "calendario.h"
//#include "login.h"

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    Controller controller;
//    Login l(nullptr, &controller);
//    l.show();
//    return a.exec();

//}


//il main della gerarchia
//********************************

#include "incarico.h"
#include "spazzatura.h"
#include "cucina.h"
#include "bolletta.h"
#include "faccenda.h"
#include "pagamento.h"
#include "pulizia.h"
#include "spesa.h"
#include "listaspesa.h"


#include<iostream>
using namespace std;

int main(){
    Faccenda * spazz=new Spazzatura("secco",20);
    cout<< spazz->generaNota() <<endl;
    cout<<spazz->Faccenda::generaNota()<<endl;
    cout<<"Questo incarico vale: "<<spazz->calcolaPunteggio()<<" punti!"<<endl;
    cout<<"***"<<endl;

    Incarico * cuc=new Cucina("pranzo",60,4);
    cout<< cuc->generaNota() <<endl;
    cout<<"Questo incarico vale: "<<cuc->calcolaPunteggio()<<" punti!"<<endl;
    cout<<"L'incaricato è: "<<cuc->getIncaricato()<<" (punt... se 0 = non assegnato)!"<<endl;
    cout<<"***"<<endl;

    Pagamento * boll=new Bolletta("luce-gas",250,Data(1,1,2021));
    boll->setImporto(50.6);
    cout<< boll->generaNota() <<endl;
    cout<<"Questo incarico vale: "<<boll->calcolaPunteggio()<<" punti!"<<endl;
    cout<<"***"<<endl;

    Pagamento * spesa=new Spesa("panificio",10,30,10);
    cout<<spesa->generaNota()<<endl;
    spesa->setSvolto();
    cout<<spesa->generaNota()<<endl;
    cout<<"Questo incarico vale: "<<spesa->calcolaPunteggio()<<" punti!"<<endl;
    cout<<"***"<<endl;

    ListaSpesa lista;
    lista.aggiungiListaSpesa("fichi secchi");
    lista.aggiungiListaSpesa("asparagi");
    lista.aggiungiListaSpesa("banane");
    cout<<lista<<"****"<<endl;
    lista.rimuoviListaSpesa("mela");
    lista.rimuoviListaSpesa("banane");
    cout<<lista<<endl;

}
