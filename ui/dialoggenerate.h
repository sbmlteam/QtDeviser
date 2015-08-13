#ifndef DIALOGGENERATE_H
#define DIALOGGENERATE_H

#include <QDialog>
#include <QProcess>

namespace Ui {
class DialogGenerate;
}


class DeviserPackage;

class DialogGenerate : public QDialog
{
  Q_OBJECT

public:
  explicit DialogGenerate(QWidget *parent = 0);
  ~DialogGenerate();

  void loadModel(DeviserPackage* package, const QString& fileName);


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
  QProcess *mpProcess;
};

#endif // DIALOGGENERATE_H
