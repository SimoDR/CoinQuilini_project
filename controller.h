#ifndef CONTROLLER_H
#define CONTROLLER_H

#include<vector>
#include<string>
#include <stdlib.h>
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
#include "utilities.h"

using std::vector;
using std::string;

class Controller : public QObject
{
    Q_OBJECT
private:
    ListaInquilini _listaInquilini;
    Calendario _calendario; //DA COSTRUIRE dando la _listaInquilini
public:



    explicit Controller( QObject *parent = nullptr);
    bool login(const QString &, const QString &);
    vector<string> getInquilini();
    void rimuoviInquilino(unsigned int); //da controllare
    vector<string> getInquilinoPos(unsigned int);
    void aggiungiInquilino(const QString &, const QString &);
    void modificaInquilino(const QString &, const QString &, unsigned int);
    void checkAdmin(unsigned int);
    unsigned short int isAdmin(const string &) const;
    void buildLogin();

    void stampaCalendario() //DEBUG
    {
        _calendario.stampaGiorni();
    }
//    void stampaBuffer() //debug
//    {
//        _calendario._buffer.stampaBuffer();
//    }

signals:

public slots:

    void creaNuovoIncarico(vector<string> parametri); //slot per la creazione di un nuovo incarico

    void rimuoviIncarico(const Data& dataIncarico, unsigned int indiceIncarico);

    void posponiIncarico(const Data& dataIncarico, unsigned int indiceIncarico, unsigned int quantoPosporre, unsigned int posizioneInquilinoRichiedente); //MESSAGGIO DA DARE IN CASO NEGATIVO

    void riassegnaIncarico(const Data& dataIncarico, unsigned int indiceIncarico, const string &nomeInquilino); //solo l'admin

    void setIncaricoSvolto(const Data& dataIncarico, unsigned int indiceIncarico);

    void incrementaGiorno(); //MESSAGGIO PER CHI NON HA SVOLTO

    void checkIncarichiSvoltiPassato();

    void buildNota(const QDate &data, unsigned int pos);

    vector<string> incarichiGiorno(string giorno, vector<string> & incaricati);

};

#endif // CONTROLLER_H
