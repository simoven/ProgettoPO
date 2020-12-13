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

void showErroreCorrelato()
{
    QMessageBox msg(QMessageBox::Warning, "Impossibile Modificare/Eliminare", "L'elemento è correlato ad un altro elemento");
    msg.exec();
}

void showErroreNotValid()
{
    //Significa che è già presente oppure alcuni campi sono vuoti
    QMessageBox msg(QMessageBox::Warning, "Impossibile aggiungere", "Elemento già presente oppure alcuni campi obbligatori sono vuoti");
    msg.exec();
}

bool Gestore::aggiungiArticolo(const Articolo &article, bool isNuovaAggiunta, int idx, bool increase)
{
    bool valid = true;
    for(Articolo* it : listArticoli)
        if((*it) == article)
            valid = false;

    //Alcuni campi non possono essere vuoti
    if(article.getTitolo() == "" || article.getNumPagine() == 0)
        valid = false;

    if(!valid)
    {
        showErroreNotValid();
        return false;
    }

    if(isNuovaAggiunta)
        listArticoli.push_back(new Articolo(article));
    else
    {
        //Controllo se l'articolo che sto modificando è nei correlati di qualcuno, se si aggiorno il puntatore
        //Perchè' sto creando un nuovo articolo con i dati modificati
        Articolo* nuovo = new Articolo(article);
        for(Articolo* ptr : listArticoli)
        {
            if(ptr != listArticoli [idx])
            {
                if(ptr->getCorrelati().contains(listArticoli [idx]))
                {
                    int indice = ptr->getCorrelati().indexOf(listArticoli [idx]);
                    ptr->rimuoviCorrelato(indice);
                    ptr->addCorrelato(nuovo);
                }
            }
        }

        delete listArticoli [idx];
        listArticoli.erase(listArticoli.begin() + idx);
        listArticoli.insert(idx, nuovo);
    }

    if(increase)
        listArticoli.back()->setIdentificativo(++nArticoli);

    return true;
}

bool Gestore::aggiungiAutore(const Autore &author, bool isNuovaAggiunta, int idx, bool increase)
{
    bool valid = true;
    for(Autore* it : listAutori)
        if((*it) == author)
            valid = false;

    if(author.getCognome() == "" || author.getNome() == "")
        valid = false;

    if(!valid)
    {
        showErroreNotValid();
        return false;
    }

    if(isNuovaAggiunta)
        listAutori.push_back(new Autore(author));
    else
    {
        if(rimuoviAutore(idx))
        {
            listAutori.insert(idx, new Autore(author));
            return true;
        }
        else return false;
    }

    if(increase)
        listAutori.back()->setIdentificativo(++nAutori);

    return true;
}

bool Gestore::aggiungiConferenza(const Conferenza &conference, bool isNuovaAggiunta, int idx)
{
    bool valid = true;
    for(Conferenza* it : listConferenze)
        if(*it == conference)
            valid = false;

    if(conference.getNome() == "" || conference.getLuogo() == "")
        valid = false;

    if(!valid)
    {
        showErroreNotValid();
        return false;
    }

    if(isNuovaAggiunta)
        listConferenze.push_back(new Conferenza(conference));
    else
    {
        if(rimuoviConferenza(idx))
        {
            listConferenze.insert(idx, new Conferenza(conference));
            return true;
        }
        else return false;
    }

    return true;
}

bool Gestore::aggiungiRivista(const Rivista &paper, bool isNuovaAggiunta, int idx)
{
    bool valid = true;
    for(Rivista* it : listRiviste)
        if(*it == paper)
            valid = false;

    if(paper.getNome() == "")
        valid = false;

    if(!valid)
    {
        showErroreNotValid();
        return false;
    }

    if(isNuovaAggiunta)
        listRiviste.push_back(new Rivista(paper));
    else
    {
        if(rimuoviRivista(idx))
        {
            listRiviste.insert(idx, new Rivista(paper));
            return true;
        }
        else return false;
    }

    return true;
}

bool Gestore::rimuoviArticolo(int idx)
{
    bool isCorrelato = false;
    for(Articolo* ptr : listArticoli)
        if(listArticoli [idx] != ptr)
            if(ptr->getCorrelati().contains(listArticoli [idx]))
                isCorrelato = true;

    if(!isCorrelato)
    {
        delete listArticoli.at(idx);
        listArticoli.erase(listArticoli.begin() + idx);
        return true;
    }

    showErroreCorrelato();
    return false;
}

bool Gestore::rimuoviAutore(int idx)
{
    //Controllo che questo autore non sia nella lista correlati di qualche articolo
    bool isCorrelato = false;
    for(Articolo* ptr : listArticoli)
        if(ptr->getAutori().contains(listAutori [idx]))
                isCorrelato = true;

    if(!isCorrelato)
    {
        delete listAutori.at(idx);
        listAutori.erase(listAutori.begin() + idx);
        return true;
    }

    showErroreCorrelato();
    return false;
}

bool Gestore::rimuoviConferenza(int idx)
{
    bool isCorrelato = false;
    for(Articolo* ptr : listArticoli)
        if(ptr->getEditorePubblicato() == listConferenze [idx])
                isCorrelato = true;

    if(!isCorrelato)
    {
        delete listConferenze.at(idx);
        listConferenze.erase(listConferenze.begin() + idx);
        return true;
    }

    showErroreCorrelato();
    return false;
}

bool Gestore::rimuoviRivista(int idx)
{
    bool isCorrelato = false;
    for(Articolo* ptr : listArticoli)
        if(ptr->getEditorePubblicato() == listRiviste [idx])
                isCorrelato = true;

    if(!isCorrelato)
    {
        delete listRiviste.at(idx);
        listRiviste.erase(listRiviste.begin() + idx);
        return true;
    }

    showErroreCorrelato();
    return false;
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












