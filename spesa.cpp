#include "spesa.h"

unsigned short int Spesa::_pesoSpesa=10; // => 1 punto ogni 10 articoli comprati

Spesa* Spesa::clone() const {return new Spesa(*this);}

void Spesa::setArticoli(const unsigned short & x)
{
    _numeroArticoli=x;
}

bool Spesa::posponi(const Data d) const{
    return true;
}

string Spesa::generaNota() const {
    if ( ! getSvolto() ){
        return "La lista della spesa è... "; // chiama stampaLista Spesa
    }
    else{
        return "Spesa di "+std::to_string(_numeroArticoli)+" articoli";
    }
}

void Spesa::exportXml(QXmlStreamWriter & xmlOutput) const
{
    xmlOutput.writeStartElement(QString::fromStdString("SPESA"));
    Faccenda::exportXml(xmlOutput);
    xmlOutput.writeTextElement("numeroArticoli", QString::fromStdString(std::to_string(_numeroArticoli)));
    xmlOutput.writeEndElement();
}

//ricordarsi di aggiornare _articoli quando viene conclusa una spesa

unsigned short int Spesa::calcolaPunteggio() const{
        unsigned short int p=_numeroArticoli/_pesoSpesa;
        controlloSoglia(p);
        return p;
}
