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
