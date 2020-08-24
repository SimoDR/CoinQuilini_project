#ifndef CONTROLLER_H
#define CONTROLLER_H

#include<vector>
#include<string>
#include <QObject>
#include "mainwindow.h"
#include "listainquilini.h"
#include <QString>
#include <QMessageBox>
#include "data.h"
#include "calendario.h"

#include "pulizia.h"
#include "spesa.h"
#include "spazzatura.h"
#include "cucina.h"
#include "bolletta.h"

using std::vector;
using std::string;

class Controller : public QObject
{
    Q_OBJECT
private:
    Mainwindow* view;
    
public:

    ListaInquilini _listaInquilini;
    Calendario _calendario; //DA COSTRUIRE dando la _listaInquilini

    explicit Controller( QObject *parent = nullptr);
    bool login(const QString &, const QString &);   //debug, da togliere
    vector<string> getInquilini();
    void rimuoviInquilino(unsigned int); //da controllare
    vector<string> getInquilinoPos(unsigned int);
    void aggiungiInquilino(const QString &, const QString &);
    void modificaInquilino(const QString &, const QString &, unsigned int);
    void checkAdmin(unsigned int);
    unsigned short int isAdmin(const string &) const;

    void stampaCalendario() //DEBUG
    {
        _calendario.stampaGiorni();
    }
    void stampaBuffer()
    {
        _calendario._buffer.stampaBuffer();
    }

signals:

public slots:

    void creaNuovoIncarico(vector<string> parametri); //slot per la creazione di un nuovo incarico

    void rimuoviIncarico(const Data& dataIncarico, int indiceIncarico);

    bool posponiIncarico(const Data& dataIncarico, int indiceIncarico, unsigned int quantoPosporre, unsigned int posizioneInquilinoRichiedente); //MESSAGGIO DA DARE IN CASO NEGATIVO

    bool riassegnaIncarico(const Data& dataIncarico, int indiceIncarico, unsigned int posNuovo); //solo l'admin

    void setIncaricoSvolto(const Data& dataIncarico, int indiceIncarico);

    void incrementaGiorno(); //MESSAGGIO PER CHI NON HA SVOLTO

    void modificaIncarico(const Data &dataIncarico, int indiceIncarico, vector<string> parametri);

};

#endif // CONTROLLER_H
