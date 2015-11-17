#include "instantiationconstraint.h"

#include <model/devisertypes.h>

InstantiationConstraint::InstantiationConstraint(DeviserValidator *validator)
  : DeviserConstraint(validator)
{

}

int InstantiationConstraint::analyzePackage(DeviserPackage *package)
{
  int errors = 0;

  foreach (DeviserVersion* version, package->getVersions())
  {
    foreach(DeviserClass* pClass, version ->getElements())
    {
      foreach(DeviserConcrete* instantiation, pClass->getConcretes())
      {
        if (instantiation->getElement().isEmpty())
        {
          ADD_MESSAGE_WITH_SEVERITY(DEVISER_ERROR, "The instantiation '"
                                    << instantiation->getName()
                                    << "' has no element defined, this is a required attribute.");
          ++errors;
        }
      }
    }

  }

  return errors;
}
