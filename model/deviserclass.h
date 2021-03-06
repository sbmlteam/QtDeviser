#ifndef DEVISERCLASS_H
#define DEVISERCLASS_H

#include <model/deviserbase.h>

class DeviserAttribute;
class DeviserListOfAttribute;
class DeviserConcrete;

class DeviserClass : public DeviserBase
{
  Q_OBJECT

public:
  DeviserClass();
  DeviserClass(const DeviserClass& other);
  DeviserClass& operator= (const DeviserClass& rhs);

  virtual void initializeFrom(const QDomElement& element);

  const QString& getName() const;
  void setName(const QString& name);

  const QString& getBaseClass() const;
  void setBaseClass(const QString& baseClass);

  const QString& getTypeCode() const;
  void setTypeCode(const QString& typeCode);

  QString getDefaultTypeCode() const;


  bool hasListOf() const;
  void setHasListOf(bool hasListOf);

  bool hasMath() const;
  void setHasMath(bool hasMath);

  bool hasChildren() const;
  void setHasChildren(bool hasChildren);

  bool isBaseClass() const;
  void setIsBaseClass(bool isBaseClass);

  const QString& getElementName() const;
  void setElementName(const QString& elementName);

  const QString& getListOfName() const;
  void setListOfName(const QString& listOfName);

  const QString& getListOfClassName() const;
  void setListOfClassName(const QString& listOfClassName);

  QString getActualListOfName() const;

  bool getChildrenOverwriteElementName() const;
  void setChildrenOverwriteElementName(bool childrenOverwriteElementName);

  const QString& getAdditionalDeclarations() const;
  void setAdditionalDeclarations(const QString& additionalDeclarations);

  const QString& getAdditionalDefinitions() const;
  void setAdditionalDefinitions(const QString& additionalDefinitions);

  int getMinNumberChildren() const;
  void setMinNumberChildren(int minNoChildren);

  int getMaxNumberChildren() const;
  void setMaxNumberChildren(int maxNoChildren);

  const QList<DeviserAttribute*>& getAttributes() const;
  QList<DeviserAttribute*>& getAttributes();

  const QList<DeviserListOfAttribute*>& getListOfAttributes() const;
  QList<DeviserListOfAttribute*>& getListOfAttributes();

  const QList<DeviserConcrete*>& getConcretes() const;
  QList<DeviserConcrete*>& getConcretes();

  DeviserAttribute* createAttribute();
  DeviserListOfAttribute* createListOfAttribute();
  DeviserConcrete* createConcrete();

  virtual void writeAttributesTo(QXmlStreamWriter& writer) const;
  virtual void writeElementsTo(QXmlStreamWriter& writer) const;
  virtual void writeTo(QXmlStreamWriter& writer) const;

  virtual QString toYuml(bool usecolor = true) const;

  void getUsedTypes(QStringList& list) const;

signals:
  void nameChanged(const QString& oldName, const QString& newName,
                   const DeviserVersion* version);
  void baseClassChanged();
  void typeCodeChanged();
  void hasListOfChanged();
  void childrenOverwriteElementNameChanged();
  void hasMathChanged();
  void hasChildrenChanged();
  void isBaseClassChanged();
  void elementNameChanged();
  void listOfNameChanged();
  void listOfClassNameChanged();
  void additionalDeclarationsChanged();
  void additionalDefinitionsChanged();
  void minNoChildrenChanged();
  void maxNoChildrenChanged();



protected:
  QString mName;
  QString mBaseClass;
  QString mTypeCode;

  bool mHasListOf;
  bool mHasMath;
  bool mHasChildren;
  bool mIsBaseClass;

  QString mElementName;
  QString mListOfName;
  QString mListOfClassName;

  bool mChildrenOverwriteElementName;

  QString mAdditionalDeclarations;
  QString mAdditionalDefinitions;

  int mMinNumberChildren;
  int mMaxNumberChildren;

  QList<DeviserAttribute*> mAttributes;
  QList<DeviserListOfAttribute*> mListOfAttributes;
  QList<DeviserConcrete*> mConcretes;

  friend class FormDeviserClass;
};

#endif // DEVISERCLASS_H
