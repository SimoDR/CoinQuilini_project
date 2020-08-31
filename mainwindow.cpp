#include "mainwindow.h"
#include "controller.h"
#include "adminpanel.h"

Mainwindow::Mainwindow(QWidget *parent, Controller* c, QString inquilino) : QMainWindow(parent),  _controller(c), _inquilino(inquilino), _dataOdierna(Data::unixDateToData(std::chrono::system_clock::now()))
{
    _mainLayout=new QHBoxLayout;
    setWindowTitle("CoinQuilini - Benvenuto " + _inquilino);

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
    impostaStile();
    inizializzaTimer();
}

void Mainwindow::impostaStile()
{
    QFile file(":/resources/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    setStyleSheet(styleSheet);
}

void Mainwindow::mezzanotte()
{
    Data adesso=Data::unixDateToData(std::chrono::system_clock::now());
    if(adesso != _dataOdierna)
    {
        _controller->incrementaGiorno();
    }
    _dataOdierna=Data::unixDateToData(std::chrono::system_clock::now());
}

void Mainwindow::buildRiassegna(const QDate &data, unsigned int pos, ListaIncarichi * lista)
{
    Data giorno((data.toString("d/M/yyyy")).toStdString());
    RiassegnaDialog* riassegna=new RiassegnaDialog(giorno, pos, _controller->getInquilini(), this);
    riassegna->show();
    connect(riassegna, SIGNAL(inviaInquilino(const Data &, unsigned int, const string &)), _controller, SLOT(riassegnaIncarico(const Data & , unsigned int, const string & )));
    connect(riassegna, SIGNAL(inviaInquilino(const Data &, unsigned int, const string &)), lista, SLOT(close()));
    connect(riassegna, SIGNAL(inviaInquilino(const Data &, unsigned int, const string &)), this, SLOT(buildListaIncarichi(const Data &)));
}

void Mainwindow::buildInfo()
{
    showSuccess("Programma creato con estrema fatica dai saccensi Antonio Badan, Simone De Renzis e Francesco Trolese \n ad astra per aspera!");
}

void Mainwindow::notaPrec()
{
    QDate giorno=_calendar->selectedDate().addDays(-1);
    unsigned int pos= _precList->currentRow();
    QMetaObject::invokeMethod(_controller, "buildNota", Qt::DirectConnection, Q_ARG(QDate, giorno), Q_ARG(unsigned int, pos));
}

void Mainwindow::notaSelected()
{
    QDate giorno=_calendar->selectedDate();
    unsigned int pos= _selectedList->currentRow();
    QMetaObject::invokeMethod(_controller, "buildNota", Qt::DirectConnection, Q_ARG(QDate, giorno), Q_ARG(unsigned int, pos));
}

void Mainwindow::notaSucc()
{
    QDate giorno=_calendar->selectedDate().addDays(1);
    unsigned int pos= _succList->currentRow();
    QMetaObject::invokeMethod(_controller, "buildNota", Qt::DirectConnection, Q_ARG(QDate, giorno), Q_ARG(unsigned int, pos));
}

void Mainwindow::svoltoSelected()
{
    int successo=confirmationMessage("Confermi tu, vile marrano, di avere svolto l'incarico che hai selezionato?");
    if(successo==QMessageBox::Yes)
    {
        Data giorno(((_calendar->selectedDate()).toString("d/M/yyyy")).toStdString());
        unsigned int pos= _selectedList->currentRow();
        _controller->setIncaricoSvolto(giorno, pos);
        _posponi->setDisabled(true);
        _svolto->setDisabled(true);
    }
}

void Mainwindow::buildPosponi()
{
    PosponiDialog * posponi=new PosponiDialog(this);
    posponi->show();
    connect(posponi, SIGNAL(numero(unsigned int)), this, SLOT(posponiSelected(unsigned int)));
    connect(this, SIGNAL(datiPosponi(const Data& , unsigned int , unsigned int, const string &)), _controller, SLOT(posponiIncarico(const Data& , unsigned int , unsigned int, const string &)));
    _posponi->setDisabled(true);
    _svolto->setDisabled(true);
}

void Mainwindow::posponiSelected(unsigned int num)
{
    Data giorno(((_calendar->selectedDate()).toString("d/M/yyyy")).toStdString());
    unsigned int pos=_selectedList->currentRow();
    string inquilino=_inquilino.toStdString();
    emit datiPosponi(giorno, pos, num, inquilino);
}

void Mainwindow::enableButtons()
{
    _svolto->setEnabled(true);
    _posponi->setEnabled(true);
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

void Mainwindow::buildPunteggioPanel()
{
    showSuccess( QString::fromStdString(_controller->showPunteggio(_inquilino)) );
}

void Mainwindow::buildCreDeb()
{
    showSuccess( QString::fromStdString(_controller->showCreDeb(_inquilino)) );
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
    refreshlists(_calendar->selectedDate());
}

void Mainwindow::buildListaIncarichi(const QDate & giorno)
{
    string data=giorno.toString("d/M/yyyy").toStdString();
    vector<string> incaricati;
    vector<string> incarichi=_controller->incarichiGiorno(data, incaricati);
    ListaIncarichi *lista=new ListaIncarichi(giorno.toString("d/M/yyyy"),_controller->isAdmin(_inquilino.toStdString()), incarichi, incaricati, this);
    lista->show();
    connect(lista, SIGNAL(datiIncarico(const QDate &, unsigned int )), _controller, SLOT(buildNota(const QDate &, unsigned int)));
    connect(lista, SIGNAL(riassegnaIncarico(const QDate &, unsigned int, ListaIncarichi *)), this, SLOT(buildRiassegna(const QDate &, unsigned int, ListaIncarichi *)));
    connect(lista, SIGNAL(eliminaIncarico(const Data &, unsigned int)), _controller, SLOT(rimuoviIncarico(const Data&, unsigned int)));
    connect(lista, SIGNAL(eliminaIncarico(const Data &, unsigned int)), this, SLOT(buildListaIncarichi(const Data &)));
}

void Mainwindow::buildListaIncarichi(const Data & giorno)
{
    QDate data=QDate::fromString(QString::fromStdString(giorno.dataToString()),"d/M/yyyy");
    QMetaObject::invokeMethod(this, "buildListaIncarichi", Qt::DirectConnection, Q_ARG(QDate, data));
    QMetaObject::invokeMethod(this, "refreshlists", Qt::DirectConnection, Q_ARG(QDate, data));
}

void Mainwindow::logOut()
{
    this->close();
    _controller->buildLogin();
}

void Mainwindow::refreshlists(const QDate & giorno)
{
    _prec->setText((giorno.addDays(-1)).toString(Qt::SystemLocaleLongDate));
    populateList(_precList, _inquilino,giorno.addDays(-1));
    _selected->setText(giorno.toString(Qt::SystemLocaleLongDate));
    populateList(_selectedList, _inquilino,giorno);
    _succ->setText((giorno.addDays(1)).toString(Qt::SystemLocaleLongDate));
    populateList(_succList, _inquilino,giorno.addDays(1));
}

void Mainwindow::addbuttons()
{
    _punteggio= new QPushButton;
    _punteggio->setText("Il tuo punteggio");
    connect(_punteggio, SIGNAL(clicked()), this, SLOT(buildPunteggioPanel()));
    _creDeb= new QPushButton;
    _creDeb->setText("Il tuo credito / debito");
    connect(_creDeb, SIGNAL(clicked()), this, SLOT(buildCreDeb()));
    _calendarLayout->addWidget(_punteggio);
    _calendarLayout->addWidget(_creDeb);

    if (_controller->isAdmin(_inquilino.toStdString())) {
        _incarico= new QPushButton;
        _incarico->setText("Aggiungi un incarico");
        _calendarLayout->addWidget(_incarico);

        connect(_incarico, SIGNAL(clicked()), this, SLOT(buildSelezione()));
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
    connect(_calendar, SIGNAL(clicked(const QDate &)), this, SLOT(refreshlists(const QDate &)));
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
    _prec= new QLabel;
    _prec->setText(((_calendar->selectedDate()).addDays(-1)).toString(Qt::SystemLocaleLongDate));

    _precList= new QListWidget;
    populateList(_precList, _inquilino, (_calendar->selectedDate()).addDays(-1));
    connect(_precList,SIGNAL(itemActivated(QListWidgetItem *)),this, SLOT(notaPrec()));
    //selected day list, labe and buttons

    _selected = new QLabel;
    _selected->setText((_calendar->selectedDate()).toString(Qt::SystemLocaleLongDate));

    _selectedList= new QListWidget;
    populateList(_selectedList, _inquilino, (_calendar->selectedDate()));
    connect(_selectedList,SIGNAL(itemActivated(QListWidgetItem *)),this, SLOT(notaSelected()));
    QHBoxLayout *buttonsLayout=new QHBoxLayout;
    _svolto=new QPushButton("Svolto");
    connect(_svolto, SIGNAL(clicked()), this, SLOT(svoltoSelected()));
    _svolto->setDisabled(true);
    buttonsLayout->addWidget(_svolto);
    _posponi=new QPushButton("Posponi");
    _posponi->setDisabled(true);
    buttonsLayout->addWidget(_posponi);
    connect(_posponi, SIGNAL(clicked()), this, SLOT(buildPosponi()));
    connect(_selectedList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(enableButtons()));

    QGroupBox * selectedGroup= new QGroupBox;
    QVBoxLayout * selectedLayout=new QVBoxLayout;
    selectedLayout->addWidget(_selected);
    selectedLayout->addWidget(_selectedList);
    selectedLayout->addLayout(buttonsLayout);
    selectedGroup->setLayout(selectedLayout);

    //next list and label
    _succ= new QLabel;
    _succ->setText(((_calendar->selectedDate()).addDays(1)).toString(Qt::SystemLocaleLongDate));

    _succList= new QListWidget;
    populateList(_succList, _inquilino, (_calendar->selectedDate()).addDays(1));
    connect(_succList,SIGNAL(itemActivated(QListWidgetItem *)),this, SLOT(notaSucc()));

    //layout add
    QVBoxLayout* listlayout = new QVBoxLayout;
    listlayout->addWidget(_prec);
    listlayout->addWidget(_precList);
    listlayout->addWidget(selectedGroup);
    listlayout->addWidget(_succ);
    listlayout->addWidget(_succList);


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
    connect(_esci, SIGNAL(triggered()), this, SLOT(close()));
    _file->addAction(_esci);
    _menuBar->addMenu(_file);
    _opzioni= new QMenu("Opzioni");
    _logOut=new QAction("Log out");
    connect(_logOut, SIGNAL(triggered()), this, SLOT(logOut()));
    _info=new QAction("info");         //this action could open a messagebox with the instructions and informations about the program
    connect(_info, SIGNAL(triggered()), this, SLOT(buildInfo()));
    _opzioni->addAction(_logOut);
    _opzioni->addAction(_info);
    _menuBar->addMenu(_opzioni);

}

void Mainwindow::populateList(QListWidget *lista, const QString & utente, const QDate & giorno)
{
    string data=giorno.toString("d/M/yyyy").toStdString();
    vector<string> incaricati;
    vector<string> incarichi=_controller->incarichiGiorno(data, incaricati);
    lista->clear();
    for(auto ci=incarichi.cbegin();ci!=incarichi.cend();ci++)
        lista->addItem(QString::fromStdString(*ci));
    int cont=0;
    for(auto ci=incarichi.cbegin();ci!=incarichi.cend();ci++)
    {
        if(incaricati[cont]!=utente.toStdString())
            (lista->item(cont))->setHidden(true);
        cont++;
    }
}

void Mainwindow::inizializzaTimer()
{
    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(mezzanotte()));
    _timer->setInterval(10000); //ogni 10 secondi controlla
    _timer->setSingleShot(false);
    _timer->start();
}
