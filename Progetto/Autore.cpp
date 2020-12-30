#include "Autore.h"

Autore::Autore() : identificativo(""), nome(""), cognome(""), isCorrelato(false) {}

QString Autore::getIdentificativo() const { return identificativo; }

QString Autore::getNome() const { return nome; }

QString Autore::getCognome() const { return cognome; }

const QList <QString>& Autore::getAfferenze() const { return afferenze; }

void Autore::setNome(QString name) { nome = name; }

void Autore::setIdentificativo(int number) { identificativo = QString::number(number); }

void Autore::setCognome(QString surname) { cognome = surname; }

void Autore::addAfferenze(QString workplace, char separator)
{
    if(workplace.size() != 0 && workplace [0] != '-')
    {
        if(workplace.back() != separator)
            workplace += separator;

        int len = 0;
        int idx = 0;
        //Tokenizzo il plain text
        for(int i = 0; i < workplace.length(); i++)
        {
            if(workplace [i] == separator)
            {
                afferenze.push_back(workplace.mid(idx, len));
                idx = i+1;
                len = 0;
            }
            else
                len++;
        }
    }

    afferenze.removeAll("");
}

bool Autore::operator==(const Autore &A) const
{
    if(nome != A.nome || cognome != A.cognome)
        return false;

    if(afferenze != A.afferenze)
        return false;

    return true;
}
