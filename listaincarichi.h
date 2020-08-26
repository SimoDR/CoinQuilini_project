#ifndef LISTAINCARICHI_H
#define LISTAINCARICHI_H

#include <QDialog>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <vector>
#include <string>
using std::vector;
using std::string;

class ListaIncarichi : public QDialog
{
    Q_OBJECT
private:
    QListWidget * _lista;
    QVBoxLayout *_mainLayout;
    void buildButtons();
    void buildLista(const vector<string> &, const vector<string> &);
public:
    ListaIncarichi(QString data,bool admin, vector<string> incarichi, vector<string> incaricati, QWidget *parent=nullptr);
};

#endif // LISTAINCARICHI_H
