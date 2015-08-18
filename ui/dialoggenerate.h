#ifndef DIALOGGENERATE_H
#define DIALOGGENERATE_H

#include <QDialog>
#include <QProcess>
#include <QThread>

namespace Ui {
class DialogGenerate;
}


class DeviserPackage;
class DeviserVersion;

class WorkerThread : public QThread
{
  Q_OBJECT

public:

  void setProcess(QProcess* pProcess,
                  const QString& fileName,
                  const QStringList& args)
  {
    mpProcess = pProcess;
    mFileName = fileName;
    mArgs = args;
  }

  void run()
  {
    if (mpProcess == NULL)
      return;

    mpProcess->start(mFileName, mArgs);

    //QString result;
    ///* expensive or blocking operation  */
    //emit resultReady(result);
  }

signals:
  void resultReady(const QString &s);

private:
  QProcess* mpProcess;
  QString mFileName;
  QStringList mArgs;
};


class DialogGenerate : public QDialog
{
  Q_OBJECT

public:
  explicit DialogGenerate(QWidget *parent = 0);
  ~DialogGenerate();

  void loadModel(DeviserPackage* package,
                 DeviserVersion* version,
                 const QString& fileName);


public slots:
  void testLibSBML();
  void removeFromSourceDir();
  void openOutputDir();
  void generateTex();
  void generatePackageCode();
  void compileTex();
  void compileLibSBML();
  void compileDependencies();
  void browseOutputDir();
  void addToSourceDir();

  void addMessage(const QString& message = "");
  void finished(int exitCode, QProcess::ExitStatus exitStatus);
  void readyOutput();
  void error(QProcess::ProcessError);

private:
  Ui::DialogGenerate *ui;
  DeviserPackage* mPackage;
  DeviserVersion* mVersion;
  QProcess *mpProcess;

  WorkerThread workerThread;
};

#endif // DIALOGGENERATE_H
