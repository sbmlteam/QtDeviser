#ifndef FORMDEVISERPLUGIN_H
#define FORMDEVISERPLUGIN_H

#include <QWidget>

namespace Ui {
class FormDeviserPlugin;
}

class DeviserPlugin;
class QTableWidgetItem;
class AttributesModel;
class QSortFilterProxyModel;

class FormDeviserPlugin : public QWidget
{
  Q_OBJECT

public:
  explicit FormDeviserPlugin(QWidget *parent = 0);
  ~FormDeviserPlugin();

  void initializeFrom(DeviserPlugin* plugin);

public slots:
  void typeCodeChanged(const QString&);
  void typeCodeModified(const QString&);
  void packageChanged(const QString&);
  void packageModified(const QString&);
  void implementationChanged(const QString&);
  void extensionPointChanged(const QString&);
  void extensionModified(const QString&);
  void declarationChanged(const QString&);

  void upClicked();
  void downClicked();
  void addChild();
  void delChild();
  void browseImplementation();
  void browseDeclaration();
  void delAttribute();
  void addAttribute();
  void additionalCodeStateChanged(int);
  void hasAttributesStateChanged(int);
  void fromCoreStateChanged(int);

private:
  Ui::FormDeviserPlugin *ui;
  DeviserPlugin* mPlugin;

  AttributesModel* mpAttributes;
  QSortFilterProxyModel* mpAttributesFilter;

  bool mbInitializing;
};

#endif // FORMDEVISERPLUGIN_H
