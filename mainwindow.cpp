#include "mainwindow.h"
#include "controller.h"

Mainwindow::Mainwindow(QWidget *parent, Controller* c, QString inquilino) : QMainWindow(parent),  controller(c), inquilino(inquilino)
{
    mainlayout=new QHBoxLayout;
    setWindowTitle("Qoinquilini-Benvenuto " + inquilino);
    //create menu bar
    addmenubar();
    //create calendar and buttons
    addcalendar();
    //create the 3 lists and labels
    addlists();
    //setting the central widget of the window
    mainwidget=new QWidget;
    mainwidget->setLayout(mainlayout);
    setCentralWidget(mainwidget);
}

void Mainwindow::addbuttons()
{
    incarico= new QPushButton;
    incarico->setText("Aggiungi un incarico");
    listaspesa= new QPushButton;
    listaspesa->setText("lista della spesa");
    credeb= new QPushButton;
    credeb->setText("il tuo credito / debito");
    admin= new QPushButton;
    admin->setText("Apri pannello admin");

    //add buttons to the layout
    calendarlayout->addWidget(incarico);
    calendarlayout->addWidget(listaspesa);
    calendarlayout->addWidget(credeb);
    calendarlayout->addWidget(admin);
}

void Mainwindow::addcalendar()
{
    calendar=new QCalendarWidget;
    calendarlayout= new QVBoxLayout;

    //add calendar to the layout
    calendarlayout->addWidget(calendar);

    //buttons
    addbuttons();

    calendargroup=new QGroupBox("Calendario");
    calendargroup->setLayout(calendarlayout);

    //add to the main layout
    mainlayout->addWidget(calendargroup);
}

void Mainwindow::addlists()
{


    //prev list and label
    QLabel* prec= new QLabel;
    prec->setText(((calendar->selectedDate()).addDays(-1)).toString(Qt::SystemLocaleLongDate));
    QListWidget* preclist= new QListWidget;

    //selected day list and label
    QLabel* selected = new QLabel;
    selected->setText((calendar->selectedDate()).toString(Qt::SystemLocaleLongDate));
    QListWidget* selectedlist= new QListWidget;

    //next list and label
    QLabel* succ= new QLabel;
    succ->setText(((calendar->selectedDate()).addDays(1)).toString(Qt::SystemLocaleLongDate));
    QListWidget* succlist= new QListWidget;

    //layout add
    QVBoxLayout* listlayout = new QVBoxLayout;
    listlayout->addWidget(prec);
    listlayout->addWidget(preclist);
    listlayout->addWidget(selected);
    listlayout->addWidget(selectedlist);
    listlayout->addWidget(succ);
    listlayout->addWidget(succlist);

    listgroup=new QGroupBox("I tuoi incarichi");
    listgroup->setLayout(listlayout);

    //add to the main layout
    mainlayout->addWidget(listgroup);
}

void Mainwindow::addmenubar()
{
    menubar=menuBar();
    file=new QMenu("File");
    esci=new QAction("Esci");
    file->addAction(esci);
    menubar->addMenu(file);
    opzioni= new QMenu("Opzioni");
    logout=new QAction("Log out");
    info=new QAction("info");         //this action could open a messagebox with the instructions and informations about the program
    opzioni->addAction(logout);
    opzioni->addAction(info);
    menubar->addMenu(opzioni);
}
