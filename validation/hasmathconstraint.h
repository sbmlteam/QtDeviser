#ifndef HASMATHCONSTRAINT_H
#define HASMATHCONSTRAINT_H

#include "deviserconstraint.h"

class HasMathConstraint : public DeviserConstraint
{
public:
  HasMathConstraint(DeviserValidator* validator);

  virtual int analyzePackage(DeviserPackage *package);
  virtual bool fixIssue(DeviserPackage* package);
};

#endif // HASMATHCONSTRAINT_H
