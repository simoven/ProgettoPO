#ifndef GESTORE_H
#define GESTORE_H

#include "Articolo.h"
#include "Autore.h"
#include "Conferenza.h"
#include "Rivista.h"
#include <QDebug>
#include <QMessageBox>

class Gestore
{
    private :
        QList <Articolo*> listArticoli;
        QList <Autore*> listAutori;
        QList <Conferenza*> listConferenze;
        QList <Rivista*> listRiviste;

        int nAutori;
        int nArticoli;

        void svuota();
        void copia(const Gestore& G);

    public :
        Gestore();
        ~Gestore();
        Gestore(const Gestore& G);
        Gestore& operator=(const Gestore& G);

        bool aggiungiArticolo(const Articolo& article, bool mostraErrore = true, bool isNuovaAggiunta = true, int idx = -1, bool increase = true);
        bool aggiungiAutore(const Autore& author, bool mostraErrore = true, bool isNuovaAggiunta = true, int idx = -1, bool increase = true);
        bool aggiungiConferenza(const Conferenza& conference, bool mostraErrore = true, bool isNuovaAggiunta = true, int idx = -1);
        bool aggiungiRivista(const Rivista& paper, bool mostraErrore = true, bool isNuovaAggiunta = true, int idx = -1);

        bool rimuoviArticolo(int idx);
        bool rimuoviAutore(int idx);
        bool rimuoviConferenza(int idx);
        bool rimuoviRivista(int idx);

        const QList <Articolo*>& getArticoli() const;
        const QList <Autore*>& getAutori() const;
        const QList <Conferenza*>& getConferenze() const;
        const QList <Rivista*>& getRiviste() const;

        const QList <Articolo*> getArticoliPerAutore(int idx) const;
        const QList <Articolo*> getArticoliPerAutoreSorted(int idx) const;
        const QList <Base*> getRivisteNonPubblicateDaAutore(int idx) const;

        const QList <Articolo*> getArticoliPerRivista(int idx) const;
        const QList <Articolo*> getArticoliPerRivistaSorted(int idx) const;
        const QList <Articolo*> getArticoliPerConferenza(int idx) const;

        const QList <QString> getTutteKeyword() const;
        const QList <double> getGuadagnoPerKeyword(const QList <QString>& listaKeyword) const;

        const QList <QString> getKeywordConferenzaAt(int idx) const;

        const QList <Articolo*> getInfluenzati(Articolo* iniziale) const;

        bool areSimilar(const QList <QString>& listaKeyword1, const QList <QString>& listaKeyword2) const;
};

#endif // GESTORE_H
