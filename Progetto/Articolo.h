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
        QList <QString> listAutori;
        QList <QString> listKeyword;
        QList <QString> listCorrelati;
        Tipo pubblicatoPer;

    public :
        Articolo();
        QString getIdentificativo() const;
        QString getTitolo() const;
        int getNumPagine() const;
        double getPrezzo() const;
        const QList <QString>& getAutori() const;
        const QList <QString>& getKeyword() const;
        const QList <QString>& getCorrelati() const;
        Tipo getPubblicato() const;

        void setIdentificativo(int number);
        void setTitolo(QString title);
        void setNumPagine(int numPag);
        void setPrezzo(double price);
        void addAutore(QString author);
        void addKeyword(QString keyword);
        void addCorrelato(QString corr);
        void setTipo(Tipo pubblicato);
};

#endif // ARTICOLO_H
