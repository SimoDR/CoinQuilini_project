#ifndef UTILITIES_H
#define UTILITIES_H

#include <QXmlStreamReader>
#include <string>
#include <iostream>
#include <QMessageBox>
#include <stdexcept>
#include <QFile>
#include <QIcon>

void assignWithXml(QXmlStreamReader&, const std::string, std::string&);
void showMessage(const QString &, const QString& = "\0");
void showSuccess (const QString &, const QString& = "\0");
int confirmationMessage(QWidget *, const QString &,const QString& = "\0");


#endif // UTILITIES_H
