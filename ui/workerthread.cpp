#include "workerthread.h"

#include <QDialog>
#include <QProcess>
#include <QStringList>
#include <QApplication>

WorkerThread::WorkerThread(QDialog *parent)
  : QThread(parent)
  , mpParent(parent)
  , mpProcess(NULL)
  , mFileName()
  , mArgs()
{

}

void WorkerThread::setProcess(QProcess *pProcess,
                              const QString &fileName,
                              const QStringList &args)
{
  mpProcess = pProcess;
  mFileName = fileName;
  mArgs = args;
}

void WorkerThread::run()
{
  if (mpProcess == NULL)
    return;

  mpProcess->start(mFileName, mArgs);


  connect(mpProcess, SIGNAL(finished(int, QProcess::ExitStatus)),
    this, SLOT(finished(int, QProcess::ExitStatus)));
  connect(mpProcess, SIGNAL(readyReadStandardOutput()),
    mpParent, SLOT(readyOutput()));
  connect(mpProcess, SIGNAL(readyReadStandardError()),
    mpParent, SLOT(readyOutput()));
  connect(mpProcess, SIGNAL(error(QProcess::ProcessError)),
    mpParent, SLOT(error(QProcess::ProcessError)));

  while (!mpProcess->waitForFinished(5000))
  {
    qApp->processEvents();
  }

}

void
WorkerThread::finished(int /*exitCode*/,
                       QProcess::ExitStatus /*exitStatus*/)
{
  mpProcess = NULL;
  emit finished();
}
