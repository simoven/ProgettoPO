#include "Conferenza.h"

Conferenza::Conferenza() : Base(), luogo(""), numPartecipanti(0) {}

QString Conferenza::getLuogo() const { return luogo; }

const QList <QString> Conferenza::getOrganizzatori() const { return listOrganizzatori; }

int Conferenza::getPartecipanti() const { return numPartecipanti; }

void Conferenza::setLuogo(QString place) { luogo = place; }

void Conferenza::addOrganizzatore(QString organizzatori)
{
    if(organizzatori.back() != '\n')
    organizzatori += '\n';

    //Tokenizzo gli organizzatori
    int len = 0;
    int idx = 0;
    for(int i = 0; i < organizzatori.length(); i++)
    {
        if(organizzatori [i] == '\n')
        {
            listOrganizzatori.push_back(organizzatori.mid(idx, len));
            idx = i+1;
            len = 0;
        }
        else
            len++;
    }
}

void Conferenza::setPartecipanti(int partecipanti) { numPartecipanti = partecipanti; }

bool Conferenza::operator==(const Conferenza &C) const
{
    if(getNome() != C.getNome() || getData() != C.getData() || luogo != C.luogo)
        return false;

    return true;
}


