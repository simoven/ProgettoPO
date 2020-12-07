#ifndef GESTORE_H
#define GESTORE_H

#include "Articolo.h"
#include "Autore.h"
#include "Conferenza.h"
#include "Rivista.h"

class Gestore
{
    private :
        QList <Articolo*> listArticoli;
        QList <Autore*> listAutori;
        QList <Conferenza*> listConferenze;
        QList <Rivista*> listRiviste;

    public :
        Gestore();
        ~Gestore();
        Gestore(const Gestore& G);
        Gestore& operator=(const Gestore& G);

        void aggiungiArticolo(const Articolo& article);
        void aggiungiAutore(const Autore& author);
        void aggiungiConferenza(const Conferenza& conference);
        void aggiungiRivista(const Rivista& paper);

        const QList <Articolo*> getArticoli() const;
        QList <Autore*> getAutori() const;
        QList <Conferenza*> getConferenze() const;
        QList <Rivista*> getRiviste() const;
};

#endif // GESTORE_H
