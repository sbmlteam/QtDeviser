#ifndef FORMDEVISERCLASS_H
#define FORMDEVISERCLASS_H

#include <QWidget>

namespace Ui {
class FormDeviserClass;
}

class DeviserClass;

class FormDeviserClass : public QWidget
{
  Q_OBJECT

public:
  explicit FormDeviserClass(QWidget *parent = 0);
  ~FormDeviserClass();

  void initializeFrom(DeviserClass* element);

private:
  Ui::FormDeviserClass *ui;
  DeviserClass* mElement;
};

#endif // FORMDEVISERCLASS_H
