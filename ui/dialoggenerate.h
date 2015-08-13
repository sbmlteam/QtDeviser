#ifndef DIALOGGENERATE_H
#define DIALOGGENERATE_H

#include <QDialog>

namespace Ui {
class DialogGenerate;
}


class DeviserPackage;

class DialogGenerate : public QDialog
{
  Q_OBJECT

public:
  explicit DialogGenerate(QWidget *parent = 0);
  ~DialogGenerate();

  void loadModel(DeviserPackage* package);

private:
  Ui::DialogGenerate *ui;
  DeviserPackage* mPackage;
};

#endif // DIALOGGENERATE_H
