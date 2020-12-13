#ifndef AUTORE_H
#define AUTORE_H
#include <QString>
#include <QList>

class Autore
{
    private :
        QString identificativo, nome, cognome;
        QList <QString> afferenze;
        bool isCorrelato;

    public:
        Autore();
        QString getIdentificativo() const;
        QString getNome() const;
        QString getCognome() const;
        const QList <QString>& getAfferenze() const;

        void setNome(QString name);
        void setIdentificativo(int number);
        void setCognome(QString surname);
        void addAfferenze(QString workplace);

        bool operator==(const Autore& A) const;
};

#endif // AUTORE_H
