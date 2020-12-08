#include "Conferenza.h"

Conferenza::Conferenza() : Base(), luogo(""), numPartecipanti(0) {}

QString Conferenza::getLuogo() const { return luogo; }

const QList <QString> Conferenza::getOrganizzatori() const { return listOrganizzatori; }

int Conferenza::getPartecipanti() const { return numPartecipanti; }

void Conferenza::setLuogo(QString place) { luogo = place; }

void Conferenza::addOrganizzatore(QString man) { listOrganizzatori.push_back(man); }

void Conferenza::setPartecipanti(int partecipanti) { numPartecipanti = partecipanti; }


