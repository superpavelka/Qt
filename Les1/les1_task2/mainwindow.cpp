#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>

/*Расчет стороны треугольника по двум сторонам и углом между ними.
 * Дополнительно: добавить переключатель из QRadioButton для выбора единиц, в каких указан угол: градусах или радианах.
 * Формулу для расчета можно найти по ссылке: https://www-formula.ru/2011-10-09-11-08-41.*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->rb_angle_degree->setChecked(true);
    ui->le_c->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_calc_clicked()
{
    QString a_s = ui->le_a->text();
    QString b_s = ui->le_b->text();
    QString alpha_s = ui->le_alpha->text();

    alpha_s.replace(",",".");
    a_s.replace(",",".");
    b_s.replace(",",".");

    double a = a_s.toDouble();
    double b = b_s.toDouble();
    double alpha = alpha_s.toDouble();

    bool angle_in_degree = true;

    if (ui->rb_angle_rad->isChecked())
        angle_in_degree = false;

    QString s1;
    if (angle_in_degree)
        alpha = qDegreesToRadians(alpha);

    double c = qPow(a,2)+qPow(b,2)-2*a*b*qCos(alpha);
    if (c > 0)
    {
        c = qSqrt(c);
        s1 = QString::number(c);
    }
    else
        s1 = "Не существ";

    if (qRadiansToDegrees(alpha) >= 180)
        s1 = "Не существ";

    ui->le_c->setText(s1);

}
