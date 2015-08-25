#include "isbaseclassconstraint.h"

#include <model/devisertypes.h>

IsBaseClassConstraint::IsBaseClassConstraint(DeviserValidator* validator)
  : DeviserConstraint(validator)
{

}

int
IsBaseClassConstraint::analyzePackage(DeviserPackage *package)
{
  int result = 0;

  foreach(DeviserVersion* version, package->getVersions())
  {
    foreach (DeviserClass* current, version->getElements())
    {
      bool isAbstract = current->isBaseClass();

      int countUses = 0;
      foreach (DeviserClass* item, version->getElements())
      {
        if (item == current) continue;
        if (item->getBaseClass() == current->getName())
        {
          ++countUses;
          if (!isAbstract)
          {
            ADD_MESSAGE("Class: '" << item->getName()
                        << "' uses BaseClass '" << item->getBaseClass()
                        << "', which is not marked as 'isBaseClass'.");
          }
        }
      }

      if (isAbstract && countUses== 0)
      {
        ADD_MESSAGE("Class: '" << current->getName()
                    << "' is marked as 'isBaseClass', but not used.");
      }

    }
  }


  return result;
}

bool
IsBaseClassConstraint::fixIssue(DeviserPackage* package)
{
  bool result = false;

  foreach(DeviserVersion* version, package->getVersions())
  {
    foreach (DeviserClass* current, version->getElements())
    {
      bool isAbstract = current->isBaseClass();

      int countUses = 0;
      foreach (DeviserClass* item, version->getElements())
      {
        if (item == current) continue;
        if (item->getBaseClass() == current->getName())
        {
          ++countUses;
          if (!isAbstract)
          {
            current->setIsBaseClass(true);
          }
        }
      }

      if (isAbstract && countUses== 0)
      {
        current->setIsBaseClass(false);
      }

    }
  }

  return result;
}
