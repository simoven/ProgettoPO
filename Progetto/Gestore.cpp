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

void showErroreNotValid(bool mostra)
{
    //Significa che è già presente oppure alcuni campi sono vuoti
    QMessageBox msg(QMessageBox::Warning, "Impossibile aggiungere", "Elemento già presente oppure alcuni campi obbligatori sono vuoti");

    if(mostra)
        msg.exec();
}

bool Gestore::aggiungiArticolo(const Articolo &article, bool mostraErrore, bool isNuovaAggiunta, int idx, bool increase)
{
    bool valid = true;
    for(Articolo* it : listArticoli)
        if((*it) == article)
            valid = false;

    //Alcuni campi non possono essere vuoti
    if(article.getTitolo() == "" || article.getNumPagine() == 0 || article.getKeyword().size() == 0)
        valid = false;

    if(article.getKeyword().size() == 1 && article.getKeyword() [0].isEmpty())
        valid = false;

    if(!isNuovaAggiunta)
    {
        if(article.getAutori().size() == 0 || article.getEditorePubblicato() == nullptr)
            valid = false;
    }

    if(!valid)
    {
        showErroreNotValid(mostraErrore);
        return false;
    }

    if(isNuovaAggiunta)
        listArticoli.push_back(new Articolo(article));
    else
    {
        //Controllo se l'articolo che sto modificando è nei correlati di qualche altro articolo, se si aggiorno il puntatore
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

bool Gestore::aggiungiAutore(const Autore &author, bool mostraErrore, bool isNuovaAggiunta, int idx, bool increase)
{
    bool valid = true;
    for(Autore* it : listAutori)
        if((*it) == author)
            valid = false;

    if(author.getCognome() == "" || author.getNome() == "")
        valid = false;

    if(!valid)
    {
        showErroreNotValid(mostraErrore);
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

bool Gestore::aggiungiConferenza(const Conferenza &conference, bool mostraErrore, bool isNuovaAggiunta, int idx)
{
    bool valid = true;
    for(Conferenza* it : listConferenze)
        if(*it == conference)
            valid = false;

    if(conference.getNome() == "" || conference.getLuogo() == "" || conference.getOrganizzatori().isEmpty())
        valid = false;

    if(!valid)
    {
        showErroreNotValid(mostraErrore);
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

bool Gestore::aggiungiRivista(const Rivista &paper, bool mostraErrore, bool isNuovaAggiunta, int idx)
{
    bool valid = true;
    for(Rivista* it : listRiviste)
        if(*it == paper)
            valid = false;

    if(paper.getNome() == "")
        valid = false;

    if(!valid)
    {
        showErroreNotValid(mostraErrore);
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
    //Controllo che l'articolo non sia correlato ad un altro articolo
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
    //Prendo tutti gli articoli pubblicati da un autore
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
    //Prendo inizialmente tutte le riviste e poi rimuovo quelle per cui l'autore ha pubblicato qualcosa
    QList <Base*> listTutteRiviste;
    for(Base* ptr : listRiviste)
        listTutteRiviste.push_back(ptr);

    for(Articolo* ptr : listArticoliPerAutore)
        if(listTutteRiviste.contains(ptr->getEditorePubblicato()))
            listTutteRiviste.erase(listTutteRiviste.begin() + listTutteRiviste.indexOf(ptr->getEditorePubblicato()));

    return listTutteRiviste;
}

const QList <Articolo*> Gestore::getArticoliPerRivistaOConferenza(int idx, int tipo) const
{
    //Prendi tutti gli articoli pubblicati per una rivista (indice 0) o Conferenza(indice 1)
    Base* ptrBase;
    if(tipo == 0)
        ptrBase = listRiviste [idx];
    else
        ptrBase = listConferenze [idx];

    QList <Articolo*> listArticoliDiBase;
    for(Articolo* ptr : listArticoli)
        if(ptr->getEditorePubblicato() == ptrBase)
            listArticoliDiBase.push_back(ptr);

    return listArticoliDiBase;
}

bool compara2(Articolo* art1, Articolo* art2)
{
    if(art1->getPrezzo() < art2->getPrezzo())
        return true;

    return false;
}

const QList <Articolo*> Gestore::getArticoliPerRivistaSorted(int idx) const
{
    auto listArticoliDiRivista = getArticoliPerRivistaOConferenza(idx, 0);
    std::stable_sort(listArticoliDiRivista.begin(), listArticoliDiRivista.end(), compara2);
    return listArticoliDiRivista;
}

const QList <QString> Gestore::getTutteKeyword() const
{
    //Per ogni articolo prendo le keyword e le aggiungo alla lista di keyword totali
    QList <QString> listaKeyword;
    for(Articolo* art : listArticoli)
        for(QString key : art->getKeyword())
            listaKeyword.push_back(key);

    listaKeyword.removeDuplicates();

    return listaKeyword;
}

const QList <double> Gestore::getGuadagnoPerKeyword(const QList<QString> &listaKeyword) const
{
    QList <double> listaCosti;

    //Per ogni keyword nella lista, prendo l'articolo che la contiene e aggiungo il suo prezzo
    for(QString key : listaKeyword)
    {
        double guadagno = 0;
        for(Articolo* art : listArticoli)
        {
            if(art->getKeyword().contains(key))
                guadagno += art->getPrezzo();
        }

        listaCosti.push_back(guadagno);
    }

    return listaCosti;
}

const QList <QString> Gestore::getKeywordRivistaOConferenzaAt(int idx, int tipo) const
{
    //Per ogni articolo pubblicato per una certa rivista (indice 0) o conferenza (indice1), prendo le sue keyword
    Base* ptrBase;
    if(tipo == 0)
        ptrBase = listRiviste [idx];
    else
        ptrBase = listConferenze [idx];

    QList <QString> keyList;

    for(Articolo* ptrArt : listArticoli)
    {
        if(ptrArt->getEditorePubblicato() == ptrBase)
        {
            for(QString key : ptrArt->getKeyword())
                keyList.push_back(key);
        }
    }

    keyList.removeDuplicates();

    return keyList;
}

bool Gestore::areSimilar(const QList<QString> &listaKeyword1, const QList<QString> &listaKeyword2) const
{
    //Controllo se le due liste di keyword sono simili
    QList <QString> keywordTotali = listaKeyword1;

    for(QString key : listaKeyword2)
        keywordTotali.push_back(key);

    keywordTotali.removeDuplicates();

    int keywordComuni = 0;

    for(QString key : keywordTotali)
        if(listaKeyword1.contains(key) && listaKeyword2.contains(key))
            keywordComuni++;

    double percentage = static_cast<double> (keywordComuni) / keywordTotali.size();
    percentage *= 100;

    if(percentage >= 80)
        return true;

    return false;
}

const QList <Articolo*> Gestore::getInfluenzati(Articolo* attuale) const
{
    //Prima cerco gli articoli che sono influenzati direttamente
    QList <Articolo*> influenzati;
    for(Articolo* art : listArticoli)
    {
        if(attuale != art)
        {
            if(attuale->influenzaLArticolo(art) && !influenzati.contains(art))
                influenzati.push_back(art);
        }
    }

    //Dopo, per ogni articolo influenzato direttamente, controllo se a sua volta ne influenza altri che non siano già presenti
    for(int i = 0; i < influenzati.size(); i++)
    {
        Articolo* art = influenzati [i];
        for(Articolo* tutti : listArticoli)
        {
            if(attuale != tutti && art != tutti)
            {
                if(art->influenzaLArticolo(tutti) && !influenzati.contains(tutti))
                    influenzati.push_back(tutti);
            }
        }
    }

    return influenzati;
}

bool Gestore::isRivista1Specialistica(Rivista* rivista1, Rivista* rivista2) const
{
    int index1 = listRiviste.indexOf(rivista1);
    int index2 = listRiviste.indexOf(rivista2);
    auto listKeywordRivista1 = getKeywordRivistaOConferenzaAt(index1, 0);
    auto listKeywordRivista2 = getKeywordRivistaOConferenzaAt(index2, 0);

    if(listKeywordRivista1.isEmpty() || listKeywordRivista2.isEmpty())
        return false;

    for(QString key : listKeywordRivista1)
        if(!listKeywordRivista2.contains(key))
            return false;

    if(listKeywordRivista1.size() < listKeywordRivista2.size())
        return true;

    return false;
}

const QList <Rivista*> Gestore::getRivisteSpecialistiche() const
{
    QList <Rivista*> listSpecialistiche;
    for(Rivista* rivista1 : listRiviste)
    {
        for(Rivista* rivista2 : listRiviste)
        {
            if(rivista1 != rivista2)
            {
                if(isRivista1Specialistica(rivista1, rivista2) && !listSpecialistiche.contains(rivista1))
                {
                    listSpecialistiche.push_back(rivista1);
                    break;
                }
            }
        }
    }

    return listSpecialistiche;
}

//Serve per tokenizzare il file di testo preso da input
QList <QString> Gestore::tokenizer(QString stringIniziale, char separator)
{
    if(stringIniziale.size() > 0 && stringIniziale.back() != separator)
        stringIniziale += separator;

    QList <QString> tokenizzata;
    int start = 0;
    int len = 0;
    for(int i = 0; i < stringIniziale.length(); i++)
    {
        if(stringIniziale [i] == separator)
        {
            tokenizzata.push_back(stringIniziale.mid(start, len));
            start = i+1;
            len = 0;
        }
        else
            len++;
    }

    tokenizzata.removeAll("");
    return tokenizzata;
}


bool Gestore::inputAutoreValido(Articolo& nuovoArticolo, QString nomiAutori, QString nomePubblicato, QString nomiArticoliCorrelati)
{
    //Questa funzione serve a controllare che i nomi degli autori e della conferenza/rivista di un articolo esistano
    QList <QString> listaNomiAutori = tokenizer(nomiAutori, ',');
    QList <QString> listaNomiArticoliCorrelati = tokenizer(nomiArticoliCorrelati, ',');
    QList <Autore*> listaPuntatoriAutore;
    QList <Articolo*> listaPuntatoriArticolo;
    Base* ptrEditore = nullptr;

    //Controllo l'esistenza degli autori e , se esistono, aggiungo il puntatore alla lista
    for(int i = 0; i < listaNomiAutori.size(); i++)
    {
        for(Autore* ptrAutore : listAutori)
        {
            if((ptrAutore->getNome() + " " + ptrAutore->getCognome()).toLower() == listaNomiAutori [i].toLower())
            {
                listaPuntatoriAutore.push_back(ptrAutore);
                break;
            }
        }
    }

    //Tokenizzo la linea in due parti, la prima contiene il tipo per cui viene pubblicato un articolo : Rivista/Conferenza
    //La seconda contiene il nome
    QList <QString> tipoNomePubblicato = tokenizer(nomePubblicato, ',');

    if(tipoNomePubblicato [0].toUpper() == "CF")          //Controllo nelle conferenze
    {
        for(Base* ptrBase : listConferenze)
            if(ptrBase->getNome().toLower() == tipoNomePubblicato [1].toLower())
                ptrEditore = ptrBase;
    }
    else if(tipoNomePubblicato [0].toUpper() == "RV")         //Controllo nelle riviste
    {
        for(Base* ptrBase : listRiviste)
            if(ptrBase->getNome().toLower() == tipoNomePubblicato [1].toLower())
                ptrEditore = ptrBase;
    }


    //Adesso controllo l'esistenza degli articoli correlati, se nel file di testo è stato messo un trattino - , allora il campo è vuoto
    bool campoArticoliCorrelatiVuoto = false;
    if(listaNomiArticoliCorrelati [0] == '-')
        campoArticoliCorrelatiVuoto = true;

    if(!campoArticoliCorrelatiVuoto)
    {
        //Poichè il campo non è vuoto, cerco gli articoli
        for(int i = 0; i < listaNomiArticoliCorrelati.size(); i++)
        {
            for(Articolo* art : listArticoli)
            {
                if(art->getTitolo().toLower() == listaNomiArticoliCorrelati [i])
                    listaPuntatoriArticolo.push_back(art);
            }
        }
    }

    //Controllo finale
    if(listaPuntatoriAutore.size() == listaNomiAutori.size() && ptrEditore != nullptr)
    {
        nuovoArticolo.setListAutori(listaPuntatoriAutore);
        nuovoArticolo.setEditorePubblicato(ptrEditore);

        if(!campoArticoliCorrelatiVuoto)
        {
            if(listaNomiArticoliCorrelati.size() == listaPuntatoriArticolo.size())
                nuovoArticolo.setListCorrelati(listaPuntatoriArticolo);
            else
                return false;
        }

        return true;
    }

    return false;
}





