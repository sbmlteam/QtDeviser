#ifndef SIDREFCONSTRAINT_H
#define SIDREFCONSTRAINT_H

#include <QString>
#include <QStringList>

#include "deviserconstraint.h"

class DeviserAttribute;
class DeviserVersion;

class AttributeConstraints : public DeviserConstraint
{
public:
  AttributeConstraints(DeviserValidator* validator);

  virtual int analyzePackage(DeviserPackage *package);

protected:

  virtual bool checkAttribute(DeviserAttribute *attribute,
                              const QString& name);

  virtual bool checkAttributeLOElement(DeviserAttribute *attribute,
                                       DeviserVersion* version);

  QStringList mKnownElementTypes;
  QStringList mKnownTypes;
  QStringList mClasses;
};

#endif // SIDREFCONSTRAINT_H
