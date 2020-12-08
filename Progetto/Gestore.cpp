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

void Gestore::aggiungiArticolo(const Articolo &article)
{
    listArticoli.push_back(new Articolo(article));
    //listArticoli.back()->setIdentificativo(nArticoli++);
}

void Gestore::aggiungiAutore(const Autore &author)
{
    listAutori.push_back(new Autore(author));
    listAutori.back()->setIdentificativo(nAutori++);
}

