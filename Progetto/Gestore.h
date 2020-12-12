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

        bool aggiungiArticolo(const Articolo& article, bool isNuovaAggiunta = true, int idx = -1, bool increase = true);
        bool aggiungiAutore(const Autore& author, bool isNuovaAggiunta = true, int idx = -1, bool increase = true);
        bool aggiungiConferenza(const Conferenza& conference, bool isNuovaAggiunta = true, int idx = -1);
        bool aggiungiRivista(const Rivista& paper, bool isNuovaAggiunta = true, int idx = -1);

        bool rimuoviArticolo(int idx);
        bool rimuoviAutore(int idx);
        bool rimuoviConferenza(int idx);
        bool rimuoviRivista(int idx);

        const QList <Articolo*>& getArticoli() const;
        const QList <Autore*>& getAutori() const;
        const QList <Conferenza*>& getConferenze() const;
        const QList <Rivista*>& getRiviste() const;
};

#endif // GESTORE_H
