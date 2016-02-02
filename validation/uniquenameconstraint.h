#ifndef UNIQUENAMECONSTRAINT_H
#define UNIQUENAMECONSTRAINT_H

#include "deviserconstraint.h"

class UniqueNameConstraint : public DeviserConstraint
{
public:
  UniqueNameConstraint(DeviserValidator* validator);

  virtual int analyzePackage(DeviserPackage *package);

};

#endif // UNIQUENAMECONSTRAINT_H
