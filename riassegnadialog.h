#ifndef RIASSEGNADIALOG_H
#define RIASSEGNADIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include <vector>
#include <string>
#include <QPushButton>
#include "data.h"
using std::vector;
using std::string;

class RiassegnaDialog : public QDialog
{
    Q_OBJECT
private:
    Data _data;
    unsigned int _pos;
    QComboBox * _combo;
    QLabel *_label;
    QGridLayout * _layout;
    QPushButton * _ok;
    QPushButton * _no;
public:
    RiassegnaDialog(const Data &, unsigned int, const vector<string> &,  QWidget *parent =nullptr);
private slots:
    void raccogliInquilino();

signals:
    void inviaInquilino(const Data & , unsigned int, const string &);
};

#endif // RIASSEGNADIALOG_H
