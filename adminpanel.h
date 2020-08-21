#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "controller.h"
#include <QMessageBox>
#include "creamodificainquilino.h"

class adminPanel : public QDialog {
    Q_OBJECT
private:
    Controller * _controller;
    QListWidget * _elencoInquilini;
    QPushButton * _inserisci;
    QPushButton * _modifica;
    QPushButton * _rimuovi;
    QHBoxLayout *_mainLayout;
    QVBoxLayout * _buttonLayout;
    void buildLista();
    void buildBottoni();
    void aggiornaLista();
    void buildMessage(const QString &, const QString &);
public:
    adminPanel(Controller *c, QWidget *parent = nullptr);

signals:
private slots:
    void buildAggiungi();
    void buildModifica();
    void buildRimuovi();
    void aggiungi(const QString &, const QString &);
    void modifica(const QString &, const QString &);
    void enableButtons();
};

#endif // ADMINPANEL_H
