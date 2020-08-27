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
}

ListaIncarichi::ListaIncarichi(QString data, bool admin, vector<std::string> incarichi, vector<std::string> incaricati, QWidget *parent): QDialog(parent), _mainLayout(new QVBoxLayout), _lista(new QListWidget)
{
    setWindowTitle("lista di incarichi del "+ data);
    setModal(true);
    buildLista(incarichi, incaricati);
    if(admin)
        buildButtons();
    setLayout(_mainLayout);
}
