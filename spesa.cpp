#include "spesa.h"

unsigned short int Spesa::_pesoSpesa=10; // => 1 punto ogni 10 articoli comprati

Spesa::Spesa(const std::string& nome, float importo, int tempoStimato, unsigned short numeroArticoli, Inquilino *incaricato, bool svolto):
    Incarico(nome,incaricato,svolto), Pagamento(importo), Faccenda(tempoStimato), _numeroArticoli(numeroArticoli) {}

Spesa* Spesa::clone() const {return new Spesa(*this);}

bool Spesa::posponi(const Data& d) const
{
    return Incarico::posponi(d) && _numeroArticoli <= 30;
}

string Spesa::generaNota() const
{
    return "SPESA\n\n"+Incarico::generaNota()+"\n"+Faccenda::generaNota()+"\n"+Pagamento::generaNota()+
            "\nPunteggio: "+std::to_string(calcolaPunteggio())+" punti \n"+"Numero articoli: "+
            std::to_string(_numeroArticoli)+"\n\n"+"Andiamo a fare compere!";
}

void Spesa::exportXml(QXmlStreamWriter & xmlOutput,string data) const
{
    xmlOutput.writeStartElement(QString::fromStdString("SPESA"));
    Faccenda::exportXml(xmlOutput,data);
    xmlOutput.writeTextElement("importo", QString::fromStdString(std::to_string(getImporto())));
    xmlOutput.writeTextElement("numeroArticoli", QString::fromStdString(std::to_string(_numeroArticoli)));
    xmlOutput.writeEndElement();
}

void Spesa::importXml(QXmlStreamReader & xmlInput, vector<string> & parametri)
{
    Faccenda::importXml(xmlInput,parametri);

    string numeroArticoli,importo;
    assignWithXml(xmlInput, "importo", importo);
    assignWithXml(xmlInput, "numeroArticoli", numeroArticoli);


    parametri[8]=importo;
    parametri[7]=numeroArticoli;
    parametri[1]="Spesa";

}

std::string Spesa::getLabel() const {return "Spesa";}

unsigned short int Spesa::calcolaPunteggio() const
{
    return controlloSoglia(_numeroArticoli/_pesoSpesa);
}
