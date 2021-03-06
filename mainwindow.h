#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCalendarWidget>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QDate>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QGroupBox>
#include <QTimer>
#include "data.h"
#include "selezionedialog.h"
#include "formincarico.h"
#include "listaincarichi.h"
#include "riassegnadialog.h"
#include "posponidialog.h"

class Controller;

class Mainwindow : public QMainWindow
{
    Q_OBJECT
private:
    Controller *_controller;
    QHBoxLayout* _mainLayout;
    QWidget*_mainWidget;
    //layout calendario e buttons
    QGroupBox * _calendarGroup;
    QVBoxLayout* _calendarLayout;
    QCalendarWidget* _calendar;
    QPushButton* _incarico;
    QPushButton* _punteggio;
    QPushButton* _creDeb;
    QPushButton* _admin;
    //layout 3 liste
    QGroupBox *_listGroup;
    QVBoxLayout *_listLayout;
    QLabel* _prec;
    QListWidget* _precList;
    QLabel* _selected;
    QListWidget* _selectedList;
    QLabel* _succ;
    QListWidget* _succList;
    QPushButton * _posponi;
    QPushButton * _svolto;
    //menu bar
    QMenuBar* _menuBar;
    QMenu *_file;
    QAction *_esci;
    QMenu *_opzioni;
    QAction* _logOut;
    QAction* _info;
    //inquilino loggato
    QString _inquilino;

    QTimer * _timer;
    Data _dataOdierna;

    void addbuttons();
    void addcalendar();
    void addlists();
    void addmenubar();
    void populateList(QListWidget *, const QString &, const QDate &);
    QString login();
    void inizializzaTimer();


public:
    Mainwindow(QWidget *parent, Controller*, QString);

signals:
    void datiPosponi(const Data&, unsigned int, unsigned int, const string &);

private slots:
    void buildAdminPanel();
    void buildSelezione();
    void buildPunteggioPanel();
    void buildCreDeb();
    void buildForm(const QString &, bool);
    void buildIncarico(const vector<string> &);
    void buildListaIncarichi(const QDate &);
    void buildListaIncarichi(const Data &);
    void logOut();
    void refreshlists(const QDate &giorno);
    void impostaStile();
    void mezzanotte();
    void buildRiassegna(const QDate &, unsigned int, ListaIncarichi *);
    void buildInfo();
    void notaPrec();
    void notaSelected();
    void notaSucc();
    void svoltoSelected();
    void buildPosponi();
    void posponiSelected(unsigned int, unsigned int);
    void enableButtons();
    void disableButtons();
};

#endif // MAINWINDOW_H
