#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "blockscheme.h"
#include "graphicscene.h"
#include <QGraphicsScene>
#include <QGraphicsView>

class MainWindow : public QGraphicsView
{
   Q_OBJECT

public:
   MainWindow(QWidget *parent = 0);
   ~MainWindow();
private:
   QGraphicsView *view;
   GraphicScene *scene;
   BlockScheme *bscheme,*bscheme1;
   int geometryCounter;
protected:
private slots:
    void reDraw();
    void randomColorF();
    void randomColorAll();
    void slot__createItem(QGraphicsSceneMouseEvent *event);
};

#endif // MAINWINDOW_H
