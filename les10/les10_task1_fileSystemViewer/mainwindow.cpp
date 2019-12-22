#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTimer>
#include <QDebug>
#include <QProcess>
/*В просмотрщик файлов добавить таймер, который будет проверять изменение списка дисков.
 *Если список дисков изменился, нужно запустить поток, который будет искать файл конфигурации
 * (произвольного формата, можно использовать autorun.inf), содержащий путь к приложению для запуска.
 * Для проверки подключить флеш-карту к ПК: при срабатывании таймера поток должен искать файл конфигурации на ней.
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *updDiskTime = new QTimer(this);
    connect(updDiskTime, SIGNAL(timeout()), this, SLOT(updateListDisks()));
    updDiskTime->start(5000);
    QFileInfoList diskLst = QDir::drives();
    for (auto disk : diskLst)
    {
        disksList.append(disk.absolutePath());
    }
    disksLstSize = disksList.size()-1;
    controllerl = new Controller(this);
    connect(controllerl, SIGNAL(changFindPath(QString)), this, SLOT(changStatusLabel(QString)));
    connect(controllerl, SIGNAL(genPathOfFile(QString)), this, SLOT(printFindFile(QString)));
    //connect(controllerl, SIGNAL((newFind())), infoText, SLOT(clear()));

    te = ui->plainTextEdit;
    te2 = ui->plainTextEdit_2;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateListDisks()
{
    QFileInfoList diskLst = QDir::drives();
    bool isFound = false;
    if (disksLstSize < diskLst.size()-1)
    {
        for (auto disk : diskLst)
        {
            isFound = false;
            for (auto oldDisk : disksList)
                if (disk == oldDisk)
                    isFound = true;
            if (!isFound)
            {
                controllerl->startFind(disk.absolutePath(), "autorun.inf");
                disksList.append(disk.absolutePath());
            }
        }
        disksLstSize = disksList.size()-1;
    }
    else if (disksLstSize > diskLst.size()-1)
    {
        for (auto disk : diskLst)
        {
            disksList.clear();
            disksList.append(disk.absolutePath());
        }
    }
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

void MainWindow::changStatusLabel(QString line)
{
   //qDebug() << line;
}

void MainWindow::printFindFile(QString str)
{
    qDebug() << str;
    QFile file (str);

    if (file.open(QIODevice::ReadOnly))
    {
        QProcess *p = new QProcess(this);
        QByteArray byteArray = file.readAll(); // считываем весь файл
        QString cmd = tr(byteArray.data());
        p->start(cmd);
        file.close();
    }
}
