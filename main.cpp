
#include <iostream>
#include<vector>
#include <QApplication>
#include "calendario.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller controller;
    return a.exec();
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

     Inquilino * simone = new Inquilino("simone","password");

     Faccenda * spazz=new Spazzatura("ritiro rifiuti", "secco",20,simone,true);
     cout<< spazz->generaNota() <<endl;
     cout<<"Questo incarico vale: "<<spazz->calcolaPunteggio()<<" punti!"<<endl;
     cout<<"***"<<endl;

     Incarico * cuc=new Cucina("pranzo",60,4);
     cout<< cuc->generaNota() <<endl;
     cout<<"Questo incarico vale: "<<cuc->calcolaPunteggio()<<" punti!"<<endl;
     cout<<"***"<<endl;

     Pagamento * boll=new Bolletta("luce-gas",250.30,Data(1,1,2021),simone,true);
     cout<< boll->generaNota() <<endl;
     cout<<"Questo incarico vale: "<<boll->calcolaPunteggio()<<" punti!"<<endl;
     cout<<"***"<<endl;

     Spesa * spesa=new Spesa("panificio",10,30,10);
     spesa->aggiungiListaSpesa("banane");
     spesa->aggiungiListaSpesa("zucchine");
     spesa->aggiungiListaSpesa("meloni");
     spesa->rimuoviListaSpesa("errore");
     spesa->rimuoviListaSpesa("zucchine");

     cout<<spesa->generaNota()<<endl;
     spesa->setSvolto();
     cout<<spesa->generaNota()<<endl;
     cout<<"Questo incarico vale: "<<spesa->calcolaPunteggio()<<" punti!"<<endl;
     cout<<"***"<<endl;

 }


*/
