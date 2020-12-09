#include "Articolo.h"

Articolo::Articolo() : titolo(""), nPagine(0), prezzo(0), pubblicatoPer(CONFERENZA), nomePubblicato("") {}

QString Articolo::getIdentificativo() const { return identificativo; }

QString Articolo::getTitolo() const { return titolo; }

int Articolo::getNumPagine() const { return nPagine; }

double Articolo::getPrezzo() const { return prezzo; }

const QList <QString>& Articolo::getAutori() const { return listAutori; }

const QList <QString>& Articolo::getKeyword() const { return listKeyword; }

const QList <QString>& Articolo::getCorrelati() const { return listCorrelati; }

Tipo Articolo::getPubblicato() const { return pubblicatoPer; }

QString Articolo::getNomePubblicato() const { return nomePubblicato; }

void Articolo::setIdentificativo(int number) { identificativo = QString::number(number); }

void Articolo::setTitolo(QString title) { titolo = title; }

void Articolo::setNumPagine(int numPag) { nPagine = numPag; }

void Articolo::setPrezzo(double price) { prezzo = price; }

void Articolo::addAutore(QString author) { listAutori.push_back(author); }

void Articolo::addKeyword(QString keyword) { listKeyword.push_back(keyword); }

void Articolo::addCorrelato(QString corr) { listCorrelati.push_back(corr); }

void Articolo::setTipo(Tipo pubblicato) { pubblicatoPer = pubblicato; }

void Articolo::setNomePubblicato(QString name) { nomePubblicato = name; }

bool Articolo::operator==(const Articolo& A) const
{
    if(titolo != A.titolo || nPagine != A.nPagine || prezzo != A.prezzo || pubblicatoPer != A.pubblicatoPer)
        return false;

    return true;
}
