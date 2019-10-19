#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>

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

void MainWindow::on_btn_calc_clicked()
{
    double a = ui->le_a->text().toDouble();
    double b = ui->le_b->text().toDouble();
    double c = ui->le_c->text().toDouble();

    double d =  qPow(b,2) - 4*a*c;
    double x1;
    double x2;

    QString s1;
    QString s2;

    if (d < 0)
    {
        s1 = "Нет решений";
        s2 = "Нет решений";

    }
    else if (a == 0.0 && b != 0.0)
    {
     x1 = -c/b;
     x2 = x1;
     s1 = QString::number(x1);
     s2 = QString::number(x2);
    }
    else if(a == 0.0 && b == 0.0)
    {
        s1 = "Нет решений";
        s2 = "Нет решений";
    }
    else if(a == 0.0 && b == 0.0 && c == 0.0)
    {
        s1 = "0";
        s2 = "0";
    }
    else
    {
        x1 = (-b + qSqrt(d))/2*a;
        x2 = (-b - qSqrt(d))/2*a;
        s1 = QString::number(x1);
        s2 = QString::number(x2);
    }
    ui->le_x1->setText(s1);
    ui->le_x2->setText(s2);

}
