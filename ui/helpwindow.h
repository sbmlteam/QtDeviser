#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QMainWindow>

namespace Ui {
  class HelpWindow;
  }

class QHelpEngine;
class QHelpSearchEngine;

class HelpWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit HelpWindow(QWidget *parent = 0);
  void setHelpEngine(QHelpEngine* engine);
  ~HelpWindow();

public slots:
  void search();

private:
  Ui::HelpWindow *ui;
  QHelpEngine* mpHelpEngine;
  QHelpSearchEngine * mpSearchEngine;
};

#endif // HELPWINDOW_H
