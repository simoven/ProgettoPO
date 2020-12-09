#include "itemDialog.h"
#include "ui_itemDialog.h"

itemDialog::itemDialog(int idx, classType tp, Gestore* ptr2, QListWidgetItem* itm, QWidget *parent) : QDialog(parent), ui(new Ui::itemDialog),
  author(nullptr), paper(nullptr), conference(nullptr), article(nullptr)
{
    ui->setupUi(this);
    hide();
    QListWidgetItem* listItem = itm;
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
            break;

        case cConferenza:
            conference = ptrGestore->getConferenze() [idx];
            ui->picLabel->setPixmap(QPixmap(":/res/ConferenzaColor.png").scaled(width, height, Qt::KeepAspectRatio));
            ui->tipoLabel->setText("   Conferenza");
            break;

        case cRivista:
            paper = ptrGestore->getRiviste() [idx];
            ui->picLabel->setPixmap(QPixmap(":/res/RivistaColor.png").scaled(width, height, Qt::KeepAspectRatio));
            ui->tipoLabel->setText("   Rivista");
            break;
    }

}

void itemDialog::hide()
{
    ui->itmLineEdit1->setVisible(false);
    ui->itmLineEdit2->setVisible(false);
    ui->itmLineEdit3->setVisible(false);
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
    ui->itmCombo4->addItem("Afferenze "); ui->itmCombo4->setVisible(true);
    ui->itmPlainText->setVisible(true);
    for(int i = 0; i < author->getAfferenze().size(); i++)
        ui->itmPlainText->appendPlainText(author->getAfferenze()[i]);
}

itemDialog::~itemDialog()
{
    delete ui;
}

void itemDialog::on_bottoneIndietro_clicked()
{
    done(0);
}
