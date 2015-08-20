#ifndef SIDREFCONSTRAINT_H
#define SIDREFCONSTRAINT_H

#include "deviserconstraint.h"

class SIdRefConstraint : public DeviserConstraint
{
public:
  SIdRefConstraint(DeviserValidator* validator);

  virtual int analyzePackage(DeviserPackage *package);

};

#endif // SIDREFCONSTRAINT_H
