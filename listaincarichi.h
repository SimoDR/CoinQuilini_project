#ifndef LISTAINCARICHI_H
#define LISTAINCARICHI_H

#include <QDialog>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <vector>
#include <string>
#include <QDate>
using std::vector;
using std::string;

class ListaIncarichi : public QDialog
{
    Q_OBJECT
private:
    QListWidget * _lista;
    QVBoxLayout *_mainLayout;
    QDate _data;
    void buildButtons();
    void buildLista(const vector<string> &, const vector<string> &);
public:
    ListaIncarichi(QString data,bool admin, vector<string> incarichi, vector<string> incaricati, QWidget *parent=nullptr);

private slots:
    void raccogliDatiIncarico();
signals:
    void datiIncarico(const QDate &, unsigned int pos);
};

#endif // LISTAINCARICHI_H
