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
            //showConferenza();
            break;

        case cRivista:
            paper = ptrGestore->getRiviste() [idx];
            ui->picLabel->setPixmap(QPixmap(":/res/RivistaColor.png").scaled(width, height, Qt::KeepAspectRatio));
            ui->tipoLabel->setText("   Rivista");
            //showRivista();
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
}

void itemDialog::showAutore()
{
    ui->itmLabel1->setText("Nome"); ui->itmLineEdit1->setText(author->getNome()); ui->itmLineEdit1->setVisible(true);
    ui->itmLabel2->setText("Cognome"); ui->itmLineEdit2->setText(author->getCognome()); ui->itmLineEdit2->setVisible(true);
    ui->itmLabel3->setText("Identificativo"); ui->itmLineEdit3->setText(author->getIdentificativo()); ui->itmLineEdit3->setReadOnly(true);
    ui->itmLineEdit3->setVisible(true);

    ui->itmCombo4->setVisible(true); ui->itmCombo4->addItem("Afferenze");
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
    ui->itmLabel4->setText("Nome editore"); ui->itmLineEdit4->setText(article->getNomePubblicato()); ui->itmLineEdit4->setVisible(true);
    ui->itmLabel5->setText("Pagine"); ui->itmSpinBox->setValue(article->getNumPagine()); ui->itmSpinBox->setVisible(true);
    ui->itmLabel6->setText("Prezzo"); ui->itmDoubleSpin->setValue(article->getPrezzo()); ui->itmDoubleSpin->setVisible(true);

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
    ui->itmPlainText->setVisible(true);
    for(int i = 0; i < article->getAutori().size(); i++)
        ui->itmPlainText->appendPlainText(article->getAutori()[i]);

    ui->itmLabel7->setText("Pubblicato per");
    ui->itmComboBox->addItem("Conferenza");
    ui->itmComboBox->addItem("Rivista");
    ui->itmComboBox->setVisible(true);
    ui->itmComboBox->setCurrentIndex(article->getPubblicato());
}

void itemDialog::on_itmCombo4_currentIndexChanged(int index)
{
    if(type == cArticolo)
    {
        if(index == 0)
        {
            ui->itmPlainText->setPlainText("");
            for(int i = 0; i < article->getAutori().size(); i++)
                ui->itmPlainText->appendPlainText(article->getAutori()[i]);
        }
        else if(index == 1)
        {
            ui->itmPlainText->setPlainText("");
            for(int i = 0; i < article->getCorrelati().size(); i++)
                ui->itmPlainText->appendPlainText(article->getCorrelati()[i]);
        }
     }
}



void itemDialog::on_bottoneModifica_clicked()
{
    if(type == cAutore)
    {
        Autore temp;
        temp.setNome(ui->itmLineEdit1->text());
        temp.setCognome(ui->itmLineEdit2->text());
        QString text = ui->itmPlainText->toPlainText();
        text += '\n';
        int len = 0;
        int idx = 0;
        //Tokenizzo il plain text
        for(int i = 0; i < text.length(); i++)
        {
            if(text [i] == '\n')
            {
                temp.addAfferenze(text.mid(idx, len));
                idx = i+1;
                len = 0;
            }
            else
                len++;
        }

        if(ptrGestore->aggiungiAutore(temp))
        {
            ptrGestore->rimuoviAutore(index);
            listItem->setText(temp.getNome() + " " + temp.getCognome());
        }
        else
            errorMsg();
    }
}

