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

    connect(ui->conferenzeSimiliButton, SIGNAL(clicked()), ui->dinamicListWidgetMisto, SLOT(clear()));
    connect(ui->articoliPerConferenzaButton, SIGNAL(clicked()), ui->dinamicListWidgetMisto, SLOT(clear()));
    connect(ui->keywordButton, SIGNAL(clicked()), ui->dinamicListWidgetMisto, SLOT(clear()));

    connect(ui->tuttiAutoriListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(disattivaElementiChecked(QListWidgetItem*)));
    connect(ui->tutteConferenzeListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(disattivaElementiChecked(QListWidgetItem*)));
    connect(ui->tutteRivisteListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(disattivaElementiChecked(QListWidgetItem*)));

    connect(ui->articoloLeggiButton, SIGNAL(clicked()), ui->percorsoLineEdit, SLOT(clear()));
    connect(ui->autoreLeggiButton, SIGNAL(clicked()), ui->percorsoLineEdit, SLOT(clear()));
    connect(ui->rivistaLeggiButton, SIGNAL(clicked()), ui->percorsoLineEdit, SLOT(clear()));
    connect(ui->conferenzaLeggiButton, SIGNAL(clicked()), ui->percorsoLineEdit, SLOT(clear()));
}

MainWindow::~MainWindow()
{
    ui->widgetArticolo->clear();
    ui->widgetAutore->clear();
    ui->widgetConferenza->clear();
    ui->widgetRivista->clear();

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
    //Serve solo a nascondere gli elementi grafici
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

void MainWindow::mostraTuttiAutori()
{
    ui->tuttiAutoriListWidget->clear();
    auto listAutori = gestore.getAutori();
    for(int i = 0; i < listAutori.size(); i++)
    {
        ui->tuttiAutoriListWidget->addItem(listAutori [i]->getNome() + " " + listAutori [i]->getCognome());
        ui->tuttiAutoriListWidget->item(i)->setCheckState(Qt::Unchecked);
        ui->tuttiAutoriListWidget->item(i)->setIcon(QIcon(":/res/AutoreColor.png"));
    }
}

void MainWindow::disattivaRadioButton()
{
    //Devo fare così altrimenti i bottoni rimangono attivati se cambio pagina
    ui->articoliInRivisteButton->setAutoExclusive(false); ui->articoliInRivisteButton->setChecked(false); ui->articoliInRivisteButton->setAutoExclusive(true);
    ui->tuttiArticoliButton->setAutoExclusive(false); ui->tuttiArticoliButton->setChecked(false); ui->tuttiArticoliButton->setAutoExclusive(true);
    ui->mediaPrezziButton->setAutoExclusive(false); ui->mediaPrezziButton->setChecked(false); ui->mediaPrezziButton->setAutoExclusive(true);
    ui->ordinatiArticoliButton->setAutoExclusive(false); ui->ordinatiArticoliButton->setChecked(false); ui->ordinatiArticoliButton->setAutoExclusive(true);

    ui->tuttiArticoliRivistaButton->setAutoExclusive(false); ui->tuttiArticoliRivistaButton->setChecked(false); ui->tuttiArticoliRivistaButton->setAutoExclusive(true);
    ui->guadagnoRivistaButton->setAutoExclusive(false); ui->guadagnoRivistaButton->setChecked(false); ui->guadagnoRivistaButton->setAutoExclusive(true);
    ui->articoliOrdinatiButton->setAutoExclusive(false); ui->articoliOrdinatiButton->setChecked(false); ui->articoliOrdinatiButton->setAutoExclusive(true);

    ui->conferenzeSimiliButton->setAutoExclusive(false); ui->conferenzeSimiliButton->setChecked(false); ui->conferenzeSimiliButton->setAutoExclusive(true);
    ui->keywordButton->setAutoExclusive(false); ui->keywordButton->setChecked(false); ui->keywordButton->setAutoExclusive(true);
}

void MainWindow::on_SezioneA_clicked()
{
    ui->mainStacked->setCurrentWidget(ui->pageMain);
}

void MainWindow::on_SezioneB_clicked()
{
    svuotaTutto();
    disattivaRadioButton();
    ui->mainStacked->setCurrentWidget(ui->pageMetodiAutore);
    mostraTuttiAutori();
    hide2();
}

void MainWindow::on_SezioneC_clicked()
{
    svuotaTutto();
    disattivaRadioButton();
    ui->mainStacked->setCurrentWidget(ui->pageMetodiRivista);
    mostraTutteRiviste();
    hide3();
}

void MainWindow::on_SezioneD_clicked()
{
    svuotaTutto();
    disattivaRadioButton();
    ui->dinamicLabelMisto->setText("");
    ui->mainStacked->setCurrentWidget(ui->pageMetodiMisti);
    mostraTutteConferenze();
}

void MainWindow::on_pushButton_clicked()
{
    ui->listWidgetRecenti->clear();
    ui->mainStacked->setCurrentWidget(ui->pageFileInput);
}

void MainWindow::disattivaElementiChecked(QListWidgetItem* item)
{
    QListWidget* ptrList = item->listWidget();
    int idx = ptrList->row(item);
    //Se faccio check su ul elemento di una listWidget disattivo tutti gli altri

    for(int i = 0; i < ptrList->count(); i++)
        if(i != idx && ptrList->item(i)->checkState() == Qt::Checked)
            ptrList->item(i)->setCheckState(Qt::Unchecked);
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
    ui->lineEdit2->setPlaceholderText("Scrivi le keyword separate da virgola e massimo uno spazio");
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
            //Se l'autore è stato aggiunto con successo, modifico il listWidgetItem
            item->setText(author.getNome() + " " + author.getCognome());
            item->setIcon(QIcon(":/res/AutoreColor.png"));
            item->setCheckState(Qt::Unchecked);
            ui->widgetAutore->addItem(item);
            ui->statusBar->showMessage("Aggiunto !", 3000);
        }
    }
    else if(ui->ArticoloButton->isChecked())
    {
        if(gestore.getAutori().size() == 0 || (gestore.getConferenze().size() == 0 && gestore.getRiviste().size() == 0))
        {
            QMessageBox error(QMessageBox::Warning, "Impossibile aggiungere", "Non ci sono autori e/o riviste/conferenze sufficienti");
            error.exec();
        }
        else
        {
            Articolo article;
            article.setTitolo(ui->lineEdit1->text());
            QString keyword = ui->lineEdit2->text();
            article.addKeyword(keyword);
            article.setNumPagine(ui->spinBox->value());
            article.setPrezzo(ui->doubleSpinBox->value());
            if(gestore.aggiungiArticolo(article))
            {
                item->setText(article.getTitolo() + "        " + QString::number(article.getNumPagine()) + " pagine");
                item->setIcon(QIcon(":/res/ArticoloColor.png"));
                item->setCheckState(Qt::Unchecked);
                ui->widgetArticolo->addItem(item);
                itemDialog dialog(ui->widgetArticolo->count() - 1, cArticolo, &gestore, ui->widgetArticolo->item(ui->widgetArticolo->count() - 1));
                dialog.exec();
                ui->statusBar->showMessage("Aggiunto !", 3000);
            }
        }
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
            item->setText(conference.getNome() + "      " + QString::number(conference.getData().year()));
            item->setCheckState(Qt::Unchecked);
            item->setIcon(QIcon(":/res/ConferenzaColor.png"));
            ui->widgetConferenza->addItem(item);
            ui->statusBar->showMessage("Aggiunto !", 3000);
        }
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
            item->setText(paper.getNome() + "      " + QString::number(paper.getData().year()));
            item->setIcon(QIcon(":/res/RivistaColor.png"));
            item->setCheckState(Qt::Unchecked);
            ui->widgetRivista->addItem(item);
            ui->statusBar->showMessage("Aggiunto !", 3000);
        }
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
    //Capisco qual è la lista attiva tramite il current widget dello stackedWidget, che restituisce la pagina attiva

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
                delete itm->item(i);
                i--;
            }
        }
    }
    ui->bottoneRimuovi->setVisible(false);
}

void MainWindow::onWidgetDoubleClicked(QListWidgetItem* item)
{
    //Prendo il puntatore alla lista su cui è stata chiamata la funzione
    QListWidget* ptrList = qobject_cast <QListWidget*> (sender());

    int idx = 0;
    idx = ptrList->currentRow();

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

    if(idx != -1)
    {
        itemDialog dialog(idx, tipo, &gestore, item);
        dialog.setModal(true);
        dialog.exec();
    }
}



void MainWindow::svuotaTutto()
{
    ui->lineEditPrezzo->setText("");
    ui->guadagnoLineEdit->setText("");
    ui->annoSpinBox->setValue(0);
    ui->dinamicListWidget->clear();
    ui->dinamicListWidgetRivista->clear();
    ui->dinamicListWidgetMisto->clear();
}

//Bottone esegui della pagina "Ricerca Autore"
void MainWindow::on_eseguiButton_clicked()
{
    ui->dinamicListWidget->clear();

    //Cerco l'autore che è stato selezionato
    int idxChecked = -1;
    for(int i = 0; i < ui->tuttiAutoriListWidget->count(); i++)
    {
        if(ui->tuttiAutoriListWidget->item(i)->checkState() == Qt::Checked)
        {
            idxChecked = i;
            break;
        }
    }

    QList <Articolo*> listArticoli;
    if(idxChecked != -1)
    {
        listArticoli = gestore.getArticoliPerAutore(idxChecked);

        if(ui->tuttiArticoliButton->isChecked())
        {
            //Mostro tutti gli articoli di quell'autore
            for(int i = 0; i < listArticoli.size(); i++)
            {
                ui->dinamicListWidget->addItem(listArticoli [i]->getTitolo() + "       " + QString::number(listArticoli [i]->getNumPagine()) + " Pagine");
                ui->dinamicListWidget->item(i)->setIcon(QIcon(":/res/ArticoloColor.png"));
            }
        }
        else if(ui->mediaPrezziButton->isChecked())
        {
            double price = 0;
            for(int i = 0; i < listArticoli.size(); i++)
                price += listArticoli [i]->getPrezzo();

            if(listArticoli.size() != 0)
                price /= listArticoli.size();

            ui->lineEditPrezzo->setText(QString::number(price));
        }
        else if(ui->ordinatiArticoliButton->isChecked())
        {
            listArticoli = gestore.getArticoliPerAutoreSorted(idxChecked);
            for(int i = 0; i < listArticoli.size(); i++)
            {
                ui->dinamicListWidget->addItem(listArticoli [i]->getTitolo() + "        " + QString::number(listArticoli [i]->getEditorePubblicato()->getData().year()) +
                                               "        " + QString::number(listArticoli [i]->getPrezzo()) + " €");

                ui->dinamicListWidget->item(i)->setIcon(QIcon(":/res/ArticoloColor.png"));
            }
        }
        else if(ui->articoliInRivisteButton->isChecked())
        {
            //Prendo le riviste in cui un autore non ha pubblicato nulla
            QList <Base*> listRivistePubbicate = gestore.getRivisteNonPubblicateDaAutore(idxChecked);
            for(int i = 0; i < listRivistePubbicate.size(); i++)
            {
                ui->dinamicListWidget->addItem(listRivistePubbicate [i]->getNome() + "       " + QString::number(listRivistePubbicate [i]->getData().year()));
                ui->dinamicListWidget->item(i)->setIcon(QIcon(":res/RivistaColor.png"));
            }
        }
        else
        {
            QMessageBox msg(QMessageBox::Information, "Attenzione", "Devi selezionare un'opzione");
            msg.exec();
        }
    }
}

//Metodi per la grafica di Autore, servono a nascondere/settare gli elementi che servono
void MainWindow::hide2()
{
    ui->labelPrezzo->setVisible(false);
    ui->lineEditPrezzo->setVisible(false); ui->lineEditPrezzo->setReadOnly(true);
    ui->dinamicLabel->setVisible(false);
    ui->dinamicListWidget->setVisible(false); ui->dinamicListWidget->clear();
}

void MainWindow::on_tuttiArticoliButton_clicked()
{
    hide2();
    ui->dinamicLabel->setVisible(true);
    ui->dinamicLabel->setText("Tutti gli articoli dell'autore selezionato");
    ui->dinamicListWidget->setVisible(true);
}

void MainWindow::on_mediaPrezziButton_clicked()
{
    hide2();
    ui->labelPrezzo->setVisible(true);
    ui->lineEditPrezzo->setVisible(true);
}

void MainWindow::on_ordinatiArticoliButton_clicked()
{
    hide2();
    ui->dinamicLabel->setVisible(true);
    ui->dinamicLabel->setText("Articoli ordinati dell'autore selezionato");
    ui->dinamicListWidget->setVisible(true);
}

void MainWindow::on_articoliInRivisteButton_clicked()
{
    hide2();
    ui->dinamicLabel->setVisible(true);
    ui->dinamicLabel->setText("Riviste in cui l'autore non ha pubblicato articoli");
    ui->dinamicListWidget->setVisible(true);
}



//Sezione Riviste
void MainWindow::mostraTutteRiviste()
{
    ui->tutteRivisteListWidget->clear();
    auto listTutteRiviste = gestore.getRiviste();
    for(int i = 0; i < listTutteRiviste.size(); i++)
    {
        ui->tutteRivisteListWidget->addItem(listTutteRiviste [i]->getNome() + "      " + QString::number(listTutteRiviste [i]->getData().year()));
        ui->tutteRivisteListWidget->item(i)->setIcon(QIcon(":res/RivistaColor.png"));
        ui->tutteRivisteListWidget->item(i)->setCheckState(Qt::Unchecked);
    }
}

//Bottone Esegui della pagina "Ricerca Riviste"
void MainWindow::on_cercaButton_clicked()
{
    ui->dinamicListWidgetRivista->clear();

    //Cerco la rivista che è stata selezionata
    int idxChecked = -1;
    for(int i = 0; i < ui->tutteRivisteListWidget->count(); i++)
    {
        if(ui->tutteRivisteListWidget->item(i)->checkState() == Qt::Checked)
        {
            idxChecked = i;
            break;
        }
    }

    if(idxChecked != -1)
    {
        auto listArticoliDiRivista = gestore.getArticoliPerRivista(idxChecked);

        if(ui->tuttiArticoliRivistaButton->isChecked())
        {
            for(int i = 0; i < listArticoliDiRivista.size(); i++)
            {
                ui->dinamicListWidgetRivista->addItem(listArticoliDiRivista [i]->getTitolo() + "      " + QString::number(listArticoliDiRivista [i]->getNumPagine()) + " Pagine");
                ui->dinamicListWidgetRivista->item(i)->setIcon(QIcon(":res/ArticoloColor.png"));
            }
        }
        else if(ui->guadagnoRivistaButton->isChecked())
        {
            double guadagno = 0;
            int anno = gestore.getRiviste() [idxChecked]->getData().year();
            ui->annoSpinBox->setValue(anno);

            for(Articolo* art : listArticoliDiRivista)
                guadagno += art->getPrezzo();

            ui->guadagnoLineEdit->setText(QString::number(guadagno));
        }
        else if(ui->articoliOrdinatiButton->isChecked())
        {
            QList <Articolo*> listArticoliOrdinati = gestore.getArticoliPerRivistaSorted(idxChecked);
            for(int i = 0; i < listArticoliOrdinati.size(); i++)
            {
                ui->dinamicListWidgetRivista->addItem(listArticoliOrdinati [i]->getTitolo() + "       " + QString::number(listArticoliOrdinati [i]->getPrezzo()) + " €");
                ui->dinamicListWidgetRivista->item(i)->setIcon(QIcon(":res/ArticoloColor.png"));
            }
        }
        else
        {
            QMessageBox msg(QMessageBox::Information, "Attenzione", "Devi selezionare un'opzione");
            msg.exec();
        }
    }
}

void MainWindow::hide3()
{
    //Nasconde gli elementi grafici della sezione riviste
    ui->guadagnoLabel->setVisible(false); ui->guadagnoLineEdit->setVisible(false); ui->guadagnoLineEdit->setReadOnly(true);
    ui->annoLabel->setVisible(false); ui->annoSpinBox->setVisible(false); ui->annoSpinBox->setReadOnly(true);
    ui->dinamicLabelRivista->setVisible(false);
    ui->dinamicListWidgetRivista->setVisible(false); ui->dinamicListWidgetRivista->clear();
}

void MainWindow::on_tuttiArticoliRivistaButton_clicked()
{
    hide3();
    ui->dinamicLabelRivista->setVisible(true);
    ui->dinamicLabelRivista->setText("Tutti gli articoli pubblicati per la rivista ");
    ui->dinamicListWidgetRivista->setVisible(true);
}

void MainWindow::on_guadagnoRivistaButton_clicked()
{
    hide3();
    ui->guadagnoLabel->setVisible(true);
    ui->guadagnoLineEdit->setVisible(true);
    ui->annoLabel->setVisible(true);
    ui->annoSpinBox->setVisible(true);
}

void MainWindow::on_articoliOrdinatiButton_clicked()
{
    hide3();
    ui->dinamicLabelRivista->setVisible(true);
    ui->dinamicLabelRivista->setText("Articoli ordinati pubblicati per la rivista ");
    ui->dinamicListWidgetRivista->setVisible(true);
}



void MainWindow::mostraTutteConferenze()
{
    ui->tutteConferenzeListWidget->clear();
    auto tutteConferenze = gestore.getConferenze();
    for(int i = 0; i < tutteConferenze.size(); i++)
    {
        ui->tutteConferenzeListWidget->addItem(tutteConferenze [i]->getNome() + "      " + QString::number(tutteConferenze [i]->getData().year()));
        ui->tutteConferenzeListWidget->item(i)->setIcon(QIcon(":res/ConferenzaColor.png"));
        ui->tutteConferenzeListWidget->item(i)->setCheckState(Qt::Unchecked);
    }
}

//Bottone Esegui della pagina "Misto"
void MainWindow::on_eseguiButtonMisto_clicked()
{
    ui->dinamicListWidgetMisto->clear();

    int idxChecked = -1;
    for(int i = 0; i < ui->tutteConferenzeListWidget->count(); i++)
    {
        if(ui->tutteConferenzeListWidget->item(i)->checkState() == Qt::Checked)
        {
            idxChecked = i;
            break;
        }
    }

    if(ui->conferenzeSimiliButton->isChecked())
    {
        if(idxChecked != -1)
        {
            ui->dinamicLabelMisto->setText("Conferenze simili a quella selezionata");
            //Prendo la lista keyword della conferenza selezionata
            auto listKeywordConferenza = gestore.getKeywordConferenzaAt(idxChecked);
            int indexList = 0;

            for(int i = 0; i < gestore.getConferenze().size(); i++)
            {
                if(i != idxChecked)
                {
                    //Prendo la lista keyword della conferenza che sto verificando
                    auto listKeywordConferenzaSecondaria = gestore.getKeywordConferenzaAt(i);
                    if(gestore.areSimilar(listKeywordConferenza, listKeywordConferenzaSecondaria))
                    {
                        ui->dinamicListWidgetMisto->addItem(gestore.getConferenze() [i]->getNome() + "      " + QString::number(gestore.getConferenze()[i]->getData().year()));
                        ui->dinamicListWidgetMisto->item(indexList++)->setIcon(QIcon(":res/ConferenzaColor.png"));
                    }
                }
            }
        }
    }
    else if(ui->articoliPerConferenzaButton->isChecked())
    {
        if(idxChecked != -1)
        {
            ui->dinamicLabelMisto->setText("Articoli pubblicati per la conferenza");
            auto listArticoliPerConferenza = gestore.getArticoliPerConferenza(idxChecked);

            for(int i = 0; i < listArticoliPerConferenza.size(); i++)
            {
                ui->dinamicListWidgetMisto->addItem(listArticoliPerConferenza [i]->getTitolo() + "      " + QString::number(listArticoliPerConferenza [i]->getNumPagine()) + " Pagine");
                ui->dinamicListWidgetMisto->item(i)->setIcon(QIcon(":res/ArticoloColor.png"));
            }

        }
    }
    else if(ui->keywordButton->isChecked())
    {
        ui->dinamicLabelMisto->setText("Keyword la cui somma degli articoli porta al guadagno piu' alto");
        auto listTutteKeyword = gestore.getTutteKeyword();
        auto listGuadagnoPerKeyword = gestore.getGuadagnoPerKeyword(listTutteKeyword);
        //Nella seconda lista ho il guadagno di tutte le keyword
        double max = -1;

        for(double val : listGuadagnoPerKeyword)
            if(val > max)
                max = val;

        int idxList = 0;
        for(int i = 0; i < listTutteKeyword.size(); i++)
        {
            if(listGuadagnoPerKeyword [i] == max)
            {
                ui->dinamicListWidgetMisto->addItem("  Keyword:  " + listTutteKeyword [i] + "      " + QString::number(listGuadagnoPerKeyword [i]) + " €");
                ui->dinamicListWidgetMisto->item(idxList++)->setIcon(QIcon(":/res/ArticoloColor.png"));
            }
        }
    }
    else
    {
        QMessageBox msg(QMessageBox::Information, "Attenzione", "Devi selezionare un'opzione");
        msg.exec();
    }

}


//Serve per tokenizzare il file di testo preso da input
QList <QString> tokenizer(QString stringIniziale, char separator = '\n')
{
    if(stringIniziale.back() != separator)
        stringIniziale += separator;

    QList <QString> tokenizzata;
    int start = 0;
    int len = 0;
    for(int i = 0; i < stringIniziale.length(); i++)
    {
        if(stringIniziale [i] == separator)
        {
            tokenizzata.push_back(stringIniziale.mid(start, len));
            start = i+1;
            len = 0;
        }
        else
            len++;
    }

    tokenizzata.removeAll("");
    return tokenizzata;
}

bool controlloCheck(QList <QString>& tokenizzata, int nParametri)
{
    //nParametri è pari al numero di dati che ha un autore/conferenza ... a cui va aggiunto il "---" finale
    if(tokenizzata.size() >= (nParametri + 1) && tokenizzata [0].contains("---"))
    {
        tokenizzata.erase(tokenizzata.begin());
        return true;
    }

    return false;
}

bool MainWindow::inputAutoreValido(Articolo& nuovoArticolo, QString nomiAutori, QString nomePubblicato)
{
    //Questa funzione serve a controllare che i nomi degli autori e della conferenza/rivista di un articolo esistano
    QList <QString> listaNomiAutori = tokenizer(nomiAutori, ',');
    QList <Autore*> listaPuntatoriAutore;
    Base* ptrEditore = nullptr;
    for(int i = 0; i < listaNomiAutori.size(); i++)
    {
        for(Autore* ptrAutore : gestore.getAutori())
        {
            if((ptrAutore->getNome() + " " + ptrAutore->getCognome()).toLower() == listaNomiAutori [i].toLower())
            {
                listaPuntatoriAutore.push_back(ptrAutore);
                break;
            }
        }
    }

    //Tokenizzo la linea in due parti, la prima contiene il tipo per cui viene pubblicato un articolo : Rivista/Conferenza
    //La seconda contiene il nome
    QList <QString> tipoNomePubblicato = tokenizer(nomePubblicato, ',');

    if(tipoNomePubblicato [0].toUpper() == "CF")          //Controllo nelle conferenze
    {
        for(Base* ptrBase : gestore.getConferenze())
            if(ptrBase->getNome().toLower() == tipoNomePubblicato [1].toLower())
                ptrEditore = ptrBase;
    }
    else if(tipoNomePubblicato [0].toUpper() == "RV")         //Controllo nelle riviste
    {
        for(Base* ptrBase : gestore.getRiviste())
            if(ptrBase->getNome().toLower() == tipoNomePubblicato [1].toLower())
                ptrEditore = ptrBase;
    }

    if(listaPuntatoriAutore.size() == listaNomiAutori.size() && ptrEditore != nullptr)
    {
        nuovoArticolo.setListAutori(listaPuntatoriAutore);
        nuovoArticolo.setEditorePubblicato(ptrEditore);
        return true;
    }

    return false;

}

QDate getDataFromString(QString dateString)
{
    //La stringa di data deve essere formato GG/MM/AAAA
    int day = 0, month = 0, year = 0;
    day = dateString.mid(0,2).toInt();
    month = dateString.mid(3,2).toInt();
    year = dateString.mid(6,4).toInt();

    return QDate(year, month, day);
}


//Bottone leggi della sezione File
void MainWindow::on_leggiButton_clicked()
{
    QString path = ui->percorsoLineEdit->text();

    QFile file(path);

    //Apro il file in read only
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox msg(QMessageBox::Warning, "Errore", "Impossibile aprire il file");
        msg.exec();
        return;
    }

    QTextStream input(&file);
    QString testo = input.readAll();

    //Tokenizzo ogni linea del file
    QList <QString> tokenizzata = tokenizer(testo);
    QListWidgetItem* itemTemp;
    QListWidgetItem* item;
    bool check = true;
    bool elementoNonInserito = false;

    if(ui->autoreLeggiButton->isChecked())
    {
        while(check)
        {
            //Prendo dalla lista di tokenizzati i vari dati che mi servono, che saranno sempre nelle prime posizioni perché dopo rimuovo i dati inseriti
            Autore nuovo;
            nuovo.setNome(tokenizzata [0]);
            nuovo.setCognome(tokenizzata [1]);
            nuovo.addAfferenze(tokenizzata [2], ',');
            if(gestore.aggiungiAutore(nuovo, false))
            {
                item = new QListWidgetItem;
                itemTemp = new QListWidgetItem;

                item->setText(nuovo.getNome() + " " + nuovo.getCognome());
                item->setIcon(QIcon(":/res/AutoreColor.png"));
                item->setCheckState(Qt::Unchecked);
                ui->widgetAutore->addItem(item);

                itemTemp->setText(item->text());
                itemTemp->setIcon(item->icon());
                ui->listWidgetRecenti->addItem(itemTemp);
            }
            else
                elementoNonInserito = true;

            tokenizzata.erase(tokenizzata.begin(), tokenizzata.begin() + 3);
            check = controlloCheck(tokenizzata, 3);
        }
    }
    else if(ui->articoloLeggiButton->isChecked())
    {
        while(check)
        {
            Articolo nuovo;
            nuovo.setTitolo(tokenizzata [0]);
            nuovo.addKeyword(tokenizzata [1]);
            nuovo.setNumPagine(tokenizzata [2].toInt());
            nuovo.setPrezzo(tokenizzata [3].toDouble());
            if(inputAutoreValido(nuovo, tokenizzata [4], tokenizzata [5]))
            {
                if(gestore.aggiungiArticolo(nuovo, false))
                {
                    item = new QListWidgetItem;
                    itemTemp = new QListWidgetItem;

                    item->setText(nuovo.getTitolo() + "        " + QString::number(nuovo.getNumPagine()) + " pagine");
                    item->setIcon(QIcon(":/res/ArticoloColor.png"));
                    item->setCheckState(Qt::Unchecked);
                    ui->widgetArticolo->addItem(item);

                    itemTemp->setText(item->text());
                    itemTemp->setIcon(item->icon());
                    ui->listWidgetRecenti->addItem(itemTemp);
                 }
                else
                    elementoNonInserito = true;
            }
            else
                elementoNonInserito = true;

            tokenizzata.erase(tokenizzata.begin(), tokenizzata.begin() + 6);
            check = controlloCheck(tokenizzata, 6);
        }
    }
    else if(ui->conferenzaLeggiButton->isChecked())
    {
        while(check)
        {
            Conferenza nuovo;
            nuovo.setNome(tokenizzata [0]);
            nuovo.setAcronimo(tokenizzata [1]);
            nuovo.setLuogo(tokenizzata [2]);
            nuovo.addOrganizzatore(tokenizzata [3], ',');
            nuovo.setPartecipanti(tokenizzata [4].toInt());
            nuovo.setData(getDataFromString(tokenizzata [5]));

            if(gestore.aggiungiConferenza(nuovo, false))
            {
                item = new QListWidgetItem;
                itemTemp = new QListWidgetItem;

                item->setText(nuovo.getNome() + "      " + QString::number(nuovo.getData().year()));
                item->setIcon(QIcon(":/res/ConferenzaColor.png"));
                item->setCheckState(Qt::Unchecked);
                ui->widgetConferenza->addItem(item);

                itemTemp->setText(item->text());
                itemTemp->setIcon(item->icon());
                ui->listWidgetRecenti->addItem(itemTemp);
            }
            else
                elementoNonInserito = true;

            tokenizzata.erase(tokenizzata.begin(), tokenizzata.begin() + 6);
            check = controlloCheck(tokenizzata, 6);
        }
    }
    else if(ui->rivistaLeggiButton->isChecked())
    {
        while(check)
        {
            Rivista nuovo;
            nuovo.setNome(tokenizzata [0]);
            nuovo.setAcronimo(tokenizzata [1]);
            nuovo.setEditore(tokenizzata [2]);
            nuovo.setVolume(tokenizzata [3].toInt());
            nuovo.setData(getDataFromString(tokenizzata [4]));

            if(gestore.aggiungiRivista(nuovo, false))
            {
                item = new QListWidgetItem;
                itemTemp = new QListWidgetItem;

                item->setText(nuovo.getNome() + "      " + QString::number(nuovo.getData().year()));
                item->setIcon(QIcon(":/res/RivistaColor.png"));
                item->setCheckState(Qt::Unchecked);
                ui->widgetRivista->addItem(item);

                itemTemp->setText(item->text());
                itemTemp->setIcon(item->icon());
                ui->listWidgetRecenti->addItem(itemTemp);
            }
            else
                elementoNonInserito = true;

            tokenizzata.erase(tokenizzata.begin(), tokenizzata.begin() + 5);
            check = controlloCheck(tokenizzata, 5);
        }
    }
    else
    {
        QMessageBox msg(QMessageBox::Information, "Attenzione", "Devi selezionare un'opzione");
        msg.exec();
    }

    if(elementoNonInserito)
    {
        QMessageBox msg(QMessageBox::Warning, "Attenzione", "Uno o piu' elementi non sono stati inseriti perché già esistenti\n"
                                                            "oppure alcuni campi non sono validi");
        msg.exec();
    }

    file.flush();
    file.close();
}

void MainWindow::on_istruzioniButton_clicked()
{
    QString testo = "I dati devono essere scritti linea per linea e separati da --- per indicare un elemento diverso\n\n "
                    "Ad esempio un File valido per un articolo è il seguente : \n\n"
                    "Articolo1\nkeyword1,keyword2,keyword3\n"
                    "10                                                  (numero pagine)"
                    "\n18.90                                             (prezzo)"
                    "\nautore rossi,autore verdi               (autori)"
                    "\nCF,conferenza12                           (pubblicazione    Tipo,Nome)"
                    "\n---";

    QMessageBox msg(QMessageBox::Information, "Formato Valido", testo);
    msg.exec();
}

void MainWindow::on_infoProgButton_clicked()
{
    QString text = "Progetto singolo a cura di : Simone Ventrici\n"
                   "Matricola : 209714\n\n"
                   "Metodi implementati : \n"
                   "Sezione B : 1, 4, 5\n"
                   "Sezione C : 3, 5, 6\n"
                   "Sezione D : 4, 6\n"
                   "Sezione E : 2\n"
                   "Sezione F : 4, 5";

    QMessageBox msg(QMessageBox::Information, "Informazioni sul progetto", text);
    msg.exec();
}
