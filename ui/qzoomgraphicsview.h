#ifndef QZOOMGRAPHICSVIEW_H
#define QZOOMGRAPHICSVIEW_H

#include <QGraphicsView>

class QWidget;

class QZoomGraphicsView : public QGraphicsView
{
  Q_OBJECT
public:
  QZoomGraphicsView(QWidget* parent);
protected:
  virtual void wheelEvent(QWheelEvent * event);
};

#endif // QZOOMGRAPHICSVIEW_H
