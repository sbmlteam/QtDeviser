#ifndef SIDREFCONSTRAINT_H
#define SIDREFCONSTRAINT_H

#include <QString>
#include <QStringList>

#include "deviserconstraint.h"

class DeviserAttribute;

class AttributeConstraints : public DeviserConstraint
{
public:
  AttributeConstraints(DeviserValidator* validator);

  virtual int analyzePackage(DeviserPackage *package);

protected:

  virtual bool checkAttribute(DeviserAttribute *attribute,
                              const QString& name);

  QStringList mKnownElementTypes;
  QStringList mKnownTypes;
};

#endif // SIDREFCONSTRAINT_H
