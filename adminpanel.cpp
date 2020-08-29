#include "adminpanel.h"

void adminPanel::buildLista()
{
    _elencoInquilini= new QListWidget;
    aggiornaLista();
    _mainLayout->addWidget(_elencoInquilini);
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

void adminPanel::buildMessage(const QString & title, const QString & message)
{
    QMessageBox *error= new QMessageBox;
    setWindowModality(Qt::WindowModal);
    error->setWindowTitle(title);
    error->setText(message);
    error->exec();
}

adminPanel::adminPanel(Controller *c, QWidget *parent) : QDialog(parent), _controller(c), _mainLayout(new QHBoxLayout), _buttonLayout(new QVBoxLayout)
{
    setWindowTitle("Pannello admin");
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
        form->show();
        connect(form, SIGNAL(invia(const QString &, const QString &)), this, SLOT(modifica(const QString &, const QString &)));
    }
    catch (std::logic_error * e) {
        buildMessage("Attenzione", e->what());

    }
}

void adminPanel::buildRimuovi()
{
    try {
        _controller->checkAdmin(_elencoInquilini->currentRow());
        QMessageBox *conferma=new QMessageBox;
        conferma->setWindowTitle("Rimozione inquilino");
        conferma->setText("Sei sicuro di voler eliminare l'inquilino selezionato?");
        conferma->setDetailedText("La rimozione comporta la perdita dei dati dell'inquilino e la riassegnazione automatica di tutti gli incarichi a lui assegnati in futuro");
        conferma->setStandardButtons(QMessageBox::Yes | QMessageBox::No );
        conferma->setDefaultButton(QMessageBox::Yes);
        int scelta = conferma->exec();
        if (scelta==QMessageBox::Yes)
            _controller->rimuoviInquilino(_elencoInquilini->currentRow());
        showSuccess("Inquilino rimosso con successo");
        aggiornaLista();
    }
    catch (std::logic_error * e) {
        buildMessage("Attenzione", e->what());
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

