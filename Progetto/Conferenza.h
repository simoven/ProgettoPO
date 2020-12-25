#ifndef CONFERENZA_H
#define CONFERENZA_H

#include "Base.h"
#include <QList>

class Conferenza : public Base
{
    private :
        QString luogo;
        QList <QString> listOrganizzatori;
        int numPartecipanti;

    public:
        Conferenza();

        QString getLuogo() const;
        const QList <QString> getOrganizzatori() const;
        int getPartecipanti() const;

        void setLuogo(QString place);
        void addOrganizzatore(QString man, char separator = '\n');
        void setPartecipanti(int partecipanti);

        bool operator==(const Conferenza& C) const;
};

#endif // CONFERENZA_H
