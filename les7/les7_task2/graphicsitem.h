#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QContextMenuEvent>
#include <QBrush>
#include <QGraphicsScene>

class GraphicsItem : public QObject, public QGraphicsItem
{
   Q_OBJECT
   Q_PROPERTY(QBrush brush)
public:
   void setBrush(QBrush brush) {this->brush = brush; emit reDraw();}
signals:
   void reDraw();
   void dblClick();
   //void signal__createItem(QGraphicsSceneMouseEvent *event);
public slots:
private:
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
   QRectF boundingRect() const override;
private:
   enum Geometry {RECTANGLE, ELLIPS, STAR};

   Geometry geometry;
   QPoint bpoint;
   bool moving;
   bool rotate;
   QBrush brush;
public:
   explicit GraphicsItem(QObject *parent = nullptr,int g = 0);
   int x, y;
protected:
   void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
   void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
   void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};


#endif // GRAPHICSITEM_H
