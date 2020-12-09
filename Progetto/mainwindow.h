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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Gestore.h"
#include <QDebug>
#include <QMessageBox>
#include <QListWidgetItem>
#include <itemDialog.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
            void on_SezioneA_clicked();
            void on_SezioneB_clicked();

            void on_AutoreButton_clicked();
            void on_ArticoloButton_clicked();
            void on_ConferenzaButton_clicked();
            void on_RivistaButton_clicked();
            void on_bottoneAggiungi_clicked();

            void onWidgetClicked();
            void onWidgetDoubleClicked(QListWidgetItem* item);

            void on_bottoneRimuovi_clicked();
            void onRimuoviItem(QListWidget* itm);


    signals:
            void widgetClicked(QListWidget* itm);
            void rimuoviItem(QListWidget* itm);


    private:
            Ui::MainWindow *ui;
            Gestore gestore;
            void hide();
            void svuotaLineEdit();
};

#endif // MAINWINDOW_H
