#ifndef BLOCKSCHEME_H
#define BLOCKSCHEME_H

#include <QObject>
#include <QGraphicsItem>
#include <QContextMenuEvent>
#include <QBrush>
#include <QGraphicsScene>

class BlockScheme : public QObject, public QGraphicsItem
{
   Q_OBJECT
   Q_PROPERTY(QBrush brush)
public:
   void setBrush(QBrush brush) {this->brush = brush; emit reDraw();}
signals:
   void reDraw();
   void dblClick();
   void signal__createItem(QGraphicsSceneMouseEvent *event);
public slots:
private:
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
   QRectF boundingRect() const override;
private:
   enum Geometry {RECTANGLE, ELLIPS, STAR};
   int x, y;
   Geometry geometry;
   QPoint bpoint;
   bool moving;
   QBrush brush;
public:
   explicit BlockScheme(QObject *parent = nullptr,int g = 0);
protected:
   void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
   void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
   void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
   void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // BLOCKSCHEME_H
