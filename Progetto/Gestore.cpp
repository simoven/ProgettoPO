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
    if(article.getTitolo() == "" || article.getNumPagine() == 0 || article.getKeyword().size() == 0)
        valid = false;

    if(!isNuovaAggiunta)
    {
        if(article.getAutori().size() == 0 || article.getEditorePubblicato() == nullptr)
            valid = false;
    }

    if(!valid)
    {
        showErroreNotValid();
        return false;
    }

    if(isNuovaAggiunta)
        listArticoli.push_back(new Articolo(article));
    else
    {
        //Controllo se l'articolo che sto modificando è nei correlati di qualche articolo, se si aggiorno il puntatore
        //Perchè' sto creando un nuovo articolo con i dati modificati, quindi il puntatore sarà diverso
        Articolo* nuovo = new Articolo(article);
        for(Articolo* ptr : listArticoli)
        {
            if(ptr != listArticoli [idx])
            {
                if(ptr->getCorrelati().contains(listArticoli [idx]))
                {
                    int indice = ptr->getCorrelati().indexOf(listArticoli [idx]);
                    ptr->rimuoviCorrelato(indice);
                    ptr->addCorrelato(nuovo, indice);
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

const QList <Articolo*> Gestore::getArticoliPerAutore(int idx) const
{
    Autore* ptr = listAutori [idx];
    QList <Articolo*> nuovalistArticoli;
    for(int i = 0; i < listArticoli.size(); i++)
    {
        if(listArticoli [i]->getAutori().contains(ptr))
            nuovalistArticoli.push_back(listArticoli [i]);
    }

    return nuovalistArticoli;
}

bool compara(Articolo* item1, Articolo* item2)
{
    //Se l'articolo non è stato pubblicato per una rivista/conferenza, imposto l'anno di default a 2020
    int anno1 = 0, anno2 = 0;

    anno1 = item1->getEditorePubblicato()->getData().year();
    anno2 = item2->getEditorePubblicato()->getData().year();

    if(anno1 < anno2)
        return true;

    if(anno2 > anno1)
        return false;

    if(item1->getPrezzo() > item2->getPrezzo())
        return true;

    if(item1->getPrezzo() < item2->getPrezzo())
        return false;

    if(item1->getKeyword() [0] < item2->getKeyword() [0])
        return true;

    return false;
}

const QList <Articolo*> Gestore::getArticoliPerAutoreSorted(int idx) const
{
    QList <Articolo*> nuovalist = getArticoliPerAutore(idx);
    std::stable_sort(nuovalist.begin(), nuovalist.end(), compara);
    return nuovalist;
}

const QList <Base*> Gestore::getRivisteNonPubblicateDaAutore(int idx) const
{
    auto listArticoliPerAutore = getArticoliPerAutore(idx);
    //Prendo inizialmente tutte le riviste e poi rimuovo quelle per cui l'autore non ha pubblicato
    QList <Base*> listTutteRiviste;
    for(Base* ptr : listRiviste)
        listTutteRiviste.push_back(ptr);

    for(Articolo* ptr : listArticoliPerAutore)
        if(listTutteRiviste.contains(ptr->getEditorePubblicato()))
            listTutteRiviste.erase(listTutteRiviste.begin() + listTutteRiviste.indexOf(ptr->getEditorePubblicato()));

    return listTutteRiviste;
}

const QList <Articolo*> Gestore::getArticoliPerRivista(int idx) const
{
    Base* ptrRivista = listRiviste [idx];
    QList <Articolo*> listArticoliDiRivista;
    for(Articolo* ptr : listArticoli)
        if(ptr->getEditorePubblicato() == ptrRivista)
            listArticoliDiRivista.push_back(ptr);

    return listArticoliDiRivista;
}

bool compara2(Articolo* art1, Articolo* art2)
{
    if(art1->getPrezzo() < art2->getPrezzo())
        return true;

    return false;
}

const QList <Articolo*> Gestore::getArticoliPerRivistaSorted(int idx) const
{
    auto listArticoliDiRivista = getArticoliPerRivista(idx);
    std::stable_sort(listArticoliDiRivista.begin(), listArticoliDiRivista.end(), compara2);
    return listArticoliDiRivista;
}












