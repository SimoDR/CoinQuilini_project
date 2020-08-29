#ifndef CREAMODIFICAINQUILINO_H
#define CREAMODIFICAINQUILINO_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QString>
#include "utilities.h"

class CreaModificaInquilino : public QDialog
{
    Q_OBJECT
public:
    CreaModificaInquilino(QWidget *parent = nullptr, const QString & user ="", const QString & pw ="");
private:
    QGridLayout * _layout;
    QLabel *_userlabel;
    QLabel *_pwlabel;
    QLineEdit *_useredit;
    QLineEdit *_pwedit;
    QPushButton * _yes;
    QPushButton* _no;

    void buildFields(const QString &user, const QString &pw);
    void buildButtons();

private slots:
    void checkDati();
    void raccogliDati();    //per raccogliere i dati dell'editline
signals:
    void invia(const QString&, const QString &);  //invia i dati al pannello admin

};

#endif // CREAMODIFICAINQUILINO_H
