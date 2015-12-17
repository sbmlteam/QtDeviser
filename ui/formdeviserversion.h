#ifndef FORMDEVISERVERSION_H
#define FORMDEVISERVERSION_H

#include <QWidget>

namespace Ui {
class FormDeviserVersion;
}

class DeviserVersion;

class FormDeviserVersion : public QWidget
{
  Q_OBJECT

public:
  explicit FormDeviserVersion(QWidget *parent = 0);
  ~FormDeviserVersion();

  void initializeFrom(DeviserVersion* version);

public slots:
  void downPressed();
  void upPressed();
  void levelChanged(const QString&);
  void versionChanged(const QString&);
  void pkgVersionChanged(const QString&);
  void pkgVersionModified(const QString&);
  void ignorePackageVersionChanged();

private:
  Ui::FormDeviserVersion *ui;
  DeviserVersion* mVersion;

  bool mbInitializing;
};


#endif // FORMDEVISERVERSION_H
