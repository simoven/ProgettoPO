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

        bool aggiungiArticolo(const Articolo& article, bool increase = true);
        bool aggiungiAutore(const Autore& author, bool increase = true);
        bool aggiungiConferenza(const Conferenza& conference);
        bool aggiungiRivista(const Rivista& paper);

        bool rimuoviArticolo(int idx);
        bool rimuoviAutore(int idx);
        void rimuoviConferenza(int idx);
        void rimuoviRivista(int idx);

        const QList <Articolo*>& getArticoli() const;
        const QList <Autore*>& getAutori() const;
        const QList <Conferenza*>& getConferenze() const;
        const QList <Rivista*>& getRiviste() const;
};

#endif // GESTORE_H
