#include "utilities.h"


void assignWithXml(QXmlStreamReader & xmlInput, const std::string tag, std::string & string)
{
    xmlInput.readNextStartElement();
    if (xmlInput.name() != QString::fromStdString(tag))
        throw new std::runtime_error("errore durante il parsing del documento");
    string = (xmlInput.readElementText()).toStdString();
    std::cout<<string<<"***";
}

void showMessage(const QString & message)
{
    QMessageBox * m= new QMessageBox;
    m->setWindowTitle("Errore");
    m->setText(message);
    m->exec();
}
