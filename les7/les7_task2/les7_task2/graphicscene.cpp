#include "graphicscene.h"
#include <QGraphicsSceneMouseEvent>

GraphicScene::GraphicScene(QObject *parent)
{

}

void GraphicScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

   if (event->button() == Qt::LeftButton)
   {
      emit signal__createItem(event);
   }
}
