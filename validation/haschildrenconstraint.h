#ifndef HASCHILDRENCONSTRAINT_H
#define HASCHILDRENCONSTRAINT_H

#include "deviserconstraint.h"

class HasChildrenConstraint : public DeviserConstraint
{
public:
  HasChildrenConstraint(DeviserValidator* validator);

  virtual int analyzePackage(DeviserPackage *package);
  virtual bool fixIssue(DeviserPackage* package);
};

#endif // HASCHILDRENCONSTRAINT_H
