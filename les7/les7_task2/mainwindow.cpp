#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include "graphicsitem.h"

/*Используя графическое представление, создать программу-окно, на которое можно добавлять
 * графические элементы щелчком левой кнопки мыши на пустой области окна.
 * Добавляемыми элементами могут быть прямоугольник, эллипс, звезда, они должны добавляться
 * по очереди, т.е. первый щелчок мыши - прямоугольник, второй - эллипс, третий - звезда,
 * четвертый - снова прямоугольник и т.д. Цвет этих фигур должен быть случайным.
 * При щелчке правой кнопки мыши по элементу он должен удалиться.
 * Должна быть возможность перемещать элементы, с помощью зажатой левой кнопкой мыши.
 */
/*
3. * Для предыдущей задачи добавить:
a. возможность приближать и удалять изображение путем прокручивания колеса мыши и нажатия клавиш + или - соответственно.
b. Возможность вращать фигуру вокруг своего центра зажатым колесом мыши.*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view = new GraphicsView();
    scene = new QGraphicsScene();
    view->setScene(scene);
    this->setCentralWidget(view);
    geometryCounter = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

   if (event->button() == Qt::LeftButton)
   {
       GraphicsItem *item;
       if (geometryCounter == 3)
           geometryCounter = 0;
       item = new GraphicsItem(this,geometryCounter);
       geometryCounter++;
       item->setBrush(QBrush(QColor(rand() % 256,rand() % 256,rand() % 256)));
       scene->addItem(item);
       //QPoint point = event->pos();
       item->setPos(event->pos().x(),event->pos().y());
       connect(item, SIGNAL(reDraw()),this,SLOT(reDraw()));
   }
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
        const double scaleFactor = 1.15;
        if (event->delta() > 0)
        {
            view->scale(scaleFactor, scaleFactor);
        }
        else
        {
            view->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }
}

void MainWindow::reDraw()
{
    scene->update();
    update();
}
