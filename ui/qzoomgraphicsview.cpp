#include "qzoomgraphicsview.h"

#include <QWheelEvent>

QZoomGraphicsView::QZoomGraphicsView(QWidget* parent)
  : QGraphicsView(parent)
{

}

void QZoomGraphicsView::wheelEvent(QWheelEvent *event)
{
  qreal factor = 1.2;
  if (event->delta() < 0)
    factor = 1.0 / factor;
  scale(factor, factor);
}
