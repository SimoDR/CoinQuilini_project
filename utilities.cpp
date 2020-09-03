#include "utilities.h"


void assignWithXml(QXmlStreamReader & xmlInput, const std::string tag, std::string & string)
{
    xmlInput.readNextStartElement();
    if (xmlInput.name() != QString::fromStdString(tag))
        throw new std::runtime_error("errore durante il parsing del documento");
    string = (xmlInput.readElementText()).toStdString();
}

void showMessage(const QString & message, const QString & details)
{
    QMessageBox * m= new QMessageBox;
    m->setModal(true);
    m->setWindowIcon(QIcon(":/resources/error.png"));
    m->setAttribute(Qt::WA_DeleteOnClose);
    m->setWindowTitle("Alert");
    m->setIcon(QMessageBox::Warning);
    m->setText(message);
    if(details!='\0')
            m->setDetailedText(details);
    QFile file(":/resources/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    file.close();
    m->setStyleSheet(styleSheet);
    m->show();
    QObject::connect(m, SIGNAL(buttonClicked(QAbstractButton *)), m, SLOT(close()));
}

void showSuccess(const QString & message, const QString & details)
{
    QMessageBox * m= new QMessageBox;
    m->setModal(true);
    m->setAttribute(Qt::WA_DeleteOnClose);
    m->setWindowTitle("Info");
    m->setWindowIcon(QIcon(":/resources/info.svg"));
    m->setIcon(QMessageBox::Information);
    m->setText(message);
    if(details!='\0')
            m->setDetailedText(details);
    QFile file(":/resources/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    file.close();
    m->setStyleSheet(styleSheet);
    m->show();
    QObject::connect(m, SIGNAL(buttonClicked(QAbstractButton *)), m, SLOT(close()));
}

int confirmationMessage(QWidget *parent, const QString & text,const QString & details)
{
    QMessageBox *conferma=new QMessageBox(parent);
    conferma->setWindowTitle("Conferma");
    conferma->setText(text);
    conferma->setWindowIcon(QIcon(":/resources/warning.svg"));
    if(details!='\0')
            conferma->setDetailedText(details);
    conferma->setStandardButtons(QMessageBox::Yes | QMessageBox::No );
    conferma->setDefaultButton(QMessageBox::Yes);
    QFile file(":/resources/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    file.close();
    conferma->setStyleSheet(styleSheet);
    return conferma->exec();
}
