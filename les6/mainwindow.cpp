#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QInputDialog>
/*
Добавить меню в текстовый редактор.
Добавить в текстовый редактор печать, класс печати. Учтите, что строка может не помещаться по ширине страницы. Реализовать разбиение текста на дополнительные строки.
Новая строка должна разделяться горизонтальной линией (тег <hr>). Добавить опцию нумерации абзацев. Добавить возможность вставки таблиц.
Добавить в текстовый редактор поддержку многодокументного интерфейса.
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    ui->plainTextEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->centralwidget->setLayout(ui->verticalLayout);
    QMenu *m_menu = new QMenu(this);
    ui->btn_menu->setMenu(m_menu);
    htmlMode = false;
    parMode = false;
    roAct = new QAction("Только чтение(ВКЛ)", m_menu);
    printAct = new QAction("Печать", m_menu);
    hrAct = new QAction("Горизонтальная линия при переходе на новую строку(ВКЛ)", m_menu);
    parAct = new QAction("Нумерация абзацев(ВКЛ)", m_menu);
    tableInsAct = new QAction("Вставка таблицы", m_menu);

    m_menu->addAction(roAct);
    m_menu->addAction(printAct);
    m_menu->addAction(hrAct);
    m_menu->addAction(parAct);
    m_menu->addAction(tableInsAct);

    connect(roAct, SIGNAL(triggered()), this, SLOT(read_only_switch()));
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));
    connect(hrAct, SIGNAL(triggered()), this, SLOT(newlineToBr()));
    connect(parAct, SIGNAL(triggered()), this, SLOT(paragraphMode()));
    connect(tableInsAct, SIGNAL(triggered()), this, SLOT(tableIns()));

    QFile file ("./lasttext.txt");
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray byteArray = file.readAll(); // считываем весь файл
        ui->plainTextEdit->setPlainText(tr(byteArray.data()));
        ui->textEdit->setPlainText(tr(byteArray.data()));
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

void MainWindow::newlineToBr()
{
    if (!htmlMode)
    {
        QString s = ui->textEdit->toPlainText();
        s.replace("\n","<hr>");
        ui->textEdit->setHtml(s);
        hrAct->setText("Горизонтальная линия при переходе на новую строку(ВЫКЛ)");
        htmlMode = true;
    }
    else
    {
        QString s = ui->textEdit->toPlainText();
        s.replace("<hr>","\n");
        ui->textEdit->setPlainText(s);
        hrAct->setText("Горизонтальная линия при переходе на новую строку(ВКЛ)");
        htmlMode = false;
    }
}

void MainWindow::paragraphMode()
{
    if (!parMode)
    {
        QString s = ui->textEdit->toPlainText();
        int c = 1;
        s.insert(0,QString::number(c) + ". ");
        c++;
        for (int i=0;i<s.size();i++)
        {
            if (s[i] == "\n" && ((i+1) < s.size()) && s[i+1] != "\n")
            {
                s.insert(i+1,QString::number(c) + ". ");
                c++;
            }
        }
        ui->textEdit->setPlainText(s);
        parMode = true;
        parAct->setText("Нумерация абзацев(ВЫКЛ)");
    }
    else
    {
       QString s = ui->textEdit->toPlainText();
       if (s.size() > 3 && s[0] == "1" && s[1] == ".")
           s.remove(0,3);
       for (int i=0;i<s.size();i++)
       {
           if (s[i] == "\n" && ((i+1) < s.size()) && s[i+1] != "\n")
           {
               if ((i+1) < s.size())
               {
                   while (true)
                   {
                       s.remove(i+1,1);
                       if (s[i+1] == ".")
                           break;
                   }
                   s.remove(i+1,2);
               }
           }
       }
       ui->textEdit->setPlainText(s);
       parMode = false;
       parAct->setText("Нумерация абзацев(ВКЛ)");
    }
}
void MainWindow::print()
{
    QString printStr = ui->plainTextEdit->toPlainText();

    QChar *list = printStr.data();
    QStringList strlst;
    int line = 0, cursor = 0;
    for (bool getst = true;getst;)
    {
        int index = printStr.indexOf("\n", cursor);
        QString s = "";
        if (index == -1)
        {
           getst = false;
           s.append(&list[cursor], printStr.length() - cursor);
        }
        else s.append(&list[cursor], index - cursor);
        cursor = index + 1;
        strlst << s;
    }

    QPrinter printer;
    QPrintDialog dlg(&printer, this);
    dlg.setWindowTitle("Print");
    if (dlg.exec() != QDialog::Accepted)
        return;
    QPainter painter;
    painter.begin(&printer);
    int w = painter.window().width();
    int h = painter.window().height();
    int amount = strlst.count();
    QFont font = painter.font();
    QFontMetrics fmetrics(font);
    for (int i = 0; i < amount; i++)
    {
        QPointF pf;
        pf.setX(10);
        pf.setY(line);
        painter.drawText(pf, strlst.at(i));
        line += fmetrics.height();
        if (h - line <= fmetrics.height())
        {
            printer.newPage();
            line = 0;
        }
     }
    painter.end();

}

void MainWindow::tableIns()
{
    int r = QInputDialog::getInt(this,"Input","rows:",2,1,100,1);
    int c = QInputDialog::getInt(this,"Input","columns:",2,1,100,1);
    if (r && c)
    {
        QTextCursor cur = ui->textEdit->textCursor();
        QTextTable* t = cur.insertTable(r, c);
    }
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    if (arg1 == "green")
    {
        this->setStyleSheet("");
        this->setStyleSheet("QPushButton {background-color: green;} QMainWindow{background-color: green}");
    }
    else if (arg1 == "red")
    {
        this->setStyleSheet("");
        this->setStyleSheet("QPushButton {background-color: red;}QMainWindow{background-color: red}");
    }
    else if (arg1 == "default")
    {
        this->setStyleSheet("");
        //nw->setStyleSheet("QPushButton {background-color: gray;}QMainWindow{background-color: gray}");
    }
}
