#ifndef ARTICOLO_H
#define ARTICOLO_H

#include "Autore.h"
#include "Base.h"

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
        Base* editorePubblicato;
        bool isCorrelato;

    public :
        Articolo();
        QString getIdentificativo() const;
        QString getTitolo() const;
        int getNumPagine() const;
        double getPrezzo() const;
        const QList <Autore*>& getAutori() const;
        const QList <QString>& getKeyword() const;
        const QList <Articolo*>& getCorrelati() const;
        Base* getEditorePubblicato() const;

        void setIdentificativo(int number);
        void setTitolo(QString title);
        void setNumPagine(int numPag);
        void setPrezzo(double price);
        void addAutore(Autore* author);
        void addKeyword(QString keyword);
        void addCorrelato(Articolo* corr);
        void setEditorePubblicato(Base* ptr);
        void rimuoviCorrelato(int idx);
        void setListAutori(QList <Autore*> ls);
        void setListCorrelati(QList <Articolo*> ls);

        bool operator==(const Articolo& A) const;
};

#endif // ARTICOLO_H
