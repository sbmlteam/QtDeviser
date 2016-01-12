#ifndef DIALOGPREFERENCES_H
#define DIALOGPREFERENCES_H

#include <QColor>
#include <QDialog>

#include <QStandardItemModel>
#include <QSortFilterProxyModel>


namespace Ui {
class DialogPreferences;
}


class DeviserPackage;

class DialogPreferences : public QDialog
{
  Q_OBJECT

public:
  explicit DialogPreferences(DeviserPackage* package, QWidget *parent = 0);
  ~DialogPreferences();

  void loadSettings();
  void saveSettings();


public slots:

  void addType();
  void delType();

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

  void selectValidationColor();

private:
  Ui::DialogPreferences *ui;
  QStandardItemModel* mpTypes;
  QSortFilterProxyModel* mpTypesFilter;

  DeviserPackage* mpModel;

  bool mbInitializing;

  QColor mColor;

};

#endif // DIALOGPREFERENCES_H
