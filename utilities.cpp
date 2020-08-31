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
    m->setIcon(QMessageBox::Warning);
    m->setText(message);

    QFile file(":/resources/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    m->setStyleSheet(styleSheet);

    m->exec();
}

void showSuccess(const QString & message)
{
    QMessageBox * m= new QMessageBox;
    m->setWindowTitle("Info");
    m->setIcon(QMessageBox::Information);
    m->setText(message);

    QFile file(":/resources/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    m->setStyleSheet(styleSheet);

    m->exec();
}

bool confirmationMessage(const QString & text)
{
    QMessageBox *conferma=new QMessageBox;
    conferma->setWindowTitle("Conferma");
    conferma->setText(text);
    conferma->setStandardButtons(QMessageBox::Yes | QMessageBox::No );
    conferma->setDefaultButton(QMessageBox::Yes);
    return conferma->exec();
}
