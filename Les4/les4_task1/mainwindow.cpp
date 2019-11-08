#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
 Создать программу, в которой будет поле ввода. После ввода строки и нажатия клавиши Enter, строка переносится в заголовок окна.
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(signal__setTitleText(QString)), this, SLOT(slot__setTitleText(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Enter)
    {
        QString s = ui->plainTextEdit->toPlainText();
        emit signal__setTitleText(s);
    }
    if (event->key() == Qt::Key_Return)
    {
        QString s = ui->plainTextEdit->toPlainText();
        emit signal__setTitleText(s);
    }
}

void MainWindow::slot__setTitleText(QString s)
{
   this->setWindowTitle(s);
}
