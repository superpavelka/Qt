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
#include <QTextList>
#include <QDate>
#include <QTime>
/*
Добавить в текстовый редактор возможность вставлять дату и время в текст по позиции курсора.
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    ui->centralwidget->setLayout(ui->verticalLayout);
    mdiArea = new QMdiArea(this);
    m_menu = new QMenu(this);
    ui->btn_menu->setMenu(m_menu);
    hrMode = false;
    parMode = false;
    roAct = new QAction("Только чтение(ВКЛ)", m_menu);
    printAct = new QAction("Печать", m_menu);
    hrAct = new QAction("Горизонтальная линия при переходе на новую строку(ВКЛ)", m_menu);
    parAct = new QAction("Нумерация абзацев(ВКЛ)", m_menu);
    tableInsAct = new QAction("Вставка таблицы", m_menu);
    dateInsAct = new QAction("Вставка даты", m_menu);
    timeInsAct = new QAction("Вставка времени", m_menu);
    ui->verticalLayout->addWidget(mdiArea);
    mdiArea->addSubWindow(ui->textEdit);
    te = ui->textEdit;
    m_menu->addAction(roAct);
    m_menu->addAction(printAct);
    m_menu->addAction(hrAct);
    m_menu->addAction(parAct);
    m_menu->addAction(tableInsAct);
    m_menu->addAction(dateInsAct);
    m_menu->addAction(timeInsAct);
    connect(roAct, SIGNAL(triggered()), this, SLOT(read_only_switch()));
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));
    connect(hrAct, SIGNAL(triggered()), this, SLOT(newlineToBr()));
    connect(parAct, SIGNAL(triggered()), this, SLOT(paragraphMode()));
    connect(tableInsAct, SIGNAL(triggered()), this, SLOT(tableIns()));
    connect(dateInsAct, SIGNAL(triggered()), this, SLOT(dateIns()));
    connect(timeInsAct, SIGNAL(triggered()), this, SLOT(timeIns()));

    /*QFile file ("./lasttext.txt");
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray byteArray = file.readAll(); // считываем весь файл
        //ui->textEdit->setPlainText(tr(byteArray.data()));
        ui->textEdit->setHtml(tr(byteArray.data()));
        file.close();
    }*/
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
        //QString s = ui->textEdit->toPlainText();
        QString s = ui->textEdit->toHtml();
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
          //QString s = te->toPlainText();
          QString s = te->toHtml();
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
            //te->setPlainText(list[0]);
            te->setHtml(list[0]);
            if (list.size() > 1)
                ui->lineEdit->setText(list[1]);
            else
                ui->lineEdit->setText("");
          }
          else
          {
              te->setHtml(s);
              //te->setPlainText(s);
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
    if (!hrMode)
    {
        //QString s =te->toPlainText();
        QString s =te->toHtml();
        //s.replace("\n","<hr>");
        s.replace("<br /></p>","</p><hr>");
        te->setHtml(s);
        hrAct->setText("Горизонтальная линия при переходе на новую строку(ВЫКЛ)");
        hrMode = true;
    }
    else
    {
        //QString s = te->toPlainText();
        QString s =te->toHtml();
        //s.replace("<hr>","\n");
        s.replace("<hr />","");
        //te->setPlainText(s);
        te->setHtml(s);
        hrAct->setText("Горизонтальная линия при переходе на новую строку(ВКЛ)");
        hrMode = false;
    }
}

void MainWindow::paragraphMode()
{
    QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();
    QWidget *wgt = activeSubWindow->widget();
    QTextEdit* te = (QTextEdit*)wgt;
    QTextCursor cursor = te->textCursor();
    QTextListFormat::Style style = QTextListFormat::ListStyleUndefined;
    int styleIndex = 0;
    if (!parMode)
    {
        style = QTextListFormat::ListDecimal;
        styleIndex = 4;
        parMode = true;
        parAct->setText("Нумерация абзацев(ВЫКЛ)");
    }
    else
    {
        parAct->setText("Нумерация абзацев(ВКЛ)");
        parMode = false;
    }
    cursor.beginEditBlock();

    QTextBlockFormat blockFmt = cursor.blockFormat();

    if (style == QTextListFormat::ListStyleUndefined) {
        blockFmt.setObjectIndex(-1);
        int headingLevel = styleIndex >= 9 ? styleIndex - 9 + 1 : 0; // H1 to H6, or Standard
        blockFmt.setHeadingLevel(headingLevel);
        cursor.setBlockFormat(blockFmt);

        int sizeAdjustment = headingLevel ? 4 - headingLevel : 0; // H1 to H6: +3 to -2
        QTextCharFormat fmt;
        fmt.setFontWeight(headingLevel ? QFont::Bold : QFont::Normal);
        fmt.setProperty(QTextFormat::FontSizeAdjustment, sizeAdjustment);
        cursor.select(QTextCursor::LineUnderCursor);
        cursor.mergeCharFormat(fmt);
        te->mergeCurrentCharFormat(fmt);
    } else {
        QTextListFormat listFmt;
        if (cursor.currentList()) {
            listFmt = cursor.currentList()->format();
        } else {
            listFmt.setIndent(blockFmt.indent() + 1);
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
        }
        listFmt.setStyle(style);
        cursor.createList(listFmt);
    }

    cursor.endEditBlock();

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

void MainWindow::dateIns()
{
    QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();
    QWidget *wgt = activeSubWindow->widget();
    QTextEdit* te = (QTextEdit*)wgt;
    int day = QInputDialog::getInt(this,"Input","day:",1,1,31,1);
    int month = QInputDialog::getInt(this,"Input","month:",1,1,12,1);
    int year = QInputDialog::getInt(this,"Input","year:",2019,0,3000,1);
    if (day && month && year)
    {
        QDate date;
        date.setDate(year,month,day);
        const QString month[] = {"", " января " , " февраля ", " марта ",
                                      " апреля ", " мая ", " июня ",
                                      " июля ", " августа ", " сентября ",
                                      " октября ", " ноября ", " декабря ",
                                     }; // Месяцы отсчитываются от 1, поэтому первый
                                        // элемент - пустая строка
        QString dstr = QString::number(date.day()) + month[date.month()] + QString::number(date.year());
        QTextCursor cur = te->textCursor();
        cur.insertHtml(dstr);
    }

}

void MainWindow::timeIns()
{
    QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow();
    QWidget *wgt = activeSubWindow->widget();
    QTextEdit* te = (QTextEdit*)wgt;
    int h = QInputDialog::getInt(this,"Input","hours:",0,1,23,1);
    int m = QInputDialog::getInt(this,"Input","minutes:",0,1,59,1);
    int s = QInputDialog::getInt(this,"Input","seconds:",0,1,59,1);
    if (h && m && s)
    {
        QTime time;
        QString zeroS;
        QString zeroM;
        QString zeroH;
        time.setHMS(h,m,s);
        if (time.second() < 10)
            zeroS = '0';
        else
            zeroS = "";
        if (time.minute() < 10)
            zeroM = '0';
        else
            zeroM = "";
        if (time.hour() < 10)
            zeroH = '0';
        else
            zeroH = "";
        QString tstr = zeroH + QString::number(time.hour()) + ':' + zeroM + QString::number(time.minute())
                + ':' + zeroS + QString::number(time.second());
        QTextCursor cur = te->textCursor();
        cur.insertHtml(tstr);
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

