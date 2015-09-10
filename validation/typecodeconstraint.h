#ifndef TYPECODECONSTRAINT_H
#define TYPECODECONSTRAINT_H

#include "deviserconstraint.h"

class TypeCodeConstraint : public DeviserConstraint
{
public:
  TypeCodeConstraint(DeviserValidator* validator);

  virtual int analyzePackage(DeviserPackage *package);
};

#endif // TYPECODECONSTRAINT_H
