#ifndef RIVISTA_H
#define RIVISTA_H

#include "Base.h"

class Rivista : public Base
{
    private :
        QString editore;
        int volume;

    public:
        Rivista();

        QString getEditore() const;
        int getVolume() const;

        void setEditore(QString editor);
        void setVolume(int vol);
};

#endif // RIVISTA_H
