#include "graphicsitem.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

GraphicsItem::GraphicsItem(QObject *parent,int g) : QObject(parent), QGraphicsItem()
{
   x = 0;
   y = 0;
   brush.setColor(QColor(rand() % 256, rand() % 256, rand() % 256));
   brush.setStyle(Qt::BrushStyle::SolidPattern); // Полностью закрашивать
   geometry = (Geometry)g;                  // По умолчанию - эллипс
   setPos(0,0);
   moving = false;
   setFlag(QGraphicsItem::ItemIsMovable,true);
}

void GraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   painter->setBrush(brush);
   if (geometry == Geometry::ELLIPS)
   {
       painter->drawEllipse(x, y, 200, 100);

   }
   if (geometry == Geometry::RECTANGLE)
   {
       painter->drawRect(x, y, 200, 100);

   }
   if (geometry == Geometry::STAR)
   {
       QPainterPath path;
       path.moveTo(x,y);
       path.lineTo(x+10, y-30);
       path.lineTo(x+20, y);
       path.lineTo(x+50, y+10);
       path.lineTo(x+20, y+20);
       path.lineTo(x+10, y+50);
       path.lineTo(x, y+20);
       path.lineTo(x-30, y+10);
       path.lineTo(x, y);
       painter->fillPath(path,brush);
   }
   Q_UNUSED(option)
   Q_UNUSED(widget)
}

QRectF GraphicsItem::boundingRect() const         // Обязателен для
                                                 // переопределения
{
    if (geometry == Geometry::ELLIPS || geometry == Geometry::RECTANGLE)
        return QRectF(x, y, 200, 100);                // Текущие координаты
    else
        return QRectF(x,y,80,80);
}

void GraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

   if (event->button() == Qt::LeftButton)
   {
       moving = true;
       bpoint = event->pos().toPoint();

   }
   if (event->button() == Qt::RightButton)
   {
       this->deleteLater();
       emit reDraw();                            // переотрисовка
   }
}

void GraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
   if (event->button() == Qt::LeftButton)
   {
       moving = false;                            // Снимаем флаг на
                                                  // перемещение
       emit reDraw();
   }
}

void GraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
   if (moving)                                    // Если активен флаг
                                                  // перемещения
   {
// Вычисляем вектор смещения
       QPoint p = event->pos().toPoint() - bpoint;
       x += p.x();
       y += p.y();
       bpoint = event->pos().toPoint();           // Запоминаем новую позицию
                                                  // курсора
       emit reDraw();                             // Переотрисовываем
   }
}

void GraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
   if (event->button() == Qt::LeftButton)
   {
       emit dblClick();                            // Отправляем сигнал
                                                   // о двойном клике
   }
}

/*void GraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit reDraw();
}*/
