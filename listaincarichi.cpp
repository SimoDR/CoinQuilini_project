#include "listaincarichi.h"

void ListaIncarichi::buildButtons()
{
    QHBoxLayout *buttons=new QHBoxLayout;
    _rimuovi= new QPushButton("Rimuovi");
    _rimuovi->setDisabled(true);
    buttons->addWidget(_rimuovi);
    connect(_rimuovi,SIGNAL(clicked()), this, SLOT(raccogliDaEliminare()));
    _riassegna= new QPushButton("Riassegna");
    _riassegna->setDisabled(true);
    connect(_riassegna,SIGNAL(clicked()), this, SLOT(raccogliDaRiassegnare()));
    buttons->addWidget(_riassegna);
    _mainLayout->addLayout(buttons);
    connect(_lista, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(enableButtons()));
}

void ListaIncarichi::buildLista(const vector<std::string> & incarichi, const vector<std::string> & incaricati)
{
    int cont=0;
    _lista->clear();
    for(auto ci=incarichi.cbegin();ci!=incarichi.cend();ci++)
    {
        _lista->addItem(QString::fromStdString(incarichi[cont])+ "        " + QString::fromStdString(incaricati[cont]));
        cont++;
    }
    _mainLayout->addWidget(_lista);
    connect(_lista, SIGNAL(itemActivated(QListWidgetItem *)), this, SLOT(raccogliDatiIncarico()));
}

ListaIncarichi::ListaIncarichi(QString data, bool admin, vector<std::string> incarichi, vector<std::string> incaricati, QWidget *parent): QDialog(parent),_lista(new QListWidget), _mainLayout(new QVBoxLayout), _data(QDate::fromString(data,"d/M/yyyy"))
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Lista di incarichi del "+ data);
    setModal(true);
    setFixedSize(sizeHint());
    buildLista(incarichi, incaricati);
    if(admin && _data>=QDate::currentDate())
        buildButtons();
    setLayout(_mainLayout);
}

void ListaIncarichi::raccogliDatiIncarico()
{
    QDate giorno=_data;
    unsigned int pos=_lista->currentRow();
    emit datiIncarico(giorno,pos);
}

void ListaIncarichi::raccogliDaRiassegnare()
{
    QDate giorno=_data;
    unsigned int pos=_lista->currentRow();
    emit riassegnaIncarico(giorno,pos, this);
}

void ListaIncarichi::raccogliDaEliminare()
{
    int scelta = confirmationMessage(this, "Sei sicuro di voler eliminare l'incarico selezionato?", "La rimozione comporta la perdita dei dati dell'incarico");
    if (scelta==QMessageBox::Yes)
    {
    Data giorno((_data.toString("d/M/yyyy")).toStdString());
    unsigned int pos=_lista->currentRow();
    emit eliminaIncarico(giorno,pos);
    close();
    showSuccess("Incarico rimosso con successo");
    }
}

void ListaIncarichi::enableButtons()
{
    _riassegna->setDisabled(false);
    _rimuovi->setDisabled(false);
}
