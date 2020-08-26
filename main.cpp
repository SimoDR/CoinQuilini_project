/*
#include <iostream>
#include<vector>
#include <QApplication>
#include "calendario.h"
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller controller;
    Login l(nullptr, &controller);
    l.show();
    return a.exec();
}
*/





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
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Controller controller;


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
    parametri.push_back("\0"); //12
    parametri.push_back("\0"); //13





    controller.aggiungiInquilino("Simone","gay99");

    controller.aggiungiInquilino("Antonio","pisellolungo");
    controller.aggiungiInquilino("Francesco","Il montanaro");


    controller.creaNuovoIncarico(parametri);


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
    parametri1.push_back("\0"); //12
    parametri1.push_back("\0"); //13


    controller.creaNuovoIncarico(parametri1);




    vector<string> parametri2;
    parametri2.push_back("PuliziaCessi"); //0
    parametri2.push_back("Pulizia"); //1
    parametri2.push_back("\0"); //2
    parametri2.push_back("12"); //3
    parametri2.push_back("10"); //4
    parametri2.push_back("2"); //5
    parametri2.push_back("\0"); //6
    parametri2.push_back("\0"); //7
    parametri2.push_back("\0"); //8
    parametri2.push_back("\0"); //9
    parametri2.push_back("22/08/2020"); //10
    parametri2.push_back("3"); //11
    parametri2.push_back("\0"); //12
    parametri2.push_back("\0"); //13


    controller.creaNuovoIncarico(parametri2);

    vector<string> parametri3;
    parametri3.push_back("Burger King"); //0
    parametri3.push_back("Cucina"); //1
    parametri3.push_back("\0"); //2
    parametri3.push_back("2"); //3
    parametri3.push_back("10"); //4
    parametri3.push_back("\0"); //5
    parametri3.push_back("10"); //6
    parametri3.push_back("\0"); //7
    parametri3.push_back("\0"); //8
    parametri3.push_back("\0"); //9
    parametri3.push_back("22/08/2020"); //10
    parametri3.push_back("6"); //11
    parametri3.push_back("\0"); //12
    parametri3.push_back("\0"); //13


    controller.creaNuovoIncarico(parametri3);

    vector<string> parametri4;
    parametri4.push_back("PastaAllaMerda"); //0
    parametri4.push_back("Cucina"); //1
    parametri4.push_back("\0"); //2
    parametri4.push_back("1"); //3
    parametri4.push_back("10"); //4
    parametri4.push_back("\0"); //5
    parametri4.push_back("10"); //6
    parametri4.push_back("\0"); //7
    parametri4.push_back("\0"); //8
    parametri4.push_back("\0"); //9
    parametri4.push_back("25/08/2020"); //10
    parametri4.push_back("6"); //11
    parametri4.push_back("\0"); //12
    parametri4.push_back("\0"); //13


    controller.creaNuovoIncarico(parametri4);

    vector<string> parametri5;
    parametri5.push_back("McDonald"); //0
    parametri5.push_back("Cucina"); //1
    parametri5.push_back("\0"); //2
    parametri5.push_back("1"); //3
    parametri5.push_back("10"); //4
    parametri5.push_back("\0"); //5
    parametri5.push_back("10"); //6
    parametri5.push_back("\0"); //7
    parametri5.push_back("\0"); //8
    parametri5.push_back("\0"); //9
    parametri5.push_back("22/08/2020"); //10
    parametri5.push_back("6"); //11
    parametri5.push_back("\0"); //12
    parametri5.push_back("\0"); //13


    controller.creaNuovoIncarico(parametri5);

    controller.stampaCalendario();



    cout<<"Rimuovi incarico"<<endl;
    controller.rimuoviIncarico(Data("22/08/2020"),1);
    controller.stampaCalendario();

    cout<<"Rimuovi incarico"<<endl;
    controller.rimuoviIncarico(Data("9/09/2020"),0);
    controller.stampaCalendario();

//    cout<<"Posponi incarico"<<endl;
//    controller.posponiIncarico(Data("22/08/2020"),0,3);
//    controller.stampaCalendario();


//    cout<<"Posponi incarico"<<endl;
//    controller.posponiIncarico(Data("15/09/2020"),0,3);
//    controller.stampaCalendario();



    cout<<controller.getInquilinoPos(1)[0]<<" inquilino da rimuovere"<<endl;

    controller.stampaCalendario();

    controller.rimuoviInquilino(1);
    controller.stampaCalendario();

    controller.rimuoviInquilino(1);
    controller.stampaCalendario();


    controller.rimuoviInquilino(1);
    controller.stampaCalendario();


}







/*


//il main della gerarchia
// ********************************


// il main della gerarchia

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
     Faccenda * spazz=new Spazzatura("ritiro rifiuti", "secco",20);
     cout << spazz->getNome() <<endl;
     cout << spazz->getIncaricato() <<endl;
     cout<< spazz->generaNota() <<endl;
     cout<<spazz->Faccenda::generaNota()<<endl;
     cout<<"Questo incarico vale: "<<spazz->calcolaPunteggio()<<" punti!"<<endl;
     cout<<"***"<<endl;

     Incarico * cuc=new Cucina("pranzo",60,4);
     cout << cuc->getNome() <<endl;
     cout<< cuc->generaNota() <<endl;
     cout<<"Questo incarico vale: "<<cuc->calcolaPunteggio()<<" punti!"<<endl;
     cout<<"L'incaricato è: "<<cuc->getIncaricato()<<" (punt... se 0 = non assegnato)!"<<endl;
     cout<<"***"<<endl;

     Pagamento * boll=new Bolletta("luce-gas",250,Data(1,1,2021));
     cout << boll->getNome() <<endl;
     boll->setImporto(50.6);
     cout<< boll->generaNota() <<endl;
     cout<<"Questo incarico vale: "<<boll->calcolaPunteggio()<<" punti!"<<endl;
     cout<<"***"<<endl;

     Spesa * spesa=new Spesa("panificio",10,30,10);
     spesa->aggiungiListaSpesa("banane");
     spesa->aggiungiListaSpesa("zucchine");
     spesa->aggiungiListaSpesa("meloni");
     spesa->rimuoviListaSpesa("errore");
     spesa->rimuoviListaSpesa("zucchine");

     cout << spesa->getNome() <<endl;
     cout<<spesa->generaNota()<<endl;
     spesa->setSvolto();
     cout<<spesa->generaNota()<<endl;
     cout<<"Questo incarico vale: "<<spesa->calcolaPunteggio()<<" punti!"<<endl;
     cout<<"***"<<endl;

 }

*/


