#include "listainquilini.h"

ListaInquilini::ListaInquilini()
{
    importXml();
    creaInserisci("ADMIN", "admin", "admin"); //creainserisci controlla se l'inquilino già esiste
}

ListaInquilini::~ListaInquilini()
{
    exportXml();
}

void ListaInquilini::aggiungi(Inquilino * nuovo)
{
    _listaInquilini.insertBack(nuovo);
}

void ListaInquilini::rimuovi(unsigned int pos)
{
    unsigned int cont=0;
    dList<Inquilino*>::iterator i;
    for(i=_listaInquilini.begin();i!=_listaInquilini.end(); ++i) {
        if (cont==pos)
        {
            _listaInquilini.remove(i);
            return;
        }

        cont++;
    }
}

Inquilino *ListaInquilini::getInquilino(unsigned int pos) const
{
    unsigned int cont=0;
    dList<Inquilino*>::iterator i;
    for(i=_listaInquilini.begin();i!=_listaInquilini.end(); ++i) {
        if (cont==pos)
            return *i;
        cont++;
    }
    return *i;   //se pos è out of bound ritorna iteratore past the end
}

Inquilino *ListaInquilini::getInquilino(const std::string & user) const
{
    dList<Inquilino*>::iterator i;
    for(i=_listaInquilini.begin();i!=_listaInquilini.end(); ++i) {
        if ((*i)->getNome()==user)
            return *i;
    }
    return *i;   //se pos è out of bound ritorna iteratore past the end
}
bool ListaInquilini::checkCredenziali(const std::string & user, const std::string & pw) const
{
    dList<Inquilino*>::iterator i;
    for(i=_listaInquilini.begin();i!=_listaInquilini.end(); ++i) {
        if ((**i).isLogged(user, pw))
            return true;
    }
    return false;
}

bool ListaInquilini::checkPresenza(const std::string &user) const
{

    for(auto i=_listaInquilini.begin();i!=_listaInquilini.end(); ++i) {
        if ((**i).getNome()==user)
            return true;
    }
    return false;
}

void ListaInquilini::creaInserisci(const std::string & tipo,  const std::string &user, const std::string &pw)
{
    if(checkPresenza(user))
        return;
    else {
        Inquilino *p=nullptr;
        if (tipo=="ADMIN")
            p=new Admin(user, pw);
        else if (tipo=="INQUILINO")
            p=new Inquilino(user, pw);
        aggiungi(p);
    }
}

vector<std::string> ListaInquilini::inquilini() const
{
    vector<string> elenco;
    for (auto i=_listaInquilini.begin();i!=_listaInquilini.end();++i)
        if((*i)!=nullptr)
            elenco.push_back((*i)->getNome());
    return elenco;
}

vector<std::string> ListaInquilini::getCredenziali(unsigned int pos) const
{
    Inquilino *i=getInquilino(pos);
    vector<string> inquilino;
    inquilino.push_back(i->getNome());
    inquilino.push_back(i->_password);
    return inquilino;
}

void ListaInquilini::modifica(const std::string & newuser, const std::string & newpw, unsigned int pos)
{
    Inquilino* i= getInquilino(pos);
    i->_user=newuser;
    i->_password=newpw;
}

void ListaInquilini::checkAdmin(unsigned int pos) const
{
    Inquilino* i= getInquilino(pos);
    if(i->isAdmin()==1)
    {
        throw new std::logic_error("Non è possibile apportare modifiche all'utente admin");
    }
}

unsigned short int ListaInquilini::isAdmin(const std::string & user) const
{
    Inquilino* i= getInquilino(user);
    return i->isAdmin();

}

void ListaInquilini::importXml()
{
    QFile file("listainquilini.xml");
    try {
        if (file.open(QFile::ReadOnly | QFile::Text))
        {
            QXmlStreamReader xmlInput(&file);
            if (xmlInput.readNextStartElement())
            {
                if (xmlInput.name() == "INQUILINI")
                {
                    std::string user, pw;
                    while(xmlInput.readNextStartElement()) {
                        std::string tipo=((xmlInput.name().toString()).toStdString());
                        assignWithXml(xmlInput, "nome", user);
                        assignWithXml(xmlInput, "password", pw);
                        creaInserisci(tipo, user, pw);
                        xmlInput.skipCurrentElement(); //per uscire dallo "scope"(?)
                    }
                }
                else
                    throw new std::runtime_error("Errore nel parsing del documento");
            }
            else
                throw new std::runtime_error("Errore nella lettura del documento");

            file.close();
        }
    }
    catch(std::runtime_error * e)
    {
        creaInserisci("ADMIN", "admin", "admin");
        showMessage(QString::fromStdString(e->what()));
    }

}

void ListaInquilini::exportXml() const
{
    QFile file("listainquilini.xml");
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlOutput(&file);
    xmlOutput.setAutoFormatting(true);
    xmlOutput.writeStartDocument();
    xmlOutput.writeStartElement("INQUILINI");
    for(auto ci = _listaInquilini.cbegin(); ci != _listaInquilini.cend(); ++ci)
        (*ci)->exportXml(xmlOutput);
    xmlOutput.writeEndElement();
    xmlOutput.writeEndDocument();
    file.close();
}
