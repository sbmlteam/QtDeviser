#include "smoothgraphicsitem.h"

#include <QPainter>

SmoothGraphicsItem::SmoothGraphicsItem(const QPixmap& pixmap)
  : QGraphicsPixmapItem(pixmap)
{

}

void SmoothGraphicsItem::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem * /*option*/,
                               QWidget * /*widget*/)
{
  painter->setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform );
  painter->drawPixmap( boundingRect().topLeft(), pixmap() );
}

