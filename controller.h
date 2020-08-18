#ifndef CONTROLLER_H
#define CONTROLLER_H

#include<vector>
#include<string>
#include <QObject>
#include "mainwindow.h"
#include <QString>
#include <QMessageBox>
#include "data.h"
using std::vector;
using std::string;

class Controller : public QObject
{
    Q_OBJECT
private:
    Mainwindow* view;
public:
    explicit Controller(QObject *parent = nullptr);
    bool login(QString, QString);

signals:

public slots:
    void creaNuovoIncarico(vector<string>); //slot per la creazione di un nuovo incarico

};

#endif // CONTROLLER_H
