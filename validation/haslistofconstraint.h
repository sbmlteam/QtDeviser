#ifndef HASLISTOFCONSTRAINT_H
#define HASLISTOFCONSTRAINT_H

#include "deviserconstraint.h"

class HasListOfConstraint : public DeviserConstraint
{
public:
  HasListOfConstraint(DeviserValidator* validator);

  virtual int analyzePackage(DeviserPackage *package);
  virtual bool fixIssue(DeviserPackage* package);
};

#endif // HASLISTOFCONSTRAINT_H
