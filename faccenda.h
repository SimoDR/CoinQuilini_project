#ifndef FACCENDA_H
#define FACCENDA_H

#include "incarico.h"

class Faccenda: virtual public Incarico
{
private:
    int _tempoStimato; // minuti per effettuare la faccenda
    static unsigned short int _pesoFaccenda;

public:
    Faccenda(int tempoStimato);
    Faccenda() {}
    virtual ~Faccenda()=0;

    //get
    virtual string generaNota() const;

    virtual unsigned short int calcolaPunteggio() const;

    // input/output
    static void importXml(QXmlStreamReader & xmlInput, vector<string> & parametri);
    virtual void exportXml(QXmlStreamWriter&,string data) const;
};

#endif // FACCENDA_H
