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

class Controller;

class Mainwindow : public QMainWindow
{
    Q_OBJECT
private:
    Controller* controller; //controller figlio di mainwindow: alla distruzione della vista si distrugge in automatico anche il controller
    QHBoxLayout* mainlayout;
    QWidget*mainwidget;
    //layout calendario e buttons
    QGroupBox * calendargroup;
    QVBoxLayout* calendarlayout;
    QCalendarWidget* calendar;
    QPushButton* incarico;
    QPushButton* listaspesa;
    QPushButton* credeb;
    QPushButton* admin;
    //layout 3 liste
    QGroupBox* listgroup;
    QVBoxLayout* listlayout;
    QLabel* prec;
    QListWidget* preclist;
    QLabel* selected;
    QListWidget* selectedlist;
    QLabel* succ;
    QListWidget* succlist;

    //menu bar
    QMenuBar* menubar;
    QMenu *file;
    QAction *esci;
    QMenu *opzioni;
    QAction* logout;
    QAction* info;

    //inquilino loggato
    QString inquilino;

    void addbuttons();
    void addcalendar();
    void addlists();
    void addmenubar();
    QString login();

public:
    explicit Mainwindow(QWidget *parent, Controller*, QString);

signals:

};

#endif // MAINWINDOW_H
