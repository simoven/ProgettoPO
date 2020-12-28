#include "itemDialog.h"
#include "ui_itemDialog.h"

itemDialog::itemDialog(int idx, classType tp, Gestore* ptr2, QListWidgetItem* itm, QWidget *parent) : QDialog(parent), ui(new Ui::itemDialog),
  author(nullptr), paper(nullptr), conference(nullptr), article(nullptr)
{
    //index è l'indice dell'elemento cliccato nella listWidget
    //listItem punta direttamente al listWidgetItem
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
    if(type == cArticolo)
        if(ptrGestore->getArticoli() [index]->getAutori().size() == 0 || ptrGestore->getArticoli() [index]->getEditorePubblicato() == nullptr)
            return;

    done(0);
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
    //Riempio i vari elementi grafici
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

void itemDialog::showArticolo()
{
    ui->itmLabel1->setText("Testo"); ui->itmLineEdit1->setText(article->getTitolo()); ui->itmLineEdit1->setVisible(true);
    ui->itmLabel2->setText("Identificativo"); ui->itmLineEdit2->setText(article->getIdentificativo()); ui->itmLineEdit2->setReadOnly(true);
    ui->itmLineEdit2->setVisible(true);

    ui->itmLabel3->setText("Keyword"); ui->itmLineEdit3->setVisible(true);
    ui->itmLabel4->setText("Nome editore"); ui->itmLineEdit4->setVisible(true); ui->itmLineEdit4->setReadOnly(true);

    if(article->getEditorePubblicato() != nullptr)
        ui->itmLineEdit4->setText(article->getEditorePubblicato()->getNome());
    else
        ui->itmLineEdit4->setText("* Nessuno *");

    ui->itmLabel5->setText("Pagine"); ui->itmSpinBox->setValue(article->getNumPagine()); ui->itmSpinBox->setVisible(true);
    ui->itmLabel6->setText("Prezzo"); ui->itmDoubleSpin->setValue(article->getPrezzo()); ui->itmDoubleSpin->setVisible(true);

    //Mostro le keyword dell'articolo nel line edit
    QString text = "";
    for(int i = 0; i < article->getKeyword().size(); i++)
    {
        text += article->getKeyword() [i];
        if(i != article->getKeyword().size() - 1)
            text += ",";
    }

    ui->itmLineEdit3->setText(text);

    ui->itmCombo4->addItem("Autori ");
    ui->itmCombo4->addItem("Articoli correlati");
    ui->itmCombo4->setCurrentIndex(0);
    ui->itmCombo4->setVisible(true);
    ui->stackedWidget->setCurrentWidget(ui->pageList);

    riempiLista(ui->itmCombo4->currentIndex());

    ui->itmLabel7->setText("Pubblicato per");
    ui->itmComboBox->setVisible(true);
    ui->itmComboBox->addItem("Nessuno");
    ui->itmComboBox->setCurrentIndex(0);

    //Questo serve a riempire il comboBox che mostra per chi ho pubblicato l'articolo
    QList <Conferenza*> listConf = ptrGestore->getConferenze();
    QList <Rivista*> listRivista = ptrGestore->getRiviste();

    //aggiungo tutte le conferenze
    for(int i = 0; i < listConf.size(); i++)
    {
        ui->itmComboBox->addItem(QIcon(":/res/ConferenzaColor.png"), listConf [i]->getNome());

        if(article->getEditorePubblicato() == listConf [i])
            ui->itmComboBox->setCurrentIndex(i+1);
    }


    //Aggiungo tutte le riviste
    for(int i = 0; i < listRivista.size(); i++)
    {
        ui->itmComboBox->addItem(QIcon(":/res/RivistaColor.png"), listRivista [i]->getNome());

        if(article->getEditorePubblicato() == listRivista [i])
            ui->itmComboBox->setCurrentIndex(listConf.size() + i + 1);
    }
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


void itemDialog::riempiLista(int option)
{
    //Questo serve a riempire la listWidget con gli autori o articoli correlati, in base a cosa ho cliccato
    ui->listWidget->clear();
    ui->itmPlainText->setPlainText("");

    if(option == 0) //Mostro gli autori
    {
        auto listAutori = article->getAutori();
        auto tuttiAutori = ptrGestore->getAutori();
        for(int i = 0; i < tuttiAutori.size(); i++)
        {
            ui->listWidget->addItem(tuttiAutori [i]->getNome() + " " + tuttiAutori [i]->getCognome());
            if(listAutori.contains(tuttiAutori [i]))
                ui->listWidget->item(i)->setCheckState(Qt::Checked);
            else
                ui->listWidget->item(i)->setCheckState(Qt::Unchecked);
        }
    }
    else //Mostro gli articoli correlati
    {
        auto listArticoli = article->getCorrelati();
        auto tuttiArticoli = ptrGestore->getArticoli();
        int contaElem = 0;
        for(int i = 0; i < tuttiArticoli.size(); i++)
        {
            //Controllo prima di non aggiungere l'articolo a se stesso
            if(i != index)
            {
                ui->listWidget->addItem(tuttiArticoli [i]->getTitolo());

                if(listArticoli.contains(tuttiArticoli [i]))
                    ui->listWidget->item(contaElem)->setCheckState(Qt::Checked);
                else
                    ui->listWidget->item(contaElem)->setCheckState(Qt::Unchecked);

                contaElem++;
            }
        }
    }
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


        if(ptrGestore->aggiungiAutore(temp, true, false, index, false))
            listItem->setText(temp.getNome() + " " + temp.getCognome());

    }
    else if(type == cArticolo)
    {
        Articolo articleTmp;
        articleTmp.setTitolo(ui->itmLineEdit1->text());
        articleTmp.addKeyword(ui->itmLineEdit3->text());
        articleTmp.setNumPagine(ui->itmSpinBox->value());
        articleTmp.setPrezzo(ui->itmDoubleSpin->value());
        QString x = ui->itmLineEdit2->text();
        articleTmp.setIdentificativo(x.toInt());

        int indexEditor = ui->itmComboBox->currentIndex();
        //La combobox dice per chi è stato pubblicato l'articolo

        if(indexEditor == 0)
            articleTmp.setEditorePubblicato(nullptr);
        else
        {
            //Se l'indice è maggiore della size delle conferenze vuol dire che ho selezionato una rivista
            if(indexEditor > ptrGestore->getConferenze().size())
                articleTmp.setEditorePubblicato(ptrGestore->getRiviste() [indexEditor - ptrGestore->getConferenze().size() - 1]);
            else
                articleTmp.setEditorePubblicato(ptrGestore->getConferenze()[indexEditor - 1]);
        }


        //Combo4 dice se sto mostrando la listWidget di autori o articoli correlati
        if(ui->itmCombo4->currentIndex() == 0) // prendo autori nella list widget e vedo a chi sono correlato
        {
            articleTmp.setListCorrelati(article->getCorrelati());
            for(int i = 0; i < ui->listWidget->count(); i++)
            {
                if(ui->listWidget->item(i)->checkState() == Qt::Checked)
                    articleTmp.addAutore(ptrGestore->getAutori() [i]);
            }
        }
        else // prendo articoli nella list widget e vedo a chi sono correlato
        {
            articleTmp.setListAutori(article->getAutori());
            int correctIdx = 0;
            for(int i = 0; i < ui->listWidget->count(); i++)
            {
                //Risolvo lo sfasamento tra gli indici della lista Articoli e del listWidget (poichè non considero l'articolo attuale)
                if(i == index)
                    correctIdx++;

                if(ui->listWidget->item(i)->checkState() == Qt::Checked)
                    articleTmp.addCorrelato(ptrGestore->getArticoli() [correctIdx]);

                correctIdx++;
            }
        }

       if(ptrGestore->aggiungiArticolo(articleTmp, true, false, index, false))
            listItem->setText(articleTmp.getTitolo() + "        " + QString::number(articleTmp.getNumPagine()) + " pagine");
       else
           return;

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


        if(ptrGestore->aggiungiConferenza(tmp, true, false, index))
            listItem->setText(tmp.getNome() + "      " + QString::number(tmp.getData().year()));
    }
    else
    {
        Rivista temp;
        temp.setNome(ui->itmLineEdit1->text());
        temp.setAcronimo(ui->itmLineEdit2->text());
        temp.setEditore(ui->itmLineEdit3->text());
        temp.setVolume(ui->itmSpinBox->value());
        temp.setData(ui->calendarWidget->selectedDate());


        if(ptrGestore->aggiungiRivista(temp, true, false, index))
            listItem->setText(temp.getNome() + "      " + QString::number(temp.getData().year()));
    }
    done(0);
}

