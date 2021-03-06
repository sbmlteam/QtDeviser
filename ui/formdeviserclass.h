#ifndef FORMDEVISERCLASS_H
#define FORMDEVISERCLASS_H

#include <QWidget>
#include <QCheckBox>

namespace Ui {
class FormDeviserClass;
}

class QTableWidgetItem;
class DeviserClass;
class QSortFilterProxyModel;
class AttributesModel;
class LoAttributesModel;
class ConcretesModel;

class FormDeviserClass : public QWidget
{
  Q_OBJECT

public:
  explicit FormDeviserClass(QWidget *parent = 0);
  ~FormDeviserClass();

  void initializeFrom(DeviserClass* element);

public slots:
  void browseDefinitionClick();
  void browseDeclarationClick();
  void delConcrete();
  void delListOfAttribute();
  void delAttribute();
  void addListOfAttribute();
  void addConcrete();
  void addAttribute();
  void xmlElementNameChanged(const QString&);
  void typeCodeChanged(const QString&);
  void nameChanged(const QString&);
  void minNoChildrenChanged(const QString&);
  void maxNoChildrenChanged(const QString&);
  void listOfNameChanged(const QString&);
  void listOfClassNameChanged(const QString&);
  void definitionChanged(const QString&);
  void declarationChanged(const QString&);
  void baseClassChanged(const QString&);
  void requiresStateChanged(int);
  void isBaseClassStateChanged(int);
  void hasListOfStateChanged(int);
  void childrenOverwriteElementNameChanged(int);

  void defaultXmlElementName();
  void defaultTypeCode();
  void defaultListOfName();
  void defaultBaseClass();
  void defaultListOfClassName();

  void defaultToggled(bool isChecked);

  void nameModified(const QString&);
  void typeCodeModified(const QString&);

private:
  Ui::FormDeviserClass *ui;
  DeviserClass* mElement;

  AttributesModel* mpAttributes;
  QSortFilterProxyModel* mpAttributesFilter;

  LoAttributesModel* mpLoAttributes;
  QSortFilterProxyModel* mpLoAttributesFilter;

  ConcretesModel* mpConcretes;
  QSortFilterProxyModel* mpConcretesFilter;

  bool mbInitializing;

};

#endif // FORMDEVISERCLASS_H
