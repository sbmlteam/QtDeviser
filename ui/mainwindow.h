#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <validation/deviservalidator.h>

namespace Ui {
class MainWindow;
}

class QTreeWidgetItem;

class FormDeviserPackage;
class FormDeviserVersion;
class FormDeviserEnum;
class FormDeviserMapping;
class FormDeviserClass;
class FormDeviserPlugin;

class DeviserPackage;
class DeviserBase;
class DeviserVersion;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);

  ~MainWindow();

  void setCurrentFile(const QString&);
  DeviserVersion* getCurrentVersion();

public slots:
  void showAbout();
  void addClass();
  void addEnum();
  void addPlugin();
  void addVersion();
  void editPreferences();
  void fixErrors();
  void generate();
  void newModel();
  void openFile();
  void openFile(const QString&);
  void saveFile();
  void saveFileAs();
  void saveAsFile(const QString&);
  void showUML();
  void validateDescription();

  void updateUI();
  void displayElement(DeviserBase* element);
  void treeElementRenamed(const QString&, const QString&,
                          const DeviserVersion* version);
  void selectionChanged();
  void deleteSelected();
  void duplicateSelected();


protected:
  DeviserBase* getDeviserItemForTreeView(QTreeWidgetItem* item);

private:
  Ui::MainWindow *ui;

  FormDeviserPackage* ctrlPackage;
  FormDeviserVersion* ctrlVersion;
  FormDeviserEnum* ctrlEnum;
  FormDeviserMapping* ctrlMapping;
  FormDeviserClass* ctrlClass;
  FormDeviserPlugin* ctrlPlugin;

  DeviserPackage* mModel;
  DeviserVersion* mCurrentVersion;
  DeviserBase* mCurrentElement;

  QString mFileName;

  DeviserValidator mValidator;

};

#endif // MAINWINDOW_H
