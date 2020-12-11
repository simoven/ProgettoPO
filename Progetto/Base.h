#ifndef BASE_H
#define BASE_H

#include <QString>
#include <QDate>

class Base
{
    private :
        QString nome, acronimo;
        QDate data;
        bool isCorrelato;

    public:
        QString getNome() const { return nome; }
        QString getAcronimo() const { return acronimo; }
        QDate getData() const { return data; }
        QString stampaData() const { return data.toString(Qt::ISODate); }
        bool getIsCorrelato() const { return isCorrelato; }
        virtual ~Base() {}

        void setData(QDate date) { data = date; }
        void setNome(QString name) { nome = name; }
        void setAcronimo(QString achronyme) { acronimo = achronyme; }
        void setIsCorrelato(bool x) { isCorrelato = x; }

    protected:
        Base() : nome(""), acronimo(""), data(QDate()), isCorrelato(false) {}
};

#endif // BASE_H
