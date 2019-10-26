#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QModelIndexList>
/*Создать список с названиями языков программирования (С++, Python, Java, C#, PHP, JavaScript).
 * Для каждого элемента списка рядом отобразить иконку с логотипом языка программирования.
 * Предусмотреть возможно изменения текста в каждом элементе списка.
 * Добавить возможность перемещения элементов в списке.
 * Создать кнопку для добавления нового языка программирования в список.
 * Иконку для него поставить любую (по-умолчанию).
 * Создать кнопку для удаления элемента из списка (в этом случае элемент должен быть выбран).
 * Создать CheckBox и когда будет стоять галочка, отобразить список в режиме иконок (нужен метод setViewMode()).
 * Когда галочка не стоит, то список должен отображаться в обычном режиме.
 * Подсказка: используйте справку qt, вызов F1.*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    ui->listView->setModel(model);
    model->appendRow(new QStandardItem(QIcon(":/icons8-c++.png"), "C++"));
    model->appendRow(new QStandardItem(QIcon(":/icons8-java.png"), "Java"));
    model->appendRow(new QStandardItem(QIcon(":/icons8-python.png"), "Python"));
    model->appendRow(new QStandardItem(QIcon(":/icons8-javascript.png"), "JavaScript"));
    model->appendRow(new QStandardItem(QIcon(":/icons8-c-sharp.png"), "C#"));
    model->appendRow(new QStandardItem(QIcon(":/icons8-php.png"), "PHP"));

    ui->listView->setAcceptDrops(true);
    ui->listView->setDragEnabled(true);
    ui->listView->setDragDropMode(QAbstractItemView::DragDrop);
    ui->listView->setDefaultDropAction(Qt::MoveAction);

    if (ui->checkBox->isChecked())
        ui->listView->setViewMode(QListView::IconMode);
    else
        ui->listView->setViewMode(QListView::ListMode);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_checkBox_clicked()
{
    if (ui->checkBox->isChecked())
        ui->listView->setViewMode(QListView::IconMode);
    else
        ui->listView->setViewMode(QListView::ListMode);

    ui->listView->setAcceptDrops(true);
    ui->listView->setDragEnabled(true);
    ui->listView->setDragDropMode(QAbstractItemView::DragDrop);
    ui->listView->setDefaultDropAction(Qt::MoveAction);
}

void MainWindow::on_btn_add_clicked()
{
    model->appendRow(new QStandardItem(QIcon(":/icons8-prog.png"), "newElement"));
}

void MainWindow::on_btn_del_clicked()
{
    QModelIndexList indexes = ui->listView->selectionModel()->selectedRows();
       while (!indexes.isEmpty())
       {
           model->removeRows(indexes.last().row(), 1);
           indexes.removeLast();
       }
}
