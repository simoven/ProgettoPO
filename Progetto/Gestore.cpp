#include "Gestore.h"

Gestore::Gestore() : nAutori(0), nArticoli(0) {}

void Gestore::svuota()
{
    for(auto it = listArticoli.begin(); it != listArticoli.end(); it++)
        delete *it;

    for(auto it = listAutori.begin(); it != listAutori.end(); it++)
        delete *it;

    for(auto it = listConferenze.begin(); it != listConferenze.end(); it++)
        delete *it;

    for(auto it = listRiviste.begin(); it != listRiviste.end(); it++)
        delete *it;

    listArticoli.clear();
    listAutori.clear();
    listConferenze.clear();
    listRiviste.clear();
}

Gestore::~Gestore()
{
    qDebug() << "Distruggo";
    svuota();
}

void Gestore::copia(const Gestore& G)
{
    for(auto it = G.listArticoli.begin(); it != G.listArticoli.end(); it++)
        listArticoli.push_back(new Articolo(**it));

    for(auto it = G.listAutori.begin(); it != G.listAutori.end(); it++)
        listAutori.push_back(new Autore(**it));

    for(auto it = G.listConferenze.begin(); it != G.listConferenze.end(); it++)
        listConferenze.push_back(new Conferenza(**it));

    for(auto it = G.listRiviste.begin(); it != G.listRiviste.end(); it++)
        listRiviste.push_back(new Rivista(**it));

    nAutori = G.nAutori;
    nArticoli = G.nArticoli;
}

Gestore::Gestore(const Gestore& G)
{
    copia(G);
}

Gestore& Gestore::operator=(const Gestore &G)
{
    if(this != &G)
    {
        svuota();
        copia(G);
    }

    return *this;
}

bool Gestore::aggiungiArticolo(const Articolo &article, bool increase)
{
    for(Articolo* it : listArticoli)
        if((*it) == article)
            return false;

    //Alcuni campi non possono essere vuoti
    if(article.getTitolo() == "" || article.getNumPagine() == 0)
        return false;

    listArticoli.push_back(new Articolo(article));

    if(increase)
        listArticoli.back()->setIdentificativo(++nArticoli);

    return true;
}

bool Gestore::aggiungiAutore(const Autore &author, bool increase)
{
    for(Autore* it : listAutori)
        if((*it) == author)
            return false;

    if(author.getCognome() == "" || author.getNome() == "")
        return false;

    listAutori.push_back(new Autore(author));

    if(increase)
        listAutori.back()->setIdentificativo(++nAutori);

    return true;
}

bool Gestore::aggiungiConferenza(const Conferenza &conference)
{
    for(Conferenza* it : listConferenze)
        if(*it == conference)
            return false;
    if(conference.getNome() == "" || conference.getLuogo() == "")
        return false;

    listConferenze.push_back(new Conferenza(conference));
    return true;
}

bool Gestore::aggiungiRivista(const Rivista &paper)
{
    for(Rivista* it : listRiviste)
        if(*it == paper)
            return false;

    if(paper.getNome() == "")
        return false;

    listRiviste.push_back(new Rivista(paper));
    return true;
}

void showMsgErrore()
{
    QMessageBox msg(QMessageBox::Warning, "Impossibile eliminare", "L'elemento è correlato ad un altro elemento");
    msg.exec();
}

bool Gestore::rimuoviArticolo(int idx)
{
    if(!listArticoli.at(idx)->getIsCorrelato())
    {
        delete listArticoli.at(idx);
        listArticoli.erase(listArticoli.begin() + idx);
        return true;
    }

    showMsgErrore();
    return false;
}

bool Gestore::rimuoviAutore(int idx)
{
    //Controllo che questo autore non sia nella lista correlati di qualcuno
    if(!listAutori.at(idx)->getIsCorrelato())
    {
        delete listAutori.at(idx);
        listAutori.erase(listAutori.begin() + idx);
        return true;
    }

    showMsgErrore();
    return false;
}

void Gestore::rimuoviConferenza(int idx)
{
    delete listConferenze.at(idx);
    listConferenze.erase(listConferenze.begin() + idx);
}

void Gestore::rimuoviRivista(int idx)
{
    delete listRiviste.at(idx);
    listRiviste.erase(listRiviste.begin() + idx);
}

const QList <Articolo*>& Gestore::getArticoli() const
{
    return listArticoli;
}

const QList <Autore*>& Gestore::getAutori() const
{
    return listAutori;
}

const QList <Conferenza*>& Gestore::getConferenze() const
{
    return listConferenze;
}

const QList <Rivista*>& Gestore::getRiviste() const
{
    return listRiviste;
}












