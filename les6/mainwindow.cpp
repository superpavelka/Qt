#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QInputDialog>
#include <QMdiSubWindow>
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
    ui->centralwidget->setLayout(ui->verticalLayout);
    mdiArea = new QMdiArea(this);
    QMenu *m_menu = new QMenu(this);
    ui->btn_menu->setMenu(m_menu);
    htmlMode = false;
    parMode = false;
    roAct = new QAction("Только чтение(ВКЛ)", m_menu);
    printAct = new QAction("Печать", m_menu);
    hrAct = new QAction("Горизонтальная линия при переходе на новую строку(ВКЛ)", m_menu);
    parAct = new QAction("Нумерация абзацев(ВКЛ)", m_menu);
    tableInsAct = new QAction("Вставка таблицы", m_menu);
    ui->verticalLayout->addWidget(mdiArea);
    mdiArea->addSubWindow(ui->textEdit);
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
        //ui->textEdit->setPlainText(tr(byteArray.data()));
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
        QString s = ui->textEdit->toPlainText();
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
  QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();
  QWidget *wgt = activeSubWindow->widget();
  QTextEdit* te = (QTextEdit*)wgt;
  QString filename = QFileDialog::getSaveFileName(this, "Пример фильтра",
                                   QDir::currentPath(),"Текстовый файл(*.txt);;Двоичный файл(*.original)");

  if (filename.length())
  {
      QString ext = QString(&(filename.data()[filename.length() - 9]));
      QFile file (filename);

      if (file.open(QIODevice::WriteOnly))
      {
          QString s = te->toPlainText();
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
      QTextEdit *te = new QTextEdit(mdiArea);
      mdiArea->addSubWindow(te);
      te->show();
      QString ext = QString(&(filename.data()[filename.length() - 9]));
      QFile file (filename);

      if (file.open(QIODevice::ReadOnly))
      {
          QByteArray byteArray = file.readAll(); // считываем весь файл
          QString s = tr(byteArray.data());

          if (ext == ".original")
          {
            QStringList list = s.split("Author:");
            te->setPlainText(list[0]);
            if (list.size() > 1)
                ui->lineEdit->setText(list[1]);
            else
                ui->lineEdit->setText("");
          }
          else
          {
              te->setPlainText(s);
              ui->lineEdit->setText("");
          }
          file.close();
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

void MainWindow::read_only_switch()
{
    QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();
    QWidget *wgt = activeSubWindow->widget();
    QTextEdit* te = (QTextEdit*)wgt;
    if (!read_only)
    {
        read_only = true;
        roAct->setText("Только чтение(ВЫКЛ)");
        te->setReadOnly(true);
    }
    else
    {
        read_only = false;
        roAct->setText("Только чтение(ВКЛ)");
        te->setReadOnly(false);
    }
}

void MainWindow::newlineToBr()
{
    QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();
    QWidget *wgt = activeSubWindow->widget();
    QTextEdit* te = (QTextEdit*)wgt;
    if (!htmlMode)
    {
        QString s =te->toPlainText();
        s.replace("\n","<hr>");
        te->setHtml(s);
        hrAct->setText("Горизонтальная линия при переходе на новую строку(ВЫКЛ)");
        htmlMode = true;
    }
    else
    {
        QString s = te->toPlainText();
        s.replace("<hr>","\n");
        te->setPlainText(s);
        hrAct->setText("Горизонтальная линия при переходе на новую строку(ВКЛ)");
        htmlMode = false;
    }
}

void MainWindow::paragraphMode()
{
    QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();
    QWidget *wgt = activeSubWindow->widget();
    QTextEdit* te = (QTextEdit*)wgt;
    if (!parMode)
    {
        QString s = te->toPlainText();
        int c = 1;
        if (s.size() && s[0]!="\n")
        {
        s.insert(0,QString::number(c) + ". ");
        c++;
        }
        for (int i=0;i<s.size();i++)
        {
            if (s[i] == "\n" && ((i+1) < s.size()) && s[i+1] != "\n")
            {
                s.insert(i+1,QString::number(c) + ". ");
                c++;
            }
        }
        te->setPlainText(s);
        parMode = true;
        parAct->setText("Нумерация абзацев(ВЫКЛ)");
    }
    else
    {
       QString s = te->toPlainText();
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
       te->setPlainText(s);
       parMode = false;
       parAct->setText("Нумерация абзацев(ВКЛ)");
    }
}
void MainWindow::print()
{
    QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();
    QWidget *wgt = activeSubWindow->widget();
    QTextEdit* te = (QTextEdit*)wgt;
    QTextDocument* doc = te->document();
    QPrinter printer;
    QPrintDialog dlg(&printer, this);
    dlg.setWindowTitle("Print");
    if (dlg.exec() != QDialog::Accepted)
        return;
    doc->print(&printer);
}

void MainWindow::tableIns()
{
    QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();
    QWidget *wgt = activeSubWindow->widget();
    QTextEdit* te = (QTextEdit*)wgt;
    int r = QInputDialog::getInt(this,"Input","rows:",2,1,100,1);
    int c = QInputDialog::getInt(this,"Input","columns:",2,1,100,1);
    if (r && c)
    {
        QTextCursor cur = te->textCursor();
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

