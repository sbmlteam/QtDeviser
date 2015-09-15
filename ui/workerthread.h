#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QProcess>
#include <QStringList>

class QDialog;

class WorkerThread : public QThread
{
  Q_OBJECT

public:

  WorkerThread(QDialog* parent = NULL);


  void setProcess(QProcess* pProcess,
                  const QString& fileName,
                  const QStringList& args);

  void run();

public slots:
  void finished(int exitCode, QProcess::ExitStatus exitStatus);

signals:
  void finished();

private:
  QDialog* mpParent;
  QProcess* mpProcess;
  QString mFileName;
  QStringList mArgs;

};
#endif // WORKERTHREAD_H
