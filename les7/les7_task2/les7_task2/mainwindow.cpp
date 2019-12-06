#include "mainwindow.h"
#include <QMessageBox>
#include <QGraphicsSceneMouseEvent>


/*Используя графическое представление, создать программу-окно, на которое можно добавлять
 * графические элементы щелчком левой кнопки мыши на пустой области окна.
 * Добавляемыми элементами могут быть прямоугольник, эллипс, звезда, они должны добавляться
 * по очереди, т.е. первый щелчок мыши - прямоугольник, второй - эллипс, третий - звезда,
 * четвертый - снова прямоугольник и т.д. Цвет этих фигур должен быть случайным.
 * При щелчке правой кнопки мыши по элементу он должен удалиться.
 * Должна быть возможность перемещать элементы, с помощью зажатой левой кнопкой мыши.
 */

MainWindow::MainWindow(QWidget *parent)
   : QGraphicsView(parent)
{
    srand(clock());
    scene = new GraphicScene(this);
    this->setScene(scene);
    bscheme = new BlockScheme(this);
    scene->addItem(bscheme);
    bscheme1 = new BlockScheme(this);
    scene->addItem(bscheme1);
    geometryCounter = 0;

    connect(bscheme,SIGNAL(reDraw()),this, SLOT(reDraw()));
    connect(bscheme1,SIGNAL(reDraw()),this, SLOT(reDraw()));
    connect(bscheme,SIGNAL(dblClick()),this, SLOT(randomColorF()));
    connect(bscheme1,SIGNAL(dblClick()),this, SLOT(randomColorAll()));
    connect(scene,SIGNAL(signal__createItem(QGraphicsSceneMouseEvent*)),this,SLOT(slot__createItem(QGraphicsSceneMouseEvent*)));
}
MainWindow::~MainWindow()
{

}

void MainWindow::reDraw()
{
    scene->update();
    update();
}

void MainWindow::randomColorF()
{
    bscheme->setBrush(QBrush(QColor(rand() % 256,rand() % 256,rand() % 256)));
}

void MainWindow::randomColorAll()
{
    bscheme->setBrush(QBrush(QColor(rand() % 256,rand() % 256,rand() % 256)));
    bscheme1->setBrush(QBrush(QColor(rand() % 256,rand() % 256,rand() % 256)));
}

void MainWindow::slot__createItem(QGraphicsSceneMouseEvent *event)
{
    BlockScheme *item;
    if (geometryCounter == 3)
        geometryCounter = 0;
    item = new BlockScheme(this,geometryCounter);
    geometryCounter++;
    item->setBrush(QBrush(QColor(rand() % 256,rand() % 256,rand() % 256)));
    scene->addItem(item);
    item->setPos(event->scenePos());

    //emit itemInserted(item);
}
