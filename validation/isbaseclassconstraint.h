#ifndef ISBASECLASSCONSTRAINT_H
#define ISBASECLASSCONSTRAINT_H

#include "deviserconstraint.h"

class IsBaseClassConstraint : public DeviserConstraint
{
public:
  IsBaseClassConstraint(DeviserValidator* validator);

  virtual int analyzePackage(DeviserPackage *package);
  virtual bool fixIssue(DeviserPackage* package);
};

#endif // ISBASECLASSCONSTRAINT_H
