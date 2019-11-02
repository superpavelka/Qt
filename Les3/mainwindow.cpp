#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

/*
1.Написать текстовый редактор с возможностью отмены изменений. Информацию об изменениях хранить в контейнере.
2.Добаить в текстовый редактор файл описания. Текстовый файл с описанием разместить в ресурсах программы.
Для вызова описания разместить на форме соответствующую кнопку.
3.Добавить в редактор возможность сохранить содержимое текстового поля.
Если оно сохраняется в бинарный файл, сохранять имя автора, разместив поле QLineEdit,
а в тестовом виде запись в этом поле игнорировать.
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->plainTextEdit_2->setReadOnly(true);

    QFile file ("./lasttext.txt");
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray byteArray = file.readAll(); // считываем весь файл
        ui->plainTextEdit->setPlainText(tr(byteArray.data()));
        ui->plainTextEdit_2->setPlainText("lasttext.txt");
        file.close();
    }
}

MainWindow::~MainWindow()
{
    QFile file ("./lasttext.txt");

    if (file.open(QIODevice::WriteOnly))
    {
        QString s = ui->plainTextEdit->toPlainText();
        QByteArray barr = s.toUtf8();          // преобразуем строку в
                                               // последовательность байт
                                               // кодировка текста UTF-8
        file.write(barr, barr.length());       // записываем
        file.close();
    }

    delete ui;
}

void MainWindow::on_btn_save_clicked()
{
  QString filename = QFileDialog::getSaveFileName(this, "Пример фильтра",
                                   QDir::currentPath(),"Текстовый файл(*.txt);;Двоичный файл(*.original)");
  if (filename.length())
  {
      QString ext = QString(&(filename.data()[filename.length() - 9]));
      QFile file (filename);

      if (file.open(QIODevice::WriteOnly))
      {
          QString s = ui->plainTextEdit->toPlainText();
          QByteArray barr = s.toUtf8();          // преобразуем строку в
                                                 // последовательность байт
                                                 // кодировка текста UTF-8
          file.write(barr, barr.length());       // записываем
          if (ext == ".original")
          {
              s = "Author:" + ui->lineEdit->text();
              barr = s.toUtf8();
              file.write(barr, barr.length());
          }
          file.close();
      }
  }
}

void MainWindow::on_btn_open_clicked()
{
  QString filename = QFileDialog::getOpenFileName(this, "Пример фильтра",
                                   QDir::currentPath(),"Текстовый файл(*.txt);;Двоичный файл(*.original)");
  if (filename.length())
  {
      QString ext = QString(&(filename.data()[filename.length() - 9]));
      QFile file (filename);

      if (file.open(QIODevice::ReadOnly))
      {
          QByteArray byteArray = file.readAll(); // считываем весь файл
          QString s = tr(byteArray.data());

          if (ext == ".original")
          {
            QStringList list = s.split("Author:");
            ui->plainTextEdit->setPlainText(list[0]);
            if (list.size() > 1)
                ui->lineEdit->setText(list[1]);
            else
                ui->lineEdit->setText("");
          }
          else
          {
              ui->plainTextEdit->setPlainText(s);
              ui->lineEdit->setText("");
          }
          ui->plainTextEdit_2->setPlainText(filename);
          file.close();
      }

  }
}


void MainWindow::on_btn_undo_clicked()
{
    ui->plainTextEdit->undo();
}


void MainWindow::on_btn_redo_clicked()
{
    ui->plainTextEdit->redo();
}

void MainWindow::on_desc_btn_clicked()
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    QFile file (":/desc/description.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray byteArray = file.readAll();
    msgBox.setText(tr(byteArray.data()));
    msgBox.exec();
}
