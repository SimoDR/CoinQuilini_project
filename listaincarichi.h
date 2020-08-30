#ifndef LISTAINCARICHI_H
#define LISTAINCARICHI_H

#include <QDialog>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <vector>
#include <string>
#include <QDate>
#include "data.h"
using std::vector;
using std::string;

class ListaIncarichi : public QDialog
{
    Q_OBJECT
private:
    QListWidget * _lista;
    QVBoxLayout *_mainLayout;
    QPushButton * _rimuovi;
    QPushButton * _riassegna;
    QDate _data;
    void buildButtons();
    void buildLista(const vector<string> &, const vector<string> &);
public:
    ListaIncarichi(QString data,bool admin, vector<string> incarichi, vector<string> incaricati, QWidget *parent=nullptr);

private slots:
    void raccogliDatiIncarico();
    void raccogliDaRiassegnare();
    void raccogliDaEliminare();
    void enableButtons();
signals:
    void datiIncarico(const QDate &, unsigned int );
    void riassegnaIncarico(const QDate &, unsigned int, ListaIncarichi *);
    void eliminaIncarico(const Data &, unsigned int);
};

#endif // LISTAINCARICHI_H
