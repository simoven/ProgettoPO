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
        void addOrganizzatore(QString man);
        void setPartecipanti(int partecipanti);
};

#endif // CONFERENZA_H
