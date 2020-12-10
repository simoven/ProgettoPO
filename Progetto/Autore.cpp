#include "Autore.h"

Autore::Autore() : identificativo(""), nome(""), cognome("") {}

QString Autore::getIdentificativo() const { return identificativo; }

QString Autore::getNome() const { return nome; }

QString Autore::getCognome() const { return cognome; }

bool Autore::getIsCorrelato() const { return isCorrelato; }

const QList <QString>& Autore::getAfferenze() const { return afferenze; }

void Autore::setNome(QString name) { nome = name; }

void Autore::setIdentificativo(int number) { identificativo = QString::number(number); }

void Autore::setCognome(QString surname) { cognome = surname; }

void Autore::setIsCorrelato(bool x) { isCorrelato = x; }

void Autore::addAfferenze(QString workplace)
{
    if(workplace.size() != 0)
    {
        if(workplace.back() != '\n')
            workplace += '\n';

        int len = 0;
        int idx = 0;
        //Tokenizzo il plain text
        for(int i = 0; i < workplace.length(); i++)
        {
            if(workplace [i] == '\n')
            {
                afferenze.push_back(workplace.mid(idx, len));
                idx = i+1;
                len = 0;
            }
            else
                len++;
        }
    }
}

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
