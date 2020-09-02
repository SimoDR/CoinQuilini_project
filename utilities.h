#ifndef UTILITIES_H
#define UTILITIES_H

#include <QXmlStreamReader>
#include <string>
#include <iostream>
#include <QMessageBox>
#include <stdexcept>
#include "QFile"

void assignWithXml(QXmlStreamReader&, const std::string, std::string&);
void showMessage(const QString &);
void showSuccess (const QString &);
int confirmationMessage(QWidget *, const QString &,const QString& = "\0");


#endif // UTILITIES_H
