#ifndef GRAPHICSCENE_H
#define GRAPHICSCENE_H
#include <QGraphicsScene>

class GraphicScene : public QGraphicsScene
{

Q_OBJECT

public:
    GraphicScene(QObject *parent = nullptr);

protected:
   void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
   void signal__createItem(QGraphicsSceneMouseEvent *event);
};

#endif // GRAPHICSCENE_H
