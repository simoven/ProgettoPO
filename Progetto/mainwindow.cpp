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

    ui->label4->setText("Autori"); ui->plainText->setVisible(true);
    ui->plainText->setPlaceholderText("Scrivi un autore per riga");
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
        //Aggiungo \n altrimenti la tokenizzazione non prende l'ultima stringa
        text += '\n';
        int len = 0;
        int idx = 0;
        //Tokenizzo il plain text
        for(int i = 0; i < text.length(); i++)
        {
            if(text [i] == '\n')
            {
                author.addAfferenze(text.mid(idx, len));
                idx = i+1;
                len = 0;
            }
            else
                len++;
        }

        gestore.aggiungiAutore(author);
        item->setText(author.getNome() + " " + author.getCognome());
        item->setIcon(QIcon(":/res/AutoreColor.png"));
        item->setCheckState(Qt::Unchecked);
        ui->widgetAutore->addItem(item);

    }
    else if(ui->ArticoloButton->isChecked())
    {
        Articolo article;
        article.setTitolo(ui->lineEdit1->text());
        QString keyword = ui->lineEdit2->text();
        keyword += ',';
        QString autori = ui->plainText->toPlainText();
        autori += '\n';

        //Tokenizzo le keyword
        int len = 0;
        int idx = 0;
        for(int i = 0; i < keyword.length(); i++)
        {
            if(keyword [i] == ',')
            {
                article.addKeyword(keyword.mid(idx, len));
                idx = i+1;
                len = 0;
            }
            else
                len++;
        }

        //Tokenizzo il plain text
        len = 0;
        idx = 0;
        for(int i = 0; i < autori.length(); i++)
        {
            if(autori [i] == '\n')
            {
                article.addAutore(autori.mid(idx, len));
                idx = i+1;
                len = 0;
            }
            else
                len++;
        }

        article.setNumPagine(ui->spinBox->value());
        article.setPrezzo(ui->doubleSpinBox->value());
        gestore.aggiungiArticolo(article);
        item->setText(article.getTitolo());
        item->setIcon(QIcon(":/res/ArticoloColor.png"));
        item->setCheckState(Qt::Unchecked);
        ui->widgetArticolo->addItem(item);

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
        organizzatori += 'n';

        //Tokenizzo gli organizzatori
        int len = 0;
        int idx = 0;
        for(int i = 0; i < organizzatori.length(); i++)
        {
            if(organizzatori [i] == '\n')
            {
                conference.addOrganizzatore(organizzatori.mid(idx, len));
                idx = i+1;
                len = 0;
            }
            else
                len++;
        }

        item->setText(conference.getNome());
        item->setCheckState(Qt::Unchecked);
        item->setIcon(QIcon(":/res/ConferenzaColor.png"));
        gestore.aggiungiConferenza(conference);
        ui->widgetConferenza->addItem(item);

    }
    else if(ui->RivistaButton->isChecked())
    {
        Rivista paper;
        paper.setNome(ui->lineEdit1->text());
        paper.setAcronimo(ui->lineEdit2->text());
        paper.setEditore(ui->lineEdit3->text());
        paper.setVolume(ui->spinBox->value());
        paper.setData(ui->calendarWidget->selectedDate());
        gestore.aggiungiRivista(paper);
        item->setText(paper.getNome());
        item->setIcon(QIcon(":/res/RivistaColor.png"));
        item->setCheckState(Qt::Unchecked);
        ui->widgetRivista->addItem(item);

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
