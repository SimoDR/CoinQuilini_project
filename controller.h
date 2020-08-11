#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "mainwindow.h"
#include <QString>
#include <QMessageBox>
#include <vector>
#include "listainquilini.h"
using std::vector;

class Controller : public QObject
{
    Q_OBJECT
private:
    ListaInquilini* _listainquilini;
public:
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



};

#endif // CONTROLLER_H
