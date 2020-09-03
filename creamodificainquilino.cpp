#include "creamodificainquilino.h"

CreaModificaInquilino::CreaModificaInquilino(QWidget *parent, const QString & user, const QString & pw) : QDialog(parent), _layout(new QGridLayout), _userlabel(new QLabel), _pwlabel(new QLabel), _useredit(new QLineEdit), _pwedit(new QLineEdit), _yes(new QPushButton), _no(new QPushButton)
{
    setWindowModality(Qt::WindowModal);
    buildFields(user, pw);
    buildButtons();
    setLayout(_layout);
}

void CreaModificaInquilino::buildFields(const QString& user, const QString& pw)
{
    _userlabel->setText("Username:");
    _pwlabel->setText("Password:");
    _useredit->setText(user);
    _pwedit->setText(pw);
    _layout->addWidget(_userlabel,1,1);
    _layout->addWidget(_pwlabel,2,1);
    _layout->addWidget(_useredit,1,2);
    _layout->addWidget(_pwedit,2,2);
}

void CreaModificaInquilino::buildButtons()
{
    _yes->setText("Applica le modifiche");
    _layout->addWidget(_yes,3,1,1,2);
    _no->setText("Indietro");
    _layout->addWidget(_no,4,1,1,2);
    connect(_no, SIGNAL(clicked()), this, SLOT(close()));
    connect(_yes, SIGNAL(clicked()), this, SLOT(checkDati()));
}

void CreaModificaInquilino::checkDati()
{
    bool errore=false;
    if(_useredit->text().isEmpty() || _pwedit->text().isEmpty())
        errore=true;
    if(!errore)
    {
        raccogliDati();
        close();
        showSuccess("Operazione effettuata con successo");
    }
    else
        showMessage("Attenzione! I campi user e password non possono essere vuoti");
}

void CreaModificaInquilino::raccogliDati()
{
    const QString & utente=_useredit->text(),pw= _pwedit->text();
    emit  invia(utente, pw);
}
