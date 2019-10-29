#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>

/*
 * Написать программу, которая будет находить корень квадратного уравнения второй степени,
 * входные данные: a, b, c. Если нахождение корня невозможно, выводить сообщение в поле результата
 * (или выводить результат в виде комплексного числа). Учитывать, что число a может быть равно нулю.*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_x1->setReadOnly(true);
    ui->le_x2->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_calc_clicked()
{
    QString a_s = ui->le_a->text();
    QString b_s = ui->le_b->text();
    QString c_s = ui->le_c->text();

    double a = a_s.replace(",",".").toDouble();
    double b = b_s.replace(",",".").toDouble();
    double c = c_s.replace(",",".").toDouble();

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
    else if(a == 0.0 && b == 0.0 && c != 0.0)
    {
        s1 = "Нет решений";
        s2 = "Нет решений";
    }
    else if(a == 0.0 && b == 0.0 && c == 0.0)
    {
        s1 = "любое число";
        s2 = "любое число";
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
