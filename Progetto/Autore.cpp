#include "Autore.h"

Autore::Autore() : identificativo(""), nome(""), cognome("") {}

QString Autore::getIdentificativo() const { return identificativo; }

QString Autore::getNome() const { return nome; }

QString Autore::getCognome() const { return cognome; }

const QList <QString>& Autore::getAfferenze() const { return afferenze; }

void Autore::setNome(QString name) { nome = name; }

void Autore::setIdentificativo(int number) { identificativo = QString::number(number); }

void Autore::setCognome(QString surname) { cognome = surname; }

void Autore::addAfferenze(QString workplace) { afferenze.push_back(workplace); }

bool Autore::operator==(const Autore &A) const
{
    if(nome != A.nome || cognome != A.cognome)
        return false;

    if(afferenze.size() != A.afferenze.size())
        return false;

    for(int i = 0; i < afferenze.size(); i++)
        if(afferenze [i] != A.afferenze [i])
            return false;

    return true;
}
