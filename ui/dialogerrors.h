#ifndef DIALOGERRORS_H
#define DIALOGERRORS_H

#include <QDialog>
#include <QList>

namespace Ui {
class DialogErrors;
}

class DeviserMessage;

class DialogErrors : public QDialog
{
  Q_OBJECT

public:
  explicit DialogErrors(const QList<DeviserMessage*>& errors,
                        QWidget *parent = 0);
  ~DialogErrors();

public slots:
  void copyErrors();

private:
  Ui::DialogErrors *ui;
  QList<DeviserMessage*> mErrors;
  QString mMessages;
};

#endif // DIALOGERRORS_H
