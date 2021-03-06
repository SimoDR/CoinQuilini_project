#ifndef FORMINCARICO_H
#define FORMINCARICO_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QRadioButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>
#include <vector>
#include <string>
#include "utilities.h"
using std::vector;
using std::string;

class FormIncarico : public QDialog
{
    Q_OBJECT
private:
    QString _tipo;
    bool _regolare;
    QLabel *_nome;
    QLineEdit * _nomeEdit;
    QLabel * _data;
    QDateEdit * _dataEdit;
    QLabel * _inquilini;
    QComboBox * _combo;
    QPushButton *_ok;
    QPushButton *_no;
    QGridLayout * _layout;
    QSpinBox * _tempoStimato;
    QDoubleSpinBox * _importo;
    QSpinBox * _dataLimite;
    QSpinBox * _commensali;
    QSpinBox * _nStanze;
    QComboBox * _rifiuto;
    QSpinBox * _articoli;
    QHBoxLayout * _buttons;
    QVBoxLayout * _mainLayout;
    QSpinBox * _cadenza;
    QSpinBox * _nOccorrenze;
    void buildCombo(const vector<string> &);

public:
    FormIncarico(const QString & tipo, bool regolare, vector<string> inquilini, QWidget *parent=nullptr);
private slots:
    void raccogliDati();
    void controllaCampi();
signals:
    void inviaDati(const vector<string> &);
};

#endif // FORMINCARICO_H
