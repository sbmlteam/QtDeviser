#ifndef DIALOGPREFERENCES_H
#define DIALOGPREFERENCES_H

#include <QDialog>


namespace Ui {
class DialogPreferences;
}


class DeviserPackage;

class DialogPreferences : public QDialog
{
  Q_OBJECT

public:
  explicit DialogPreferences(QWidget *parent = 0);
  ~DialogPreferences();

  void loadSettings();
  void saveSettings();


public slots:
  void browsePython();
  void browseDeviserRepo();
  void browseOutputDir();
  void browseSbmlPkgSpec();
  void browseMikTex();
  void browseLibSBML();
  void selectCompiler();
  void browseCMakeExecutable();
  void browseDependencies();
  void browseSWIG();
  void browsePythonInclude();
  void browsePythonLib();

private:
  Ui::DialogPreferences *ui;
};

#endif // DIALOGPREFERENCES_H
