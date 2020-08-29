#include "formincarico.h"




FormIncarico::FormIncarico(const QString &tipo, bool regolare, vector<string> inquilini, QWidget *parent): QDialog(parent),_tipo(tipo),_regolare(regolare), _nome(new QLabel("Nome:")), _nomeEdit(new QLineEdit),_data(new QLabel("Data:")), _dataEdit(new QDateEdit), _inquilini(new QLabel("Incaricato:")),_combo(new QComboBox), _ok(new QPushButton("Ok")), _no(new QPushButton("Annulla")), _layout(new QGridLayout), _buttons(new QHBoxLayout), _mainLayout(new QVBoxLayout)
{
    _tipo=tipo;
    setWindowTitle("Creazione incarico "+ tipo);
    setModal(true);
    _layout->addWidget(_nome,1,1);
    _layout->addWidget(_nomeEdit,1,2);
    _layout->addWidget(_data,2,1);
    _dataEdit->setMinimumDate(QDate::currentDate());
    _layout->addWidget(_dataEdit,2,2);
        _layout->addWidget(_inquilini,3,1);
    buildCombo(inquilini);
    _layout->addWidget(_combo,3,2);
    _buttons->addWidget(_ok);
    _buttons->addWidget(_no);


    if(tipo=="Bolletta")
    {
        QLabel *importo= new QLabel("Importo:");
        _layout->addWidget(importo,4,1);
        _importo=new QLineEdit;
        _importo->setInputMask("d9.99");
        _layout->addWidget(_importo,4,2);
        QLabel *dataLimite= new QLabel("Data limite:");
        _layout->addWidget(dataLimite,5,1);
        _dataLimite=new QSpinBox;
        _dataLimite->setRange(1,30);
        _layout->addWidget(_dataLimite,5,2);

    }
    if (tipo=="Spesa")
    {
        QLabel *importo= new QLabel("Importo:");
        _layout->addWidget(importo,4,1);
        _importo=new QLineEdit;
        _importo->setInputMask("d9.99");
        _layout->addWidget(_importo,4,2);
        QLabel* tempo= new QLabel("Tempo stimato (in minuti):");
        _layout->addWidget(tempo,5,1);
        _tempoStimato=new QSpinBox;
        _tempoStimato->setRange(1,180);
        _layout->addWidget(_tempoStimato,5,2);
        QLabel* articoli= new QLabel("Numero di articoli da acquistare:");
        _layout->addWidget(articoli,6,1);
        _articoli=new QSpinBox;
        _articoli->setRange(1,100);
        _layout->addWidget(_articoli,6,2);

    }
    if (tipo=="Pulizia")
    {
        QLabel* tempo= new QLabel("Tempo stimato (in minuti):");
        _layout->addWidget(tempo,4,1);
        _tempoStimato=new QSpinBox;
        _tempoStimato->setRange(1,180);
        _layout->addWidget(_tempoStimato,4,2);
        QLabel* stanze= new QLabel("Numero di stanze da pulire:");
        _layout->addWidget(stanze,5,1);
        _nStanze=new QSpinBox;
        _nStanze->setRange(1,20);
        _layout->addWidget(_nStanze,5,2);

    }
    if (tipo=="Cucina")
    {
        QLabel* tempo= new QLabel("Tempo stimato (in minuti):");
        _layout->addWidget(tempo,4,1);
        _tempoStimato=new QSpinBox;
        _tempoStimato->setRange(1,180);
        _layout->addWidget(_tempoStimato,4,2);
        QLabel* persone= new QLabel("Numero di persone partecipanti:");
        _layout->addWidget(persone,5,1);
        _commensali=new QSpinBox;
        _commensali->setRange(1,20);
        _layout->addWidget(_commensali,5,2);

    }
    if (tipo=="Spazzatura")
    {
        QLabel* tempo= new QLabel("Tempo stimato (in minuti):");
        _layout->addWidget(tempo,4,1);
        _tempoStimato=new QSpinBox;
        _tempoStimato->setRange(1,180);
        _layout->addWidget(_tempoStimato,4,2);
        QLabel* rifiuto= new QLabel("Tipo di rifiuto:");
        _layout->addWidget(rifiuto,5,1);
        _rifiuto=new QComboBox;
        _rifiuto->addItems(QStringList() <<"Secco" << "Umido" << "Plastica"<< "Carta"<< "Vetro");
        _layout->addWidget(_rifiuto,5,2);

    }
    _mainLayout->addLayout(_layout);

    if(regolare)
    {
        QGridLayout *regolare=new QGridLayout;
        QLabel* cadenza= new QLabel("Cadenza (ogni quanti giorni):");
        regolare->addWidget(cadenza,1,1);
        _cadenza=new QSpinBox;
        _cadenza->setRange(1,365);
        regolare->addWidget(_cadenza,1,2);
        QLabel* occorrenze= new QLabel("Numero di occorrenze:");
        regolare->addWidget(occorrenze,2,1);
        _nOccorrenze=new QSpinBox;
        _nOccorrenze->setRange(2,100);
        regolare->addWidget(_nOccorrenze,2,2);
        _mainLayout->addLayout(regolare);
    }

    _mainLayout->addLayout(_buttons);
    setLayout(_mainLayout);

    connect(_ok, SIGNAL(clicked()), this, SLOT(controllaCampi()));
    connect(_no, SIGNAL(clicked()), this, SLOT(close()));


}

void FormIncarico::raccogliDati()
{
    vector<string> parametri(14,"\0");
    parametri[0]=(_nomeEdit->text()).toStdString();
    parametri[1]=_tipo.toStdString();
    if(_combo->currentText()!="Assegna in automatico")
        parametri[2]=(_combo->currentText()).toStdString();
    if(_regolare)
        parametri[3]=std::to_string(_cadenza->value());
    if(_tipo!="Bolletta")
        parametri[4]=std::to_string(_tempoStimato->value());
    if(_tipo=="Pulizia")
        parametri[5]=std::to_string(_nStanze->value());
    if(_tipo=="Cucina")
        parametri[6]=std::to_string(_commensali->value());
    if(_tipo=="Spesa")
        parametri[7]=std::to_string(_articoli->value());
    if(_tipo=="Spesa" || _tipo=="Bolletta")
        parametri[8]=(_importo->text()).toStdString();
    if(_tipo=="Bolletta")
        parametri[9]=std::to_string(_dataLimite->value());
    parametri[10]=((_dataEdit->date()).toString("d/M/yyyy")).toStdString();
    if(_regolare)
        parametri[11]=std::to_string(_nOccorrenze->value());
    if(_tipo=="Spazzatura")
        parametri[13]=(_rifiuto->currentText()).toStdString();
    emit inviaDati(parametri);
}

void FormIncarico::controllaCampi()
{
    bool errore=false;
    if(_tipo=="Bolletta")
    {
        if(_nomeEdit->text().isEmpty() || _importo->text().toStdString()==".")
            errore=true;
    }
    if (_tipo=="Spesa")
    {
        if(_nomeEdit->text().isEmpty() || _importo->text().toStdString()==".")
            errore=true;
    }
    if (_tipo=="Pulizia")
    {
        if(_nomeEdit->text().isEmpty())
            errore=true;
    }
    if (_tipo=="Cucina")
    {
        if(_nomeEdit->text().isEmpty())
            errore=true;

    }
    if (_tipo=="Spazzatura")
    {
        if(_nomeEdit->text().isEmpty())
            errore=true;
    }

    if(!errore)
    {
        raccogliDati();
        close();
    }
    else
    {
        showMessage("Attenzione! Tutti i campi devono essere valorizzati");
        disconnect(_ok, SIGNAL(clicked()), this, SLOT(controllaCampi()));
        connect(_ok, SIGNAL(clicked()), this, SLOT(controllaCampi()));
        connect(_no, SIGNAL(clicked()), this, SLOT(close()));
    }

}
void FormIncarico::buildCombo(const vector<std::string> & inquilini)
{
    _combo->addItem("Assegna in automatico");
    for(auto ci= inquilini.cbegin(); ci!=inquilini.cend(); ci++)
        _combo->addItem(QString::fromStdString(*ci));
}
