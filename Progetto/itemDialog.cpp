#include "itemDialog.h"
#include "ui_itemDialog.h"

itemDialog::itemDialog(int idx, classType tp, Gestore* ptr2, QListWidgetItem* itm, QWidget *parent) : QDialog(parent), ui(new Ui::itemDialog),
  author(nullptr), paper(nullptr), conference(nullptr), article(nullptr)
{
    ui->setupUi(this);
    hide();
    listItem = itm;
    type = tp;
    index = idx;
    ptrGestore = ptr2;
    int height = ui->picLabel->height();
    int width = ui->picLabel->width();

    switch (type)
    {
        case cAutore:
            author = ptrGestore->getAutori() [idx];
            ui->picLabel->setPixmap(QPixmap(":/res/AutoreColor.png").scaled(width, height, Qt::KeepAspectRatio));
            ui->tipoLabel->setText("   Autore");
            showAutore();
            break;

        case cArticolo:
            article = ptrGestore->getArticoli() [idx];
            ui->picLabel->setPixmap(QPixmap(":/res/ArticoloColor.png").scaled(width, height, Qt::KeepAspectRatio));
            ui->tipoLabel->setText("   Articolo");
            showArticolo();
            break;

        case cConferenza:
            conference = ptrGestore->getConferenze() [idx];
            ui->picLabel->setPixmap(QPixmap(":/res/ConferenzaColor.png").scaled(width, height, Qt::KeepAspectRatio));
            ui->tipoLabel->setText("   Conferenza");
            showConferenza();
            break;

        case cRivista:
            paper = ptrGestore->getRiviste() [idx];
            ui->picLabel->setPixmap(QPixmap(":/res/RivistaColor.png").scaled(width, height, Qt::KeepAspectRatio));
            ui->tipoLabel->setText("   Rivista");
            showRivista();
            break;
    }

}

itemDialog::~itemDialog()
{
    delete ui;
}

void itemDialog::on_bottoneIndietro_clicked()
{
    done(0);
}

void errorMsg()
{
    //Significa che è già presente oppure alcuni campi sono vuoti
    QMessageBox msg(QMessageBox::Warning, "Impossibile aggiungere", "Elemento già presente oppure alcuni campi obbligatori sono vuoti");
    msg.exec();
}

void itemDialog::hide()
{
    ui->itmLineEdit1->setVisible(false);
    ui->itmLineEdit2->setVisible(false);
    ui->itmLineEdit3->setVisible(false);
    ui->itmLineEdit4->setVisible(false);
    ui->itmPlainText->setVisible(false);
    ui->itmSpinBox->setVisible(false);
    ui->itmDoubleSpin->setVisible(false);
    ui->itmCombo4->setVisible(false);
    ui->itmComboBox->setVisible(false);
    ui->calendarWidget->setVisible(false);
    ui->listWidget->clear();
    ui->itmPlainText->setPlainText("");
}

void itemDialog::showAutore()
{
    ui->itmLabel1->setText("Nome"); ui->itmLineEdit1->setText(author->getNome()); ui->itmLineEdit1->setVisible(true);
    ui->itmLabel2->setText("Cognome"); ui->itmLineEdit2->setText(author->getCognome()); ui->itmLineEdit2->setVisible(true);
    ui->itmLabel3->setText("Identificativo"); ui->itmLineEdit3->setText(author->getIdentificativo()); ui->itmLineEdit3->setReadOnly(true);
    ui->itmLineEdit3->setVisible(true);

    ui->itmCombo4->setVisible(true); ui->itmCombo4->addItem("Afferenze");
    ui->stackedWidget->setCurrentWidget(ui->pageText);
    ui->itmPlainText->setVisible(true);
    for(int i = 0; i < author->getAfferenze().size(); i++)
        ui->itmPlainText->appendPlainText(author->getAfferenze()[i]);
}


void itemDialog::riempiLista(int option)
{
    ui->listWidget->clear();
    ui->itmPlainText->setPlainText("");
    Articolo* ptrArt = ptrGestore->getArticoli() [index];
    if(option == 0) //Autori
    {
        QList <Autore*> listAutori = ptrArt->getAutori();
        QList <Autore*> tuttiAutori = ptrGestore->getAutori();
        for(int i = 0; i < tuttiAutori.size(); i++)
        {
            ui->listWidget->addItem(tuttiAutori [i]->getNome() + " " + tuttiAutori [i]->getCognome());
            if(listAutori.contains(tuttiAutori [i]))
                ui->listWidget->item(i)->setCheckState(Qt::Checked);
            else
                ui->listWidget->item(i)->setCheckState(Qt::Unchecked);
        }
    }
    else //Articoli correlati
    {
        QList <Articolo*> listArticoli = ptrArt->getCorrelati();
        QList <Articolo*> tuttiArticoli = ptrGestore->getArticoli();
        for(int i = 0; i < tuttiArticoli.size(); i++)
        {
            //Controllo prima di non aggiungere l'articolo a se stesso
            if(article != tuttiArticoli [i])
            {
                ui->listWidget->addItem(tuttiArticoli [i]->getTitolo());
                if(listArticoli.contains(tuttiArticoli [i]))
                    ui->listWidget->item(i)->setCheckState(Qt::Checked);
                else
                    ui->listWidget->item(i)->setCheckState(Qt::Unchecked);
            }
        }

    }
}

void itemDialog::showArticolo()
{
    ui->itmLabel1->setText("Testo"); ui->itmLineEdit1->setText(article->getTitolo()); ui->itmLineEdit1->setVisible(true);
    ui->itmLabel2->setText("Identificativo"); ui->itmLineEdit2->setText(article->getIdentificativo()); ui->itmLineEdit2->setReadOnly(true);
    ui->itmLineEdit2->setVisible(true);

    ui->itmLabel3->setText("Keyword"); ui->itmLineEdit3->setVisible(true);
    ui->itmLabel4->setText("Nome editore"); ui->itmLineEdit4->setText(article->getNomePubblicato()); ui->itmLineEdit4->setVisible(true);
    ui->itmLabel5->setText("Pagine"); ui->itmSpinBox->setValue(article->getNumPagine()); ui->itmSpinBox->setVisible(true);
    ui->itmLabel6->setText("Prezzo"); ui->itmDoubleSpin->setValue(article->getPrezzo()); ui->itmDoubleSpin->setVisible(true);

    //Mostro le keyword nel line edit
    QString text = "";
    for(int i = 0; i < article->getKeyword().size(); i++)
    {
        text += article->getKeyword() [i];
        if(i != article->getKeyword().size() - 1)
            text += ",";
    }

    ui->itmLineEdit3->setText(text);

    ui->itmCombo4->addItem("Autori");
    ui->itmCombo4->addItem("Correlati");
    ui->itmCombo4->setCurrentIndex(0);
    ui->itmCombo4->setVisible(true);
    ui->stackedWidget->setCurrentWidget(ui->pageList);
    riempiLista(ui->itmCombo4->currentIndex());

    ui->itmLabel7->setText("Pubblicato per");
    ui->itmComboBox->addItem("Conferenza");
    ui->itmComboBox->addItem("Rivista");
    ui->itmComboBox->setVisible(true);
    ui->itmComboBox->setCurrentIndex(article->getPubblicato());
}

void itemDialog::showConferenza()
{
    ui->itmLabel1->setText("Nome"); ui->itmLineEdit1->setVisible(true); ui->itmLineEdit1->setText(conference->getNome());
    ui->itmLabel2->setText("Acronimo"); ui->itmLineEdit2->setVisible(true); ui->itmLineEdit2->setText(conference->getAcronimo());
    ui->itmLabel3->setText("Luogo"); ui->itmLineEdit3->setVisible(true); ui->itmLineEdit3->setText(conference->getLuogo());
    ui->itmCombo4->addItem("Organizzatori"); ui->itmCombo4->setVisible(true);
    ui->itmCombo4->setCurrentIndex(0);

    for(int i = 0; i < conference->getOrganizzatori().size(); i++)
        ui->itmPlainText->appendPlainText(conference->getOrganizzatori() [i]);

    ui->stackedWidget->setCurrentWidget(ui->pageText);
    ui->itmPlainText->setVisible(true);
    ui->itmLabel5->setText("Partecipanti"); ui->itmSpinBox->setVisible(true); ui->itmSpinBox->setValue(conference->getPartecipanti());
    ui->calendarWidget->setVisible(true); ui->calendarWidget->setSelectedDate(conference->getData());
}

void itemDialog::showRivista()
{
    ui->itmLabel1->setText("Nome"); ui->itmLineEdit1->setVisible(true); ui->itmLineEdit1->setText(paper->getNome());
    ui->itmLabel2->setText("Acronimo"); ui->itmLineEdit2->setVisible(true); ui->itmLineEdit2->setText(paper->getAcronimo());
    ui->itmLabel3->setText("Editore"); ui->itmLineEdit3->setVisible(true); ui->itmLineEdit3->setText(paper->getEditore());
    ui->itmLabel5->setText("Volume"); ui->itmSpinBox->setVisible(true); ui->itmSpinBox->setValue(paper->getVolume());
    ui->calendarWidget->setVisible(true); ui->calendarWidget->setSelectedDate(paper->getData());
    ui->listWidget->setVisible(false);
}


void itemDialog::on_itmCombo4_currentIndexChanged(int index)
{
    if(type == cArticolo)
        riempiLista(index);
}



void itemDialog::on_bottoneModifica_clicked()
{
    if(type == cAutore)
    {
        Autore temp;
        temp.setNome(ui->itmLineEdit1->text());
        temp.setCognome(ui->itmLineEdit2->text());
        temp.addAfferenze(ui->itmPlainText->toPlainText());
        QString x = ui->itmLineEdit3->text();
        temp.setIdentificativo(x.toInt());


        if(ptrGestore->aggiungiAutore(temp, false))
        {
            ptrGestore->rimuoviAutore(index);
            listItem->setText(temp.getNome() + " " + temp.getCognome());
        }
        else
            errorMsg();
    }
    else if(type == cArticolo)
    {
        Articolo article;
        article.setTitolo(ui->itmLineEdit1->text());
        article.addKeyword(ui->itmLineEdit3->text());
        article.setNomePubblicato(ui->itmLineEdit4->text());
        article.setNumPagine(ui->itmSpinBox->value());
        article.setPrezzo(ui->itmDoubleSpin->value());
        article.setTipo(static_cast<Tipo> (ui->itmComboBox->currentIndex()));
        QString x = ui->itmLineEdit2->text();
        article.setIdentificativo(x.toInt());

        if(ui->itmCombo4->currentIndex() == 0) // mostro autori
        {
            for(int i = 0; i < ui->listWidget->count(); i++)
            {
                if(ui->listWidget->item(i)->checkState() == Qt::Checked)
                {
                    article.addAutore(ptrGestore->getAutori() [i]);
                    ptrGestore->getAutori() [i]->setIsCorrelato(true);
                }
                else
                    ptrGestore->getAutori() [i]->setIsCorrelato(false);
            }
        }
        else //Mostro articoli
        {
            for(int i = 0; i < ui->listWidget->count(); i++)
            {
                if(ui->listWidget->item(i)->checkState() == Qt::Checked)
                {
                    article.addCorrelato(ptrGestore->getArticoli() [i]);
                    ptrGestore->getArticoli() [i]->setIsCorrelato(true);
                }
                else
                    ptrGestore->getArticoli() [i]->setIsCorrelato(false);
            }
        }

        if(ptrGestore->aggiungiArticolo(article, false))
        {
            ptrGestore->rimuoviArticolo(index);
            listItem->setText(article.getTitolo());
        }
        else
            errorMsg();
    }
    else if(type == cConferenza)
    {
        Conferenza tmp;
        tmp.setNome(ui->itmLineEdit1->text());
        tmp.setAcronimo(ui->itmLineEdit2->text());
        tmp.setLuogo(ui->itmLineEdit3->text());
        tmp.setPartecipanti(ui->itmSpinBox->value());
        tmp.setData(ui->calendarWidget->selectedDate());
        tmp.addOrganizzatore(ui->itmPlainText->toPlainText());

        if(ptrGestore->aggiungiConferenza(tmp))
        {
            ptrGestore->rimuoviConferenza(index);
            listItem->setText(tmp.getNome());
        }
        else
            errorMsg();
    }
    else
    {
        Rivista temp;
        temp.setNome(ui->itmLineEdit1->text());
        temp.setAcronimo(ui->itmLineEdit2->text());
        temp.setEditore(ui->itmLineEdit3->text());
        temp.setVolume(ui->itmSpinBox->value());
        temp.setData(ui->calendarWidget->selectedDate());

        if(ptrGestore->aggiungiRivista(temp))
        {
            ptrGestore->rimuoviRivista(index);
            listItem->setText(paper->getNome());
        }
        else
            errorMsg();

    }
}

