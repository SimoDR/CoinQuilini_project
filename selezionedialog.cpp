#include "selezionedialog.h"

SelezioneDialog::SelezioneDialog(QWidget *parent): QDialog(parent), _combo(new QComboBox), _regular(new QCheckBox), _layout(new QVBoxLayout), _explanation(new QLabel), _conferma(new QHBoxLayout), _ok(new QPushButton), _no(new QPushButton)
{
    setWindowTitle("Tipo di incarico");
    setModal(true);
    setFixedSize(sizeHint());
    _explanation->setText("Seleziona la tipologia di incarico che vuoi creare");
    _layout->addWidget(_explanation);
    _combo->addItem("Bolletta");
    _combo->addItem("Spesa");
    _combo->addItem("Pulizia");
    _combo->addItem("Cucina");
    _combo->addItem("Spazzatura");
    _layout->addWidget(_combo);
    _regular->setText("Incarico regolare");
    _layout->addWidget(_regular);
    _ok->setText("Ok");
    _no->setText("Annulla");
    _conferma->addWidget(_ok);
    _conferma->addWidget(_no);
    connect(_no, SIGNAL(clicked()), this, SLOT(close()));
    connect(_ok, SIGNAL(clicked()), this, SLOT(inoltraDati()));
    connect(_ok, SIGNAL(clicked()), this, SLOT(close()));
    _layout->addLayout(_conferma);
    setLayout(_layout);
}

void SelezioneDialog::inoltraDati()
{
    emit datiSelezionati(_combo->currentText(), _regular->isChecked());
}
