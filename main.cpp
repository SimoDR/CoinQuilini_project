#include "Incarico.h"
#include<iostream>
using namespace std;

int main(){
	Faccenda * s=new Spazzatura();
	cout<< s->generaNota() <<endl;
	cout<<s->Faccenda::generaNota()<<endl;

	Incarico * c=new Cucina();
	cout<< c->generaNota() <<endl;
	
	Pagamento * b=new Bolletta();
	b->setImporto(23.5);
	cout<< b->generaNota() <<endl;

	//prova prova prova



}