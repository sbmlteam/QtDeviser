#include "enumconstraint.h"

#include <model/devisertypes.h>

EnumConstraint::EnumConstraint(DeviserValidator *validator)
  : DeviserConstraint(validator)
{

}

int EnumConstraint::analyzePackage(DeviserPackage *package)
{
  int errors = 0;
  foreach(DeviserVersion* version, package->getVersions())
  {

    foreach(DeviserEnum* pEnum, version->getEnums())
    {
      int count = 0;

      if (pEnum->getName().isEmpty())
      {
        ADD_MESSAGE_WITH_SEVERITY(DEVISER_ERROR,
                                  "There is an unnamed enum in version '"
                                  << version->toString()
                                  << "', this is a required attribute");
        ++errors;
      }

      foreach(DeviserEnumValue* pValue, pEnum->getValues())
      {

        ++count;

        if (pValue->getName().isEmpty())
        {
          ADD_MESSAGE_WITH_SEVERITY(DEVISER_ERROR,
                                    "EnumValue " << count
                                    << " of enum '"
                                    << pEnum->getName()
                                    << "' has no name, this is a required attribute");
          ++errors;
        }

        if (pValue->getValue().isEmpty())
        {
          ADD_MESSAGE_WITH_SEVERITY(DEVISER_ERROR,
                                    "EnumValue " << count
                                    << " of enum '"
                                    << pEnum->getName()
                                    << "' has no value, this is a required attribute");
          ++errors;
        }

      }
    }
  }

  return errors;
}
