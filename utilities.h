#ifndef UTILITIES_H
#define UTILITIES_H

#include <QXmlStreamReader>
#include <string>
#include <iostream>
#include <QMessageBox>
#include <stdexcept>
#include "QFile"

//class error message

void assignWithXml(QXmlStreamReader&, const std::string, std::string&);
void showMessage(const QString &);

#endif // UTILITIES_H
