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

      if (!element->getDefaultTypeCode().isEmpty())
        continue;

      ADD_MESSAGE_WITH_SEVERITY(DEVISER_ERROR, "The element '"
                                << element->getName()
                                << "' has no typecode defined, and it can not be generated automatically.");
      ++count;

    }
  }

  return count;
}

