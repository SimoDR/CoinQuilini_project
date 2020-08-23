//#include <iostream>
//#include<vector>
#include <QApplication>
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


/*
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller controller;
    Login l(nullptr, &controller);
    l.show();
    return a.exec();

}*/

#include "incarico.h"
//#include "spazzatura.h"
//#include "cucina.h"
//#include "bolletta.h"
//#include "faccenda.h"
//#include "pagamento.h"
//#include "pulizia.h"
//#include "spesa.h"
#include "controller.h"
#include "creamodificainquilino.h"
#include "data.h"
#include "dList.h"
#include "mainwindow.h"
//#include "faccenda.h"
#include "incarico.h"
#include "inquilino.h"
#include "listainquilini.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Controller controller;

    //Incarico * a=new Pulizia("puliziaDelSabato",20,3);
    //Incarico * b=new Spazzatura("umidoDelGiovedi",2);

//    string nomeIncarico=parametri[0];
//    string tipoIncarico=parametri[1];
//    string nomeIncaricato=parametri[2]; //DA SISTEMARE
//    int cadenzaIncarico=std::stoi(parametri[3]);
//    int tempoStimato=std::stoi(parametri[4]);
//    unsigned short int stanzeDaPulire=std::stoi(parametri[5]);
//    unsigned short int numeroCommensali=std::stoi(parametri[6]);
//    unsigned short int numeroArticoli=std::stoi(parametri[7]);
//    int importo=std::stoi(parametri[8]);
//    Data dataLimite(parametri[9]);
//    Data dataInizio(parametri[10]);
//    int numeroOccorrenze=std::stoi(parametri[11]);

    vector<string> parametri;
    parametri.push_back("puliziaDelSabato"); //0
    parametri.push_back("Pulizia"); //1
    parametri.push_back("\0"); //2
    parametri.push_back("6"); //3
    parametri.push_back("20"); //4
    parametri.push_back("3"); //5
    parametri.push_back("\0"); //6
    parametri.push_back("\0"); //7
    parametri.push_back("\0"); //8
    parametri.push_back("\0"); //9
    parametri.push_back("22/08/2020"); //10
    parametri.push_back("4"); //11

    controller.rimuoviInquilino(2);
    controller.rimuoviInquilino(1);
controller.rimuoviInquilino(3);
controller.rimuoviInquilino(4);
controller.rimuoviInquilino(5);
controller.rimuoviInquilino(6);

    controller.aggiungiInquilino("Simone","gay99");
    controller.aggiungiInquilino("Antonio","pisellolungo");

//    cout<<"++++++++"<<endl;
//    vector<Inquilino*> inq=controller._listaInquilini.getInquilini();
//    for(vector<Inquilino*>::iterator it=inq.begin(); it!=inq.end(); ++it)
//        cout<<(*it)->getNome()<<" ";
//    cout<<"++++++++"<<endl;

    //cout<<controller._calendario.getDataDiOggi();
    //controller.stampaBuffer();

    controller.creaNuovoIncarico(parametri);

    //controller.stampaCalendario();


    vector<string> parametri1;
    parametri1.push_back("Plastica"); //0
    parametri1.push_back("Spazzatura"); //1
    parametri1.push_back("\0"); //2
    parametri1.push_back("3"); //3
    parametri1.push_back("5"); //4
    parametri1.push_back("\0"); //5
    parametri1.push_back("\0"); //6
    parametri1.push_back("\0"); //7
    parametri1.push_back("\0"); //8
    parametri1.push_back("\0"); //9
    parametri1.push_back("22/08/2020"); //10
    parametri1.push_back("2"); //11

    controller.creaNuovoIncarico(parametri1);




    vector<string> parametri2;
    parametri2.push_back("PastaAlTonno"); //0
    parametri2.push_back("Cucina"); //1
    parametri2.push_back("\0"); //2
    parametri2.push_back("12"); //3
    parametri2.push_back("10"); //4
    parametri2.push_back("\0"); //5
    parametri2.push_back("10"); //6
    parametri2.push_back("\0"); //7
    parametri2.push_back("\0"); //8
    parametri2.push_back("\0"); //9
    parametri2.push_back("22/08/2020"); //10
    parametri2.push_back("3"); //11

    controller.creaNuovoIncarico(parametri2);

    vector<string> parametri3;
    parametri3.push_back("PastaAllaMerda"); //0
    parametri3.push_back("Cucina"); //1
    parametri3.push_back("\0"); //2
    parametri3.push_back("1"); //3
    parametri3.push_back("10"); //4
    parametri3.push_back("\0"); //5
    parametri3.push_back("10"); //6
    parametri3.push_back("\0"); //7
    parametri3.push_back("\0"); //8
    parametri3.push_back("\0"); //9
    parametri3.push_back("25/08/2020"); //10
    parametri3.push_back("6"); //11

    controller.creaNuovoIncarico(parametri3);

    controller.stampaCalendario();

    controller.rimuoviInquilino(2);
    controller.rimuoviInquilino(1);
controller.rimuoviInquilino(3);
controller.rimuoviInquilino(4);
controller.rimuoviInquilino(5);
controller.rimuoviInquilino(6);


}

//il main della lista_spesa
//********************************


//#include "listaspesa.h"
//#include<iostream>

//using std::cout;
//using std::endl;


//int main(){
//	ListaSpesa lista;
//	lista.aggiungiListaSpesa("fichi secchi");
//	lista.aggiungiListaSpesa("asparagi");
//	lista.aggiungiListaSpesa("banane");
//	cout<<lista<<"****"<<endl;
//	lista.rimuoviListaSpesa("mela");
//	lista.rimuoviListaSpesa("banane");
//	cout<<lista;
//}




//il main della gerarchia
//********************************
// 
// #include "incarico.h"
// #include "spazzatura.h"
// #include "cucina.h"
// #include "bolletta.h"
// #include "faccenda.h"
// #include "pagamento.h"
// #include "pulizia.h"
// #include "spesa.h"
// #include "listaspesa.h"


// #include<iostream>
// using namespace std;

// int main(){
//     Faccenda * spazz=new Spazzatura("secco",20);
//     cout<< spazz->generaNota() <<endl;
//     cout<<spazz->Faccenda::generaNota()<<endl;
//     cout<<"Questo incarico vale: "<<spazz->calcolaPunteggio()<<" punti!"<<endl;
//     cout<<"***"<<endl;

//     Incarico * cuc=new Cucina("pranzo",60,4);
//     cout<< cuc->generaNota() <<endl;
//     cout<<"Questo incarico vale: "<<cuc->calcolaPunteggio()<<" punti!"<<endl;
//     cout<<"L'incaricato è: "<<cuc->getIncaricato()<<" (punt... se 0 = non assegnato)!"<<endl;
//     cout<<"***"<<endl;

//     Pagamento * boll=new Bolletta("luce-gas",250,Data(1,1,2021));
//     boll->setImporto(50.6);
//     cout<< boll->generaNota() <<endl;
//     cout<<"Questo incarico vale: "<<boll->calcolaPunteggio()<<" punti!"<<endl;
//     cout<<"***"<<endl;

//     Pagamento * spesa=new Spesa("panificio",10,30,10);
//     cout<<spesa->generaNota()<<endl;
//     spesa->setSvolto();
//     cout<<spesa->generaNota()<<endl;
//     cout<<"Questo incarico vale: "<<spesa->calcolaPunteggio()<<" punti!"<<endl;
//     cout<<"***"<<endl;

//     ListaSpesa lista;
//     lista.aggiungiListaSpesa("fichi secchi");
//     lista.aggiungiListaSpesa("asparagi");
//     lista.aggiungiListaSpesa("banane");
//     cout<<lista<<"****"<<endl;
//     lista.rimuoviListaSpesa("mela");
//     lista.rimuoviListaSpesa("banane");
//     cout<<lista<<endl;

// }
