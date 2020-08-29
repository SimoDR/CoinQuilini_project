#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
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
#include <QGroupBox> //layout with a title
#include "selezionedialog.h"
#include "formincarico.h"
#include "listaincarichi.h"

class Controller;

class Mainwindow : public QMainWindow
{
    Q_OBJECT
private:
    Controller *_controller; //controller figlio di mainwindow: alla distruzione della vista si distrugge in automatico anche il controller
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

    //menu bar
    QMenuBar* _menuBar;
    QMenu *_file;
    QAction *_esci;
    QMenu *_opzioni;
    QAction* _logOut;
    QAction* _info;

    //inquilino loggato
    QString _inquilino;

    void addbuttons();
    void addcalendar();
    void addlists();
    void addmenubar();
    void populateList(QListWidget *, const QString &, const QDate &);
    QString login();


public:
    explicit Mainwindow(QWidget *parent, Controller*, QString);

signals:

private slots:
    void buildAdminPanel();
    void buildSelezione();
    void buildForm(const QString &, bool);
    void buildIncarico(const vector<string> &);
    void buildListaIncarichi(const QDate &);
    void logOut();
    void refreshlists(const QDate &giorno);
    void impostaStile();
};

#endif // MAINWINDOW_H
