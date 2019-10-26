/*Написать класс, который будет вставлять в текст спецсимволы (4–5).
 * Пригодится для символов, для которых нет клавиши на клавиатуре,
 * но они часто используются в тексте: © — знак охраны авторского права, ‰ — промилле,
 * ®, € — евро, ₽ — рубль. Например, ввод рубля в программе #@RUB@, или руб.
 * (автоматически заменить на знак).
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCursor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    symbols.insert("RUB", "&#8381;");
    symbols.insert("REG", "&reg;");
    symbols.insert("EUR", "&euro;");
    symbols.insert("PRO", "&permil;");
    symbols.insert("COP", "&copy;");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_textEdit_textChanged()
{
    QString txt = ui->textEdit->toPlainText();
    int pos = 0;
    while (true)
    {
        int fnd = txt.indexOf("#@", pos);
        if (fnd==-1)
            return;
        pos = fnd + 1;
        int r  = txt.indexOf('@', fnd+2);
        if (r > 0 && r > fnd)
        {
            QString s = txt.mid(fnd+2, r-fnd-2);

            if (symbols.contains(s))
            {
                QString symb = symbols[s];
                txt.remove(fnd,6);
                txt.insert(fnd+1,symb);
                ui->textEdit->setHtml(txt);
            }
        }
    }
}
