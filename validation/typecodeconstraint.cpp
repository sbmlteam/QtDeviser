#include "typecodeconstraint.h"

#include <model/devisertypes.h>

TypeCodeConstraint::TypeCodeConstraint(DeviserValidator* validator)
  : DeviserConstraint(validator)
{

}

int TypeCodeConstraint::analyzePackage(DeviserPackage *package)
{
  if (package == NULL) return 0;

  int count = 0;

  foreach (DeviserVersion* version, package->getVersions())
  {
    foreach (DeviserClass* element, version->getElements())
    {
      if (!element->getTypeCode().isEmpty())
        continue;

      ADD_MESSAGE_WITH_SEVERITY(DEVISER_ERROR, "The element '"
                                << element->getName()
                                << "' has not typecode defined, this is a required attribute.");
      ++count;

    }

  }

  return count;
}

