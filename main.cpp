<<<<<<< HEAD

#include <iostream>
#include<vector>
#include <QApplication>
#include "calendario.h"
#include "login.h"
using std::cout;
using std::endl;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller controller;
    Login l(nullptr, &controller);
    l.show();
    return a.exec();

}

/*
il main della gerarchia
********************************

#include "Incarico.h"
#include<iostream>
using namespace std;

int main(){
	Faccenda * spazz=new Spazzatura();
	cout<< spazz->generaNota() <<endl;
	cout<<spazz->Faccenda::generaNota()<<endl;
	cout<<"Questo incarico vale: "<<spazz->calcolaPunteggio()<<" punti!"<<endl;
	cout<<"***"<<endl;

	Incarico * cuc=new Cucina();
	cout<< cuc->generaNota() <<endl;
	cout<<"Questo incarico vale: "<<cuc->calcolaPunteggio()<<" punti!"<<endl;
	cout<<"***"<<endl;
	
	Pagamento * boll=new Bolletta();
	boll->setImporto(50.6);
	cout<< boll->generaNota() <<endl;
	cout<<"Questo incarico vale: "<<boll->calcolaPunteggio()<<" punti!"<<endl;
	cout<<"***"<<endl;

	Pagamento * spesa=new Spesa();
	cout<<spesa->generaNota()<<endl;
	spesa->setSvolto();
	cout<<spesa->generaNota()<<endl;
	cout<<"Questo incarico vale: "<<spesa->calcolaPunteggio()<<" punti!"<<endl;
	cout<<"***"<<endl;

}

*/
=======

>>>>>>> gerarchia


