#ifndef DIALOGGENERATE_H
#define DIALOGGENERATE_H

#include <QDialog>

namespace Ui {
class DialogGenerate;
}

class DialogGenerate : public QDialog
{
  Q_OBJECT

public:
  explicit DialogGenerate(QWidget *parent = 0);
  ~DialogGenerate();

private:
  Ui::DialogGenerate *ui;
};

#endif // DIALOGGENERATE_H
