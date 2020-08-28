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
    m->setWindowTitle("Alert");
    m->setText(message);

    QFile file(":/resources/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    m->setStyleSheet(styleSheet);

    m->exec();
}
