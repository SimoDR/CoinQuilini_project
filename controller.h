#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "mainwindow.h"
#include <QString>
#include <QMessageBox>

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

};

#endif // CONTROLLER_H
