#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

/*
Добавить  в текстовый редактор выбор из нескольких таблиц стилей.
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    ui->plainTextEdit_2->setReadOnly(true);
    QPlainTextEdit* pte = ui->plainTextEdit;
    roAct = new QAction("Только чтение(ВКЛ)", pte);
    pte->addAction(roAct);
    pte->setContextMenuPolicy(Qt::ActionsContextMenu);
    pte->connect(roAct, SIGNAL(triggered()), this, SLOT(read_only_switch()));

    QFile file ("./lasttext.txt");
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray byteArray = file.readAll(); // считываем весь файл
        ui->plainTextEdit->setPlainText(tr(byteArray.data()));
        ui->plainTextEdit_2->setPlainText("lasttext.txt");
        file.close();
    }
    ui->comboBox->addItem("default");
    ui->comboBox->addItem("green");
    ui->comboBox->addItem("red");
    edit = true;
    read_only = false;
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
    edit = false;
    if (!read_only)
    {
        if (cur_undo_pos > 0)
        {
            cur_undo_pos--;
            QString s = undo_list.at(cur_undo_pos);
            ui->plainTextEdit->setPlainText(s);
        }
    }
}


void MainWindow::on_btn_redo_clicked()
{
    edit = false;
    if (!read_only)
    {
        if (undo_list.size() - 1 >= (cur_undo_pos + 1))
        {
            cur_undo_pos++;
            QString s = undo_list.at(cur_undo_pos);
            ui->plainTextEdit->setPlainText(s);
        }
    }

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

void MainWindow::on_plainTextEdit_textChanged()
{
    if (!read_only)
    {
        if (edit)
        {
            QString s = ui->plainTextEdit->toPlainText();
            if (!undo_list.isEmpty() && undo_list.last() != s)
            {
                undo_list.append(s);
                cur_undo_pos++;
            }
            else if (undo_list.isEmpty())
            {
                undo_list.append(s);
                cur_undo_pos = 0;
            }
        }
    }
    edit = true;
}

void MainWindow::read_only_switch()
{
    if (!read_only)
    {
        read_only = true;
        roAct->setText("Только чтение(ВЫКЛ)");
        ui->plainTextEdit->setReadOnly(true);
    }
    else
    {
        read_only = false;
        roAct->setText("Только чтение(ВКЛ)");
        ui->plainTextEdit->setReadOnly(false);
    }
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    MainWindow *nw = qobject_cast<MainWindow*>( QApplication::topLevelWidgets()[ 0 ] );

    if (arg1 == "green")
    {
        nw->setStyleSheet("");
        nw->setStyleSheet("QPushButton {background-color: green;} QMainWindow{background-color: green}");
    }
    else if (arg1 == "red")
    {
        nw->setStyleSheet("");
        nw->setStyleSheet("QPushButton {background-color: red;}QMainWindow{background-color: red}");
    }
    else if (arg1 == "default")
    {
        nw->setStyleSheet("");
        //nw->setStyleSheet("QPushButton {background-color: gray;}QMainWindow{background-color: gray}");
    }
    nw->update();

}
