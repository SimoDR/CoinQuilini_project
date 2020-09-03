#include "riassegnadialog.h"

RiassegnaDialog::RiassegnaDialog(const Data & data, unsigned int pos,const vector<string> & inquilini, QWidget * parent): QDialog(parent),_data(data), _pos(pos), _combo(new QComboBox),_label(new QLabel("Seleziona l'inquilino a cui riassegnare l'incarico:")), _layout(new QGridLayout),  _ok(new QPushButton("Conferma")),_no(new QPushButton("Annulla"))
{
    setWindowTitle("Riassegnazione dell'incarico");
    setModal(true);
    setFixedSize(sizeHint());
    _layout->addWidget(_label,1,1);
    for(auto ci= inquilini.cbegin(); ci!=inquilini.cend(); ci++)
        _combo->addItem(QString::fromStdString(*ci));
    _layout->addWidget(_combo,1,2);
    _layout->addWidget(_ok,2,1);
    _layout->addWidget(_no,2,2);
    setLayout(_layout);
    connect(_ok, SIGNAL(clicked()), this, SLOT(raccogliInquilino()));
    connect(_ok, SIGNAL(clicked()), this, SLOT(close()));
    connect(_no, SIGNAL(clicked()), this, SLOT(close()));
}

void RiassegnaDialog::raccogliInquilino()
{
    string inquilino=(_combo->currentText()).toStdString();
    emit inviaInquilino(_data, _pos, inquilino);
}
