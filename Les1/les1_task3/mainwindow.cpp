#include "mainwindow.h"
#include "ui_mainwindow.h"

/**Создать программу, разместить на поле виджет QPlainTextEdit.
 * Добавить кнопки: для добавления фиксированной строки, замены на готовый текст.
 * Разместить QTextEdit. Через метод setHtml(QString) установите текст произвольного
 * html-кода, например <font color='red'>Hello</font>.*/

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

void MainWindow::on_btn_add_clicked()
{
    QString s = ui->plainTextEdit->toPlainText();
    ui->textEdit->insertHtml(s);
}

void MainWindow::on_btn_replace_clicked()
{
    QString s = ui->plainTextEdit->toPlainText();
    ui->textEdit->setHtml(s);
}
