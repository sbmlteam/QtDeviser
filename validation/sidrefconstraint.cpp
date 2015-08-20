#include "sidrefconstraint.h"

#include <model/devisertypes.h>

SIdRefConstraint::SIdRefConstraint(DeviserValidator* validator)
  : DeviserConstraint(validator)
{

}

int SIdRefConstraint::analyzePackage(DeviserPackage *package)
{
  if (package == NULL) return 0;

  int count = 0;

  foreach (DeviserVersion* version, package->getVersions())
  {
    foreach (DeviserClass* element, version->getElements())
    {
      foreach(DeviserAttribute* attribute, element->getAttributes())
      {
        if (attribute->getType() != "SIdRef" || !attribute->getElement().isEmpty())
          continue;

        ADD_MESSAGE("The attribute '"
                    << attribute->getName().toStdString()
                    << "' of element '"
                    << element->getName().toStdString()
                    << "'' is of type SIdRef, but has no element set. This is needed for validation purposes.");
        ++count;

      }

    }

    foreach (DeviserPlugin* element, version->getPlugins())
    {
      foreach(DeviserAttribute* attribute, element->getAttributes())
      {
        if (attribute->getType() != "SIdRef" || !attribute->getElement().isEmpty())
          continue;

        ADD_MESSAGE("The attribute '"
                    << attribute->getName().toStdString()
                    << "' of plugin '"
                    << element->getExtensionPoint().toStdString()
                    << "'' is of type SIdRef, but has no element set. This is needed for validation purposes.");
        ++count;

      }

    }
  }

  return count;

}

