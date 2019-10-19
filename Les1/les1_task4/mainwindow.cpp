#include "mainwindow.h"
#include "ui_mainwindow.h"
/*Получите QTextDocument из виджета QTextEdit (метод document).
 * С помощью списка методов и переменных выберите, какие наиболее
 * интересны для редактирования текста. Ознакомьтесь с работой
 * подсказчика кода Qt Creator (Ctrl+Space).
 * */
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


void MainWindow::on_btn_changeFont_clicked()
{
    QTextDocument* s = ui->textEdit->document();
    QFont sansFont("Helvetica [Cronyx]", 12);
    s->setDefaultFont(sansFont);
    ui->textEdit->setDocument(s);
}
