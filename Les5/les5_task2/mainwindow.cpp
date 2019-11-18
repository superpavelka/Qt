#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_plainTextEdit_textChanged()
{
    QDir dir(ui->plainTextEdit->toPlainText());
    QFileInfoList list = dir.entryInfoList();
    QString result = "";
    for (QFileInfoList::iterator iter = list.begin(),
         end = list.end(); iter < end; iter++)
    {
        result += (*iter).fileName() + "\n";
    }
    ui->plainTextEdit_2->setPlainText(result);
}

void MainWindow::on_pushButton_clicked()
{
    QFileDialog dialog;
    QString path;
    dialog.setFileMode(QFileDialog::Directory);
    if(dialog.exec()) {
            path = dialog.getExistingDirectory();
            ui->plainTextEdit->setPlainText(path);
            QDir dir(path);
            dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks | QDir::Dirs);
            QFileInfoList list = dir.entryInfoList();
            QString result = "";
            for (QFileInfoList::iterator iter = list.begin(),
                 end = list.end(); iter < end; iter++)
            {
                result += (*iter).fileName() + "\n";
            }
            ui->plainTextEdit_2->setPlainText(result);

        }
}
