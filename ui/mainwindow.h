#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <validation/deviservalidator.h>

namespace Ui {
class MainWindow;
}

class QTreeWidgetItem;
class QHelpEngine;

class FormDeviserPackage;
class FormDeviserVersion;
class FormDeviserEnum;
class FormDeviserMapping;
class FormDeviserClass;
class FormDeviserPlugin;
class FormDeviserLanguage;

class HelpWindow;

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
  void showHelp();
  void showAboutQt();
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
  void editLanguage();
  void saveTempFile();
  /**
   * validates the description, returning the code of the
   * dialog.
   *
   * @return the dialog exit code
   */
  int validateDescription();

  void copyUML();
  void copyXML();

  void updateUI();
  void displayElement(DeviserBase* element);
  void treeElementRenamed(const QString&, const QString&,
                          const DeviserVersion* version);
  void selectionChanged();
  void deleteSelected();

  DeviserBase *findNextItem(QTreeWidgetItem* item, DeviserBase* currentDeviserItem);

  void duplicateSelected();

  void refreshRecentFiles();

  void openRecentFile(QAction *);

  void documentModified();

  bool askForSaveOrStop();

  void reloadDocument();

  void generateContextMenuForTree(const QPoint& point);


protected:
  DeviserBase* getDeviserItemForTreeView(QTreeWidgetItem* item);
  QTreeWidgetItem* getTreeItemForDeviserItem(DeviserBase* item);
  void selectTreeItem(DeviserBase *item);
  void closeEvent(QCloseEvent *event);
  void dragEnterEvent(QDragEnterEvent *e);
  void dropEvent(QDropEvent *e);

  void timerEvent(QTimerEvent* event);

private:
  Ui::MainWindow *ui;

  FormDeviserPackage* ctrlPackage;
  FormDeviserVersion* ctrlVersion;
  FormDeviserEnum* ctrlEnum;
  FormDeviserMapping* ctrlMapping;
  FormDeviserClass* ctrlClass;
  FormDeviserPlugin* ctrlPlugin;
  FormDeviserLanguage* ctrlLanguage;

  DeviserPackage* mModel;
  DeviserVersion* mCurrentVersion;
  DeviserBase* mCurrentElement;

  QString mFileName;

  QString mTempFilename;

  DeviserValidator mValidator;

  HelpWindow* mpHelpWindow;
  QHelpEngine* mpHelpEngine;

  int mAutoSaveTime;


};

#endif // MAINWINDOW_H
