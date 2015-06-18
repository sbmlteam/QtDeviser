#ifndef DIALOGUML_H
#define DIALOGUML_H

#include <QDialog>

namespace Ui {
class DialogUML;
}

class DialogUML : public QDialog
{
  Q_OBJECT

public:
  explicit DialogUML(QWidget *parent = 0);
  ~DialogUML();

private:
  Ui::DialogUML *ui;
};

#endif // DIALOGUML_H
