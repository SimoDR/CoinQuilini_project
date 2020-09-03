#include "posponidialog.h"

PosponiDialog::PosponiDialog(unsigned int pos, QWidget *parent): QDialog(parent), _pos(pos),  _label(new QLabel("Di quanti giorni vuoi posporre l'incarico?")),_spin(new QSpinBox),_layout(new QGridLayout), _ok(new QPushButton("Conferma")), _no(new QPushButton("Annulla"))
{
    setWindowTitle("Posponi");
    _layout->addWidget(_label, 1,1);
    _layout->addWidget(_spin,1,2);
    _spin->setRange(1,50);
    _layout->addWidget(_ok,2,1);
    _layout->addWidget(_no,2,2);
    setLayout(_layout);
    connect(_ok, SIGNAL(clicked()), this, SLOT(close()));
    connect(_no, SIGNAL(clicked()), this, SLOT(close()));
    connect(_ok, SIGNAL(clicked()), this, SLOT(raccogliNumero()));

}

void PosponiDialog::raccogliNumero()
{
    unsigned int value= _spin->value();
    emit numero(_pos,value);
}
