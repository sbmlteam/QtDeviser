#ifndef PACKAGECONSTRAINTS_H
#define PACKAGECONSTRAINTS_H

#include "deviserconstraint.h"

class PackageConstraints : public DeviserConstraint
{
public:
  PackageConstraints(DeviserValidator* validator);

  virtual int analyzePackage(DeviserPackage *package);
  virtual bool fixIssue(DeviserPackage* package);
};

#endif // PACKAGECONSTRAINTS_H
