#ifndef FACCENDA_H
#define FACCENDA_H

#include "incarico.h"

class Faccenda: virtual public Incarico {
private:
    int _tempoStimato; // minuti per effettuare la faccenda
    static unsigned short int _pesoFaccenda;
public:
    Faccenda(const string& nome,Inquilino * incaricato,bool svolto, int tempoStimato);
    virtual ~Faccenda()=0;
    virtual string generaNota() const;
    virtual void exportXml(QXmlStreamWriter&,string data) const;
    static void importXml(QXmlStreamReader & xmlInput, vector<string> & parametri);
    virtual unsigned short int calcolaPunteggio() const;
};

#endif // FACCENDA_H
