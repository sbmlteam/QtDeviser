#ifndef DIALOGGENERATE_H
#define DIALOGGENERATE_H

#include <QDialog>
#include <QProcess>
#include <QThread>

#include "workerthread.h"

namespace Ui {
class DialogGenerate;
}


class DeviserPackage;
class DeviserVersion;


class DialogGenerate : public QDialog
{
  Q_OBJECT

  enum  Actions
  {
    COMPILE_TEX,
    COMPILE_LIBSBML,
    COMPILE_DEPENDENCIES,
    GENERATE_TEX,
    GENERATE_PACKAGE_CODE,
    OTHER
  };

public:
  explicit DialogGenerate(QWidget *parent = 0);
  ~DialogGenerate();

  void loadModel(DeviserPackage* package,
                 DeviserVersion* version,
                 const QString& fileName);

  void createImagesIn(const QString& destDir);
  void downloadFiles(const QString& yuml, const QString& baseName);

public slots:
  void testLibSBML();
  void removeFromSourceDir();
  void openOutputDir();
  void generateTex(bool withFigures=false);
  void generateTexWithFigures();
  void generatePackageCode();
  void compileTex();
  void compileLibSBML();
  void compileDependencies();
  void browseOutputDir();
  void addToSourceDir();

  void addMessage(const QString& message = "");
  void finished(int code = 0);
  void readyOutput();
  void error(QProcess::ProcessError);

  void toggleControls(bool enable) const;

private:
  Ui::DialogGenerate *ui;
  DeviserPackage* mPackage;
  DeviserVersion* mVersion;
  QProcess *mpProcess;

  WorkerThread workerThread;

  Actions mLastAction;

};

#endif // DIALOGGENERATE_H
