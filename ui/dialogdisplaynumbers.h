#ifndef DIALOGDISPLAYNUMBERS_H
#define DIALOGDISPLAYNUMBERS_H

#include <QDialog>

namespace Ui {
class DialogDisplayNumbers;
}

class DialogDisplayNumbers : public QDialog
{
  Q_OBJECT

public:
  explicit DialogDisplayNumbers(QWidget *parent = 0);
  ~DialogDisplayNumbers();

private:
  Ui::DialogDisplayNumbers *ui;
};

#endif // DIALOGDISPLAYNUMBERS_H
