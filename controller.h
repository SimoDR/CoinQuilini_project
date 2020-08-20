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
    void rimuoviInquilino(unsigned int);
    vector<string> getInquilinoPos(unsigned int);
    void aggiungiInquilino(const QString &, const QString &);
    void modificaInquilino(const QString &, const QString &, unsigned int);
    void checkAdmin(unsigned int);
    unsigned short int isAdmin(const string &) const;
signals:

public slots:
    void creaNuovoIncarico(vector<string> parametri); //slot per la creazione di un nuovo incarico


};

#endif // CONTROLLER_H
