#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QProcess>

/* Написать планировщик запуска приложений по нажатию клавиши.
 * Программа должна иметь возможность редактировать кнопки на форме и программу,
 * которая будет запускаться по нажатию этих кнопок.
Создать файл начальных настроек, содержащий путь к исполняемому файлу, и клавишу,
которая будет запускать приложения, например calc F3 (при нажатии клавиши F3 произвести запуск калькулятора).
Для изменения настроек открыть файл и произвести заполнение структуры,
после чего сохранить файл и при запуске программы считывать его.
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItem("F1");
    ui->comboBox->addItem("F2");
    ui->comboBox->addItem("F3");
    ui->comboBox->addItem("F4");
    ui->comboBox->addItem("F5");

    ui->comboBox_2->addItem("calc");
    ui->comboBox_2->addItem("mspaint");
    ui->comboBox_2->addItem("dxdiag");
    ui->comboBox_2->addItem("notepad");
    key = ui->comboBox->currentText();
    program = ui->comboBox_2->currentText();

    connect(this, SIGNAL(signal__cmd()), this, SLOT(slot__cmd()));

    QFile file ("./last.txt");
    QString s;
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray byteArray = file.readAll();
        s = tr(byteArray.data());
        file.close();
    }
    if (s != "")
    {
       QStringList l = s.split(" ");

       if (l.at(0) == "F1")
           ui->comboBox->setCurrentIndex(0);
       if (l.at(0) == "F2")
           ui->comboBox->setCurrentIndex(1);
       if (l.at(0) == "F3")
           ui->comboBox->setCurrentIndex(2);
       if (l.at(0) == "F4")
           ui->comboBox->setCurrentIndex(3);
       if (l.at(0) == "F5")
           ui->comboBox->setCurrentIndex(4);
       key = l.at(0);
       if (l.at(1) == "calc")
           ui->comboBox_2->setCurrentIndex(0);
       if (l.at(1) == "mspaint")
           ui->comboBox_2->setCurrentIndex(1);
       if (l.at(1) == "dxdiag")
           ui->comboBox_2->setCurrentIndex(2);
       if (l.at(1) == "notepad")
           ui->comboBox_2->setCurrentIndex(3);
       program = l.at(1);
    }
}

MainWindow::~MainWindow()
{
    QFile file ("./last.txt");

    if (file.open(QIODevice::WriteOnly))
    {
        QString s = key + " " + program;
        QByteArray barr = s.toUtf8();
        file.write(barr, barr.length());
        file.close();
    }
    delete ui;
}


void MainWindow::on_comboBox_activated(const QString &arg1)
{
  if (arg1 == "F1")
  {
    key = "F1";
  }
  if (arg1 == "F2")
  {
    key = "F2";
  }
  if (arg1 == "F3")
  {
    key = "F3";
  }
  if (arg1 == "F4")
  {
    key = "F4";
  }
  if (arg1 == "F5")
  {
    key = "F5";
  }
}

void MainWindow::on_comboBox_2_activated(const QString &arg1)
{
    if (arg1 == "calc")
    {
        program = "calc";
    }
    if (arg1 == "mspaint")
    {
        program = "mspaint";
    }
    if (arg1 == "dxdiag")
    {
        program = "dxdiag";
    }
    if (arg1 == "notepad")
    {
        program = "notepad";
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_F1 && key == "F1")
    {
        emit signal__cmd();
    }
    if (event->key() == Qt::Key_F2 && key == "F2")
    {
        emit signal__cmd();
    }
    if (event->key() == Qt::Key_F3 && key == "F3")
    {
        emit signal__cmd();
    }
    if (event->key() == Qt::Key_F4 && key == "F4")
    {
        emit signal__cmd();
    }
    if (event->key() == Qt::Key_F5 && key == "F5")
    {
        emit signal__cmd();
    }
}

void MainWindow::slot__cmd()
{

    if(QSysInfo::productType()=="osx")
    {
        if (program == "calc")
        {
            QString PROGRAM_NAME = "open /Applications/Calculator.app";
            QProcess::startDetached( PROGRAM_NAME );
        }
    }
    else if(QSysInfo::productType()=="windows")
    {
        QString PROGRAM_NAME = program;
        QProcess::startDetached( PROGRAM_NAME );

    }
    else
    {
        QString PROGRAM_NAME = program;
        QProcess::startDetached( PROGRAM_NAME );
    }
}
