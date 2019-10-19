#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->rb_angle_degree->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    double a = ui->le_a->text().toDouble();
    double b = ui->le_b->text().toDouble();
    double alpha = ui->le_alpha->text().toDouble();

    bool angle_in_degree = true;

    //ui->rb_angle_degree->setChecked(true);

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
