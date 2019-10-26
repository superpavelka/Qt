#include "mainwindow.h"
#include "ui_mainwindow.h"

/*Создать таблицу со столбцами: №, Имя компьютера, IP адрес, MAC адрес.
 * Заполнить таблицу данными. Предусмотреть возможность нескольких строк в таблице
 * (они могут идти не подряд).
 * Для выделенных строк, по нажатию на кнопку покрасить
 * задний фон в другой цвет.*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    rows = 1;
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    QStringList name_table;
    name_table << "№" << "Имя компьютера" << "IP адрес" << "MAC адрес";
    ui->tableWidget->setHorizontalHeaderLabels(name_table);
    ui->tableWidget->setRowCount(rows);
    for (int i = 0;i < 4;i++)
    {
        ui->tableWidget->setItem(0, i, new QTableWidgetItem);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_add_clicked()
{
    rows++;
    ui->tableWidget->setRowCount(rows);
    for (int i = 0;i < 4;i++)
    {
        ui->tableWidget->setItem(rows-1, i, new QTableWidgetItem);
    }
}

void MainWindow::on_btn_paint_clicked()
{
    int i= ui->tableWidget->currentRow();
    for (int j = 0;j < 4;j++)
    {
        ui->tableWidget->item(i, j)->setBackground(Qt::red);
    }
}
