#ifndef GESTORE_H
#define GESTORE_H

#include "Articolo.h"
#include "Autore.h"
#include "Conferenza.h"
#include "Rivista.h"
#include <QDebug>

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

        bool aggiungiArticolo(const Articolo& article);
        bool aggiungiAutore(const Autore& author);
        bool aggiungiConferenza(const Conferenza& conference);
        bool aggiungiRivista(const Rivista& paper);

        void rimuoviArticolo(int idx);
        void rimuoviAutore(int idx);
        void rimuoviConferenza(int idx);
        void rimuoviRivista(int idx);

        const QList <Articolo*> getArticoli() const;
        QList <Autore*> getAutori() const;
        QList <Conferenza*> getConferenze() const;
        QList <Rivista*> getRiviste() const;
};

#endif // GESTORE_H
