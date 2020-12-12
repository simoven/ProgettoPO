/* This file is part of ProgettoPO.
ProgettoPO is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
ProgettoPO is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with ProgettoPO.  If not, see <http://www.gnu.org/licenses/>.*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainStacked->setCurrentWidget(ui->pageMain);
    hide();

    connect(this, SIGNAL(rimuoviItem(QListWidget*)), this, SLOT(onRimuoviItem(QListWidget*)));

    connect(ui->widgetAutore, &QListWidget::itemClicked, this, &MainWindow::onWidgetClicked);
    connect(ui->widgetArticolo, &QListWidget::itemClicked, this, &MainWindow::onWidgetClicked);
    connect(ui->widgetRivista, &QListWidget::itemClicked, this, &MainWindow::onWidgetClicked);
    connect(ui->widgetConferenza, &QListWidget::itemClicked, this, &MainWindow::onWidgetClicked);

    connect(ui->widgetAutore, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onWidgetDoubleClicked(QListWidgetItem*)));
    connect(ui->widgetArticolo, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onWidgetDoubleClicked(QListWidgetItem*)));
    connect(ui->widgetRivista, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onWidgetDoubleClicked(QListWidgetItem*)));
    connect(ui->widgetConferenza, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onWidgetDoubleClicked(QListWidgetItem*)));

}

MainWindow::~MainWindow()
{
    for(int i = 0; i < ui->widgetArticolo->count(); i++)
        delete ui->widgetArticolo->item(i);

    for(int i = 0; i < ui->widgetAutore->count(); i++)
        delete ui->widgetAutore->item(i);

    for(int i = 0; i < ui->widgetRivista->count(); i++)
        delete ui->widgetRivista->item(i);

    for(int i = 0; i < ui->widgetConferenza->count(); i++)
        delete ui->widgetConferenza->item(i);

    delete ui;
}

void MainWindow::svuotaLineEdit()
{
    ui->lineEdit1->setText("");
    ui->lineEdit2->setText("");
    ui->lineEdit3->setText("");
    ui->plainText->setPlainText("");
    ui->spinBox->setValue(0);
    ui->doubleSpinBox->setValue(0);
}

void MainWindow::hide()
{
    ui->label1->setText(""); ui->lineEdit1->setVisible(false);
    ui->label2->setText(""); ui->lineEdit2->setVisible(false);
    ui->label3->setText(""); ui->lineEdit3->setVisible(false);
    ui->label4->setText(""); ui->plainText->setVisible(false);
    ui->label5->setText(""); ui->spinBox->setVisible(false);
    ui->label6->setText(""); ui->doubleSpinBox->setVisible(false);
    ui->label7->setText(""); ui->calendarWidget->setVisible(false);
    ui->bottoneRimuovi->setVisible(false);
}

//Bottoni vari

void MainWindow::on_SezioneA_clicked()
{
    ui->mainStacked->setCurrentWidget(ui->pageMain);
}

void MainWindow::on_SezioneB_clicked()
{
    ui->mainStacked->setCurrentWidget(ui->page2);
}

//Definisco cosa mostrare in base al radio button
void MainWindow::on_AutoreButton_clicked()
{
    hide();
    ui->listStacked->setCurrentWidget(ui->pageAutore);
    ui->labelStacked->setText("Autori : ");
    ui->label1->setText("Nome"); ui->lineEdit1->setVisible(true);
    ui->label2->setText("Cognome"); ui->lineEdit2->setVisible(true);
    ui->label4->setText("Afferenze"); ui->plainText->setVisible(true);
    ui->plainText->setPlaceholderText("Scrivi un'afferenza per linea");

    ui->lineEdit2->setPlaceholderText("");
}

void MainWindow::on_ArticoloButton_clicked()
{
    hide();
    ui->listStacked->setCurrentWidget(ui->pageArticolo);
    ui->labelStacked->setText("Articoli : ");
    ui->label1->setText("Titolo"); ui->lineEdit1->setVisible(true);
    ui->label2->setText("Keyword"); ui->lineEdit2->setVisible(true);
    ui->lineEdit2->setPlaceholderText("Scrivi le keyword separate da virgole, senza spazi");
    ui->label5->setText("Pagine"); ui->spinBox->setVisible(true);
    ui->label6->setText("Prezzo"); ui->doubleSpinBox->setVisible(true);
}

void MainWindow::on_ConferenzaButton_clicked()
{
    hide();
    ui->listStacked->setCurrentWidget(ui->pageConferenza);
    ui->labelStacked->setText("Conferenze : ");
    ui->label1->setText("Nome"); ui->lineEdit1->setVisible(true);
    ui->label2->setText("Acronimo"); ui->lineEdit2->setVisible(true);
    ui->label3->setText("Luogo"); ui->lineEdit3->setVisible(true);
    ui->label4->setText("Organizzatori"); ui->plainText->setVisible(true);
    ui->plainText->setPlaceholderText("Scrivi un organizzatore per riga");

    ui->label5->setText("Partecipanti"); ui->spinBox->setVisible(true);
    ui->label7->setText("Data"); ui->calendarWidget->setVisible(true);

    ui->lineEdit2->setPlaceholderText("");
}

void MainWindow::on_RivistaButton_clicked()
{
    hide();
    ui->listStacked->setCurrentWidget(ui->pageRivista);
    ui->labelStacked->setText("Riviste : ");
    ui->label1->setText("Nome"); ui->lineEdit1->setVisible(true);
    ui->label2->setText("Acronimo"); ui->lineEdit2->setVisible(true);
    ui->label3->setText("Editore"); ui->lineEdit3->setVisible(true);
    ui->label5->setText("Volume"); ui->spinBox->setVisible(true);
    ui->label7->setText("Data"); ui->calendarWidget->setVisible(true);

    ui->lineEdit2->setPlaceholderText("");
}

//Fine bottoni vari

void errorMsg(QListWidgetItem* item)
{
    //Significa che è già presente oppure alcuni campi sono vuoti
    delete item;
    QMessageBox msg(QMessageBox::Warning, "Impossibile aggiungere", "Elemento già presente oppure alcuni campi obbligatori sono vuoti");
    msg.exec();
}

//Definisco il comportamento del bottone aggiungi
void MainWindow::on_bottoneAggiungi_clicked()
{
    QListWidgetItem* item = new QListWidgetItem;
    if(ui->AutoreButton->isChecked())
    {
        Autore author;
        author.setNome(ui->lineEdit1->text());
        author.setCognome(ui->lineEdit2->text());
        QString text = ui->plainText->toPlainText();
        author.addAfferenze(text);

        if(gestore.aggiungiAutore(author))
        {
            item->setText(author.getNome() + " " + author.getCognome());
            item->setIcon(QIcon(":/res/AutoreColor.png"));
            item->setCheckState(Qt::Unchecked);
            ui->widgetAutore->addItem(item);

        }
        else
            errorMsg(item);

    }
    else if(ui->ArticoloButton->isChecked())
    {
        Articolo article;
        article.setTitolo(ui->lineEdit1->text());
        QString keyword = ui->lineEdit2->text();
        article.addKeyword(keyword);
        article.setNumPagine(ui->spinBox->value());
        article.setPrezzo(ui->doubleSpinBox->value());
        if(gestore.aggiungiArticolo(article))
        {
            item->setText(article.getTitolo());
            item->setIcon(QIcon(":/res/ArticoloColor.png"));
            item->setCheckState(Qt::Unchecked);
            ui->widgetArticolo->addItem(item);
        }
        else
            errorMsg(item);

    }
    else if(ui->ConferenzaButton->isChecked())
    {
        Conferenza conference;
        conference.setData(ui->calendarWidget->selectedDate());
        conference.setNome(ui->lineEdit1->text());
        conference.setAcronimo(ui->lineEdit2->text());
        conference.setLuogo(ui->lineEdit3->text());
        conference.setPartecipanti(ui->spinBox->value());
        QString organizzatori = ui->plainText->toPlainText();
        conference.addOrganizzatore(organizzatori);

        if(gestore.aggiungiConferenza(conference))
        {
            item->setText(conference.getNome());
            item->setCheckState(Qt::Unchecked);
            item->setIcon(QIcon(":/res/ConferenzaColor.png"));
            ui->widgetConferenza->addItem(item);
        }
        else
            errorMsg(item);

    }
    else if(ui->RivistaButton->isChecked())
    {
        Rivista paper;
        paper.setNome(ui->lineEdit1->text());
        paper.setAcronimo(ui->lineEdit2->text());
        paper.setEditore(ui->lineEdit3->text());
        paper.setVolume(ui->spinBox->value());
        paper.setData(ui->calendarWidget->selectedDate());

        if(gestore.aggiungiRivista(paper))
        {
            item->setText(paper.getNome());
            item->setIcon(QIcon(":/res/RivistaColor.png"));
            item->setCheckState(Qt::Unchecked);
            ui->widgetRivista->addItem(item);
        }
        else
            errorMsg(item);
    }
    else
    {
        delete item;
        item = nullptr;
        QMessageBox msg(QMessageBox::Critical, "Attenzione", "Devi selezionare un'opzione");
        msg.exec();
    }

    svuotaLineEdit();
}


void MainWindow::onWidgetClicked()
{
    //In base alla list widget che chiama la funzione controllo gli elementi checked per attivare il bottone rimuovi
    QListWidget* itm = qobject_cast<QListWidget*> (sender());
    bool itmChecked = false;
    for(int i = 0; i < itm->count(); i++)
    {
        if(itm->item(i)->checkState() == Qt::Checked)
        {
            itmChecked = true;
            break;
        }
    }

    if(itmChecked)
        ui->bottoneRimuovi->setVisible(true);
    else
        ui->bottoneRimuovi->setVisible(false);
}



void MainWindow::on_bottoneRimuovi_clicked()
{
    //Quando premo il bottone rimuovi passo il puntatore della list widget attiva in quel momento
    //Capisco qual è la lista attiva tramite il current widget dello stackedWidget

    QListWidget* itm;
    if(ui->listStacked->currentWidget() == ui->widgetArticolo->parent())
        itm = ui->widgetArticolo;

    else if(ui->listStacked->currentWidget() == ui->widgetConferenza->parent())
        itm = ui->widgetConferenza;

    else if(ui->listStacked->currentWidget() == ui->widgetAutore->parent())
        itm = ui->widgetAutore;

    else
        itm = ui->widgetRivista;

    emit rimuoviItem(itm);
}

void MainWindow::onRimuoviItem(QListWidget* itm)
{
    //Itm è un puntatore alla lista attiva
    bool deleted = false;
    for(int i = 0; i < itm->count(); i++)
    {
        deleted = false;
        if(itm->item(i)->checkState() == Qt::Checked)
        {
            if(itm->objectName() == "widgetAutore" && gestore.rimuoviAutore(i))
                deleted = true;

            else if(itm->objectName() == "widgetArticolo" && gestore.rimuoviArticolo(i))
                deleted = true;

            else if(itm->objectName() == "widgetConferenza" && gestore.rimuoviConferenza(i))
                deleted = true;

            else if(itm->objectName() == "widgetRivista" && gestore.rimuoviRivista(i))
                deleted = true;

            if(deleted)
            {
                delete itm->takeItem(i);
                i--;
            }

        }

    }

    ui->bottoneRimuovi->setVisible(false);
}

void MainWindow::onWidgetDoubleClicked(QListWidgetItem* item)
{
    QListWidget* ptrList = qobject_cast <QListWidget*> (sender());

    int idx = 0;
    for(int i = 0; i < ptrList->count(); i++)
    {
        if(ptrList->item(i) == item)
        {
            idx = i;
            break;
        }
    }

    //Capisco da quale classe è partito il segnale
    classType tipo;
    if(ptrList == ui->widgetArticolo)
        tipo = cArticolo;
    else if(ptrList == ui->widgetAutore)
        tipo = cAutore;
    else if(ptrList == ui->widgetConferenza)
        tipo = cConferenza;
    else
        tipo = cRivista;

    itemDialog dialog(idx, tipo, &gestore, item);
    dialog.setModal(true);
    dialog.exec();
}

