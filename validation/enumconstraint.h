#ifndef ENUMCONSTRAINT_H
#define ENUMCONSTRAINT_H

#include "deviserconstraint.h"

class EnumConstraint : public DeviserConstraint
{
public:
  EnumConstraint(DeviserValidator *validator);

  virtual int analyzePackage(DeviserPackage *package);
};

#endif // ENUMCONSTRAINT_H
