#ifndef FORMDEVISERCLASS_H
#define FORMDEVISERCLASS_H

#include <QWidget>

namespace Ui {
class FormDeviserClass;
}

class QTableWidgetItem;
class DeviserClass;

class FormDeviserClass : public QWidget
{
  Q_OBJECT

public:
  explicit FormDeviserClass(QWidget *parent = 0);
  ~FormDeviserClass();

  void initializeFrom(DeviserClass* element);

public slots:
  void concreteChanged(QTableWidgetItem*);
  void listOfAttributeChanged(QTableWidgetItem*);
  void attributeChanged(QTableWidgetItem*);
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

private:
  Ui::FormDeviserClass *ui;
  DeviserClass* mElement;
};

#endif // FORMDEVISERCLASS_H
