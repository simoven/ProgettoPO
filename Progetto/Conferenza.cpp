#include "Conferenza.h"

Conferenza::Conferenza() : Base(), luogo(""), numPartecipanti(0){}

QString Conferenza::getLuogo() const { return luogo; }

const QList <QString> Conferenza::getOrganizzatori() const { return listOrganizzatori; }

int Conferenza::getPartecipanti() const { return numPartecipanti; }

void Conferenza::setLuogo(QString place) { luogo = place; }

void Conferenza::addOrganizzatore(QString organizzatori, char separator)
{
    if(organizzatori.size() != 0)
    {
        if(organizzatori.back() != separator)
        organizzatori += separator;

        //Tokenizzo gli organizzatori
        int len = 0;
        int idx = 0;
        for(int i = 0; i < organizzatori.length(); i++)
        {
            if(organizzatori [i] == separator)
            {
                listOrganizzatori.push_back(organizzatori.mid(idx, len));
                idx = i+1;
                len = 0;
            }
            else
                len++;
        }
    }
}

void Conferenza::setPartecipanti(int partecipanti) { numPartecipanti = partecipanti; }

bool Conferenza::operator==(const Conferenza &C) const
{
    if(getNome() != C.getNome() || (getData().year() != C.getData().year()) || luogo != C.luogo)
        return false;

    if(listOrganizzatori != C.listOrganizzatori)
        return false;

    return true;
}


