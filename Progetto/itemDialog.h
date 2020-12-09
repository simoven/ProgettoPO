#ifndef ITEMDIALOG_H
#define ITEMDIALOG_H

#include <QDialog>
#include <Autore.h>
#include <Rivista.h>
#include <Conferenza.h>
#include <Articolo.h>
#include <QDebug>
#include <QListWidgetItem>
#include "Gestore.h"
#include <QPixmap>

namespace Ui { class itemDialog; }

enum classType {cAutore = 0, cArticolo, cConferenza, cRivista};

class itemDialog : public QDialog
{
    Q_OBJECT

    public:
        explicit itemDialog(int idx, classType tp, Gestore* ptr2, QListWidgetItem* itm, QWidget *parent = nullptr);
        ~itemDialog();

    private slots:
    void on_bottoneIndietro_clicked();

    private:
        Ui::itemDialog *ui;
        Autore* author;
        Rivista* paper;
        Conferenza* conference;
        Articolo* article;

        classType type;
        Gestore* ptrGestore;
        int index;

        void showAutore();
        void showArticolo();
        void showConferenza();
        void showRivista();
        void hide();
};

#endif // ITEMDIALOG_H
