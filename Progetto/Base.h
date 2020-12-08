#ifndef BASE_H
#define BASE_H

#include <QString>
#include <QDate>

class Base
{
    private :
        QString nome, acronimo;
        QDate data;

    public:
        QString getNome() const { return nome; }
        QString getAcronimo() const { return acronimo; }
        QDate getData() const { return data; }
        QString stampaData() const { return data.toString(Qt::ISODate); }

        void setData(QDate date) { data = date; }
        void setNome(QString name) { nome = name; }
        void setAcronimo(QString achronyme) { acronimo = achronyme; }

    protected:
        Base() : nome(""), acronimo(""), data(QDate()) {}
};

#endif // BASE_H
