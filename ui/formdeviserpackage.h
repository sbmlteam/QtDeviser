#ifndef FORMDEVISERPACKAGE_H
#define FORMDEVISERPACKAGE_H

#include <QWidget>

namespace Ui {
class FormDeviserPackage;
}

class DeviserPackage;

class FormDeviserPackage : public QWidget
{
  Q_OBJECT

public:
  explicit FormDeviserPackage(QWidget *parent = 0);
  ~FormDeviserPackage();

  void initializeFrom(DeviserPackage* package);

public slots:
  void browseImplementation();
  void browseDeclaration();
  void browseCopyright();
  void additionalCodeStateChanged(int);
  void requiredStateChanged(int);
  void copyrightChanged(const QString&);
  void offsetChanged(const QString&);
  void numberChanged(const QString&);
  void nameChanged(const QString&);
  void implementationChanged(const QString&);
  void fullNameChanged(const QString&);
  void declarationChanged(const QString&);
  void showNumbersAndOffsets();

  void nameModified(const QString &);
  void fullNameModified(const QString&);
  void numberModified(const QString&);
  void offsetModified(const QString&);

private:
  Ui::FormDeviserPackage *ui;
  DeviserPackage* mPackage;

  bool mbInitializing;
};

#endif // FORMDEVISERPACKAGE_H
