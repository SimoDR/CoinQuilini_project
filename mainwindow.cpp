#include "mainwindow.h"
#include "controller.h"
#include "adminpanel.h"

Mainwindow::Mainwindow(QWidget *parent, Controller* c, QString inquilino) : QMainWindow(parent),  _controller(c), _inquilino(inquilino)
{
    _mainLayout=new QHBoxLayout;
    setWindowTitle("Qoinquilini-Benvenuto " + _inquilino);

    //create menu bar
    addmenubar();
    //create calendar and buttons
    addcalendar();
    //create the 3 lists and labels
    addlists();
    //setting the central widget of the window
    _mainWidget=new QWidget;
    _mainWidget->setLayout(_mainLayout);
    setCentralWidget(_mainWidget);
}


void Mainwindow::buildAdminPanel()
{
    adminPanel* adminpanel= new adminPanel(_controller,this);
    adminpanel->show();
}

void Mainwindow::buildSelezione()
{
    SelezioneDialog * select= new SelezioneDialog(this);
    connect(select, SIGNAL(datiSelezionati(const QString &, bool)),this, SLOT(buildForm(const QString &, bool)));
    select->show();
}

void Mainwindow::buildForm(const QString & tipo, bool regolare)
{
    FormIncarico *form=new FormIncarico(tipo, regolare, _controller->getInquilini(), this);
    form->show();
    connect(form, SIGNAL(inviaDati(const vector<string> &)), this, SLOT(buildIncarico(const vector<string> &)));
}

void Mainwindow::buildIncarico(const vector<string> & parametri)
{
    _controller->creaNuovoIncarico(parametri);
}

void Mainwindow::buildListaIncarichi(const QDate & giorno)
{
    string data=giorno.toString("d/M/yyyy").toStdString();
    vector<string> incaricati;
    vector<string> incarichi=_controller->incarichiGiorno(data, incaricati);
    ListaIncarichi *lista=new ListaIncarichi(giorno.toString("d/M/yyyy"),_controller->isAdmin(_inquilino.toStdString()), incarichi, incaricati, this);
    lista->show();
}

void Mainwindow::addbuttons()
{

    _incarico= new QPushButton;
    _incarico->setText("Aggiungi un incarico");
    connect(_incarico, SIGNAL(clicked()), this, SLOT(buildSelezione()));
    _listaSpesa= new QPushButton;
    _listaSpesa->setText("lista della spesa");
    _creDeb= new QPushButton;
    _creDeb->setText("il tuo credito / debito");
    _calendarLayout->addWidget(_incarico);
    _calendarLayout->addWidget(_listaSpesa);
    _calendarLayout->addWidget(_creDeb);

    if (_controller->isAdmin(_inquilino.toStdString())) {
        _admin= new QPushButton;
        _admin->setText("Apri pannello admin");
        connect(_admin, SIGNAL(clicked()), this, SLOT(buildAdminPanel()));
        _calendarLayout->addWidget(_admin);
    }

    //add buttons to the layout
}

void Mainwindow::addcalendar()
{

    _calendar=new QCalendarWidget;
    connect(_calendar, SIGNAL(activated(const QDate &)), this, SLOT(buildListaIncarichi(const QDate &)));
    _calendarLayout= new QVBoxLayout;

    //add calendar to the layout
    _calendarLayout->addWidget(_calendar);

    //buttons
    addbuttons();

    _calendarGroup=new QGroupBox("Calendario");
    _calendarGroup->setLayout(_calendarLayout);

    //add to the main layout
    _mainLayout->addWidget(_calendarGroup);
}

void Mainwindow::addlists()
{


    //prev list and label
    QLabel* prec= new QLabel;
    prec->setText(((_calendar->selectedDate()).addDays(-1)).toString(Qt::SystemLocaleLongDate));

    QListWidget* preclist= new QListWidget;

    //selected day list and label
    QLabel* selected = new QLabel;

    selected->setText((_calendar->selectedDate()).toString(Qt::SystemLocaleLongDate));

    QListWidget* selectedlist= new QListWidget;

    //next list and label
    QLabel* succ= new QLabel;

    succ->setText(((_calendar->selectedDate()).addDays(1)).toString(Qt::SystemLocaleLongDate));

    QListWidget* succlist= new QListWidget;

    //layout add
    QVBoxLayout* listlayout = new QVBoxLayout;
    listlayout->addWidget(prec);
    listlayout->addWidget(preclist);
    listlayout->addWidget(selected);
    listlayout->addWidget(selectedlist);
    listlayout->addWidget(succ);
    listlayout->addWidget(succlist);


    _listGroup=new QGroupBox("I tuoi incarichi");
    _listGroup->setLayout(listlayout);

    //add to the main layout
    _mainLayout->addWidget(_listGroup);

}

void Mainwindow::addmenubar()
{
    _menuBar=menuBar();
    _file=new QMenu("File");
    _esci=new QAction("Esci");
    _file->addAction(_esci);
    _menuBar->addMenu(_file);
    _opzioni= new QMenu("Opzioni");
    _logOut=new QAction("Log out");
    _info=new QAction("info");         //this action could open a messagebox with the instructions and informations about the program
    _opzioni->addAction(_logOut);
    _opzioni->addAction(_info);
    _menuBar->addMenu(_opzioni);

}
