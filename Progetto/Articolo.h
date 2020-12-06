#ifndef ARTICOLO_H
#define ARTICOLO_H

#include "Autore.h"

enum Tipo {CONFERENZA = 0, RIVISTA};

class Articolo
{
    private :
        QString identificativo, titolo;
        int nPagine;
        double prezzo;
        QList <Autore*> listAutori;
        QList <QString> listKeyword;
        QList <Articolo*> listCorrelati;
        Tipo pubblicatoPer;

    public :
        Articolo();
        QString getIdentificativo() const;
        QString getTitolo() const;
        int getNumPagine() const;
        double getPrezzo() const;
        const QList <Autore*>& getAutori() const;
        const QList <QString>& getKeyword() const;
        const QList <Articolo*>& getCorrelati() const;
        Tipo getPubblicato() const;

        void setIdentificativo();
        void setTitolo(QString title);
        void setNumPagine(int numPag);
        void setPrezzo(double price);
        void addAutore(Autore* author);
        void addKeyword(QString keyword);
        void addCorrelato(Articolo* corr);
        void setTipo(Tipo pubblicato);
};

#endif // ARTICOLO_H
