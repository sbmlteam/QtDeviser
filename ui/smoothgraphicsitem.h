#ifndef SMOOTHGRAPHICSITEM_H
#define SMOOTHGRAPHICSITEM_H

#include <QGraphicsPixmapItem>

class SmoothGraphicsItem : public QGraphicsPixmapItem
{
public:
  SmoothGraphicsItem(const QPixmap& pixmap);

  virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);

protected:


};

#endif // SMOOTHGRAPHICSITEM_H
