#ifndef INSTANTIATIONCONSTRAINT_H
#define INSTANTIATIONCONSTRAINT_H

#include "deviserconstraint.h"

class InstantiationConstraint : public DeviserConstraint
{
public:
  InstantiationConstraint(DeviserValidator *validator);

  virtual int analyzePackage(DeviserPackage *package);
};

#endif // INSTANTIATIONCONSTRAINT_H
