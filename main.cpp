#include "Incarico.h"
#include<iostream>
using namespace std;

int main(){
	Faccenda * spazz=new Spazzatura();
	cout<< spazz->generaNota() <<endl;
	cout<<spazz->Faccenda::generaNota()<<endl;

	Incarico * cuc=new Cucina();
	cout<< cuc->generaNota() <<endl;
	
	Pagamento * boll=new Bolletta();
	boll->setImporto(23.5);
	cout<< boll->generaNota() <<endl;

	Pagamento * spesa=new Spesa();
	cout<<spesa->generaNota()<<endl;

	//prova prova prova



}