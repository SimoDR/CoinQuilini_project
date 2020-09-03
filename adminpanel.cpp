#include "adminpanel.h"

void adminPanel::buildLista()
{
    _elencoInquilini= new QListWidget;
    aggiornaLista();
    _mainLayout->addWidget(_elencoInquilini);
    impostaStile();
    connect(_elencoInquilini,SIGNAL(itemSelectionChanged()),this, SLOT(enableButtons()));
}

void adminPanel::buildBottoni()
{
    _inserisci=new QPushButton("Inserisci");
    _buttonLayout->addWidget(_inserisci);
    _modifica=new QPushButton("Modifica");
    _buttonLayout->addWidget(_modifica);
    _rimuovi=new QPushButton("Rimuovi");
    _buttonLayout->addWidget(_rimuovi);
    _mainLayout->addLayout(_buttonLayout);
    connect(_rimuovi, SIGNAL(clicked()), this, SLOT(buildRimuovi()));
    connect(_inserisci, SIGNAL(clicked()), this, SLOT(buildAggiungi()));
    connect(_modifica, SIGNAL(clicked()), this, SLOT(buildModifica()));
}

void adminPanel::aggiornaLista()
{
    _elencoInquilini->clear();
    vector<string> elenco= _controller->getInquilini();
    if (elenco.size()>0)
        for (auto i=elenco.cbegin(); i!=elenco.cend(); i++)
            _elencoInquilini->addItem(QString::fromStdString(*i));
    _rimuovi->setDisabled(true);
    _modifica->setDisabled(true);
}

void adminPanel::impostaStile()
{
    QFile file(":/resources/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    setStyleSheet(styleSheet);
}

adminPanel::adminPanel(Controller *c, QWidget *parent) : QDialog(parent), _controller(c), _mainLayout(new QHBoxLayout), _buttonLayout(new QVBoxLayout)
{
    setWindowTitle("Pannello admin");
    setModal(true);
    //costruzione bottoni
    buildBottoni();
    //costruzione lista
    buildLista();
    setLayout(_mainLayout);
}

void adminPanel::buildAggiungi()
{
    CreaModificaInquilino *form= new CreaModificaInquilino(this);
    form->setWindowTitle("Aggiungi un nuovo inquilino");
    form->setFixedSize(form->sizeHint());
    form->show();
    connect(form, SIGNAL(invia(const QString &, const QString &)), this, SLOT(aggiungi(const QString &, const QString &)));
}
//TODO: modifica dell'utente
void adminPanel::buildModifica()
{
    try {
        _controller->checkAdmin(_elencoInquilini->currentRow());
        vector<string> utente= _controller->getInquilinoPos(_elencoInquilini->currentRow());
        CreaModificaInquilino *form= new CreaModificaInquilino(this, QString::fromStdString(utente[0]), QString::fromStdString(utente[1]));
        form->setWindowTitle("Modifica i dati dell'inquilino");
        form->setFixedSize(form->sizeHint());
        form->show();
        connect(form, SIGNAL(invia(const QString &, const QString &)), this, SLOT(modifica(const QString &, const QString &)));
    }
    catch (std::logic_error * e) {
        showMessage(QString::fromStdString(e->what()));
    }
}

void adminPanel::buildRimuovi()
{
    try {
        _controller->checkAdmin(_elencoInquilini->currentRow());
        QString details="La rimozione comporta:\n"
                        "- l'appianamento della situazione contabile della casa\n"
                        "- la perdita dei dati dell'inquilino eliminato\n"
                        "- la riassegnazione automatica degli incarichi futuri dell'inquilino eliminato";
        int scelta = confirmationMessage(this, "Sei sicuro di voler eliminare l'inquilino selezionato?",details);
        if (scelta==QMessageBox::Yes){
            showMessage(QString::fromStdString (_controller->showCdCasa()) );
            _controller->rimuoviInquilino(_elencoInquilini->currentRow());
            showSuccess("Inquilino rimosso con successo");
            aggiornaLista();
        }
    }
    catch (std::logic_error * e) {
        showMessage(QString::fromStdString(e->what()));
    }
}

void adminPanel::aggiungi(const QString & user, const QString & pw)
{
    _controller->aggiungiInquilino(user,pw);
    aggiornaLista();
}

void adminPanel::modifica(const QString & user, const QString & pw)
{
    _controller->modificaInquilino(user, pw, _elencoInquilini->currentRow());
    aggiornaLista();
}

void adminPanel::enableButtons()
{
    _modifica->setDisabled(false);
    _rimuovi->setDisabled(false);
}
