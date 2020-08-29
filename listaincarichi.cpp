#include "listaincarichi.h"

void ListaIncarichi::buildButtons()
{
    QHBoxLayout *buttons=new QHBoxLayout;
    QPushButton *rimuovi= new QPushButton("Rimuovi");
    buttons->addWidget(rimuovi);
    QPushButton *riassegna= new QPushButton("Riassegna");
    buttons->addWidget(riassegna);
    _mainLayout->addLayout(buttons);


}

void ListaIncarichi::buildLista(const vector<std::string> & incarichi, const vector<std::string> & incaricati)
{
    int cont=0;
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
    setWindowTitle("lista di incarichi del "+ data);
    setModal(true);
    buildLista(incarichi, incaricati);
    if(admin)
        buildButtons();
    setLayout(_mainLayout);
}

void ListaIncarichi::raccogliDatiIncarico()
{
    QDate giorno=_data;
    unsigned int pos=_lista->currentRow();
    emit datiIncarico(giorno,pos);
}
