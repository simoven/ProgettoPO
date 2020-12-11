#include "Articolo.h"

Articolo::Articolo() : titolo(""), nPagine(0), prezzo(0), editorePubblicato(nullptr), isCorrelato(false) {}

QString Articolo::getIdentificativo() const { return identificativo; }

QString Articolo::getTitolo() const { return titolo; }

int Articolo::getNumPagine() const { return nPagine; }

double Articolo::getPrezzo() const { return prezzo; }

bool Articolo::getIsCorrelato() const { return isCorrelato; }

const QList <Autore*>& Articolo::getAutori() const { return listAutori; }

const QList <QString>& Articolo::getKeyword() const { return listKeyword; }

const QList <Articolo*>& Articolo::getCorrelati() const { return listCorrelati; }

Base* Articolo::getEditorePubblicato() const { return editorePubblicato; }

void Articolo::setIdentificativo(int number) { identificativo = QString::number(number); }

void Articolo::setTitolo(QString title) { titolo = title; }

void Articolo::setNumPagine(int numPag) { nPagine = numPag; }

void Articolo::setPrezzo(double price) { prezzo = price; }

void Articolo::setIsCorrelato(bool x) { isCorrelato = x; }

void Articolo::addAutore(Autore* author) { listAutori.push_back(author); }

void Articolo::setEditorePubblicato(Base *ptr) { editorePubblicato = ptr; }

void Articolo::addKeyword(QString keyword)
{
    if(keyword.size() != 0)
    {
        //Tokenizzo le keyword
        if(keyword.back() != ',')
            keyword += ',';

        int len = 0;
        int idx = 0;
        for(int i = 0; i < keyword.length(); i++)
        {
            if(keyword [i] == ',')
            {
                listKeyword.push_back(keyword.mid(idx, len));
                idx = i+1;
                len = 0;
            }
            else
                len++;
        }
    }
}

void Articolo::addCorrelato(Articolo* corr) { listCorrelati.push_back(corr); }

bool Articolo::operator==(const Articolo& A) const
{
    if(titolo != A.titolo || nPagine != A.nPagine || prezzo != A.prezzo)
        return false;

    if(listAutori.size() != A.listAutori.size() || listCorrelati.size() != A.listCorrelati.size() || listKeyword.size() != A.listKeyword.size())
        return false;

    for(int i = 0; i < listAutori.size(); i++)
        if(listAutori [i] != A.listAutori [i])
            return false;

    for(int i = 0; i < listCorrelati.size(); i++)
        if(listCorrelati [i] != A.listCorrelati [i])
            return false;

    for(int i = 0; i < listKeyword.size(); i++)
        if(listKeyword [i] != A.listKeyword [i])
            return false;

    if(editorePubblicato != A.editorePubblicato)
        return false;

    return true;
}
