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
            ++result;
            ADD_MESSAGE("Class: '" << item->getName()
                        << "' uses BaseClass '" << item->getBaseClass()
                        << "', which is not marked as 'isBaseClass'.");
          }
        }
      }

      if (isAbstract && countUses== 0)
      {
        ++result;
        ADD_MESSAGE("Class: '" << current->getName()
                    << "' is marked as 'isBaseClass', but not used.");
      }

      if (isAbstract)
      {
        if (current->getConcretes().size() == 0)
        {
          ++result;
          ADD_MESSAGE_WITH_SEVERITY(DEVISER_ERROR, "The class '"
            << current->getName()
            << "' is marked as 'isBaseClass' but no instantiation classes are listed.");
        }
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
            result = true;
          }
        }
      }

      if (isAbstract && countUses== 0)
      {
        current->setIsBaseClass(false);
        result = true;
      }

    }
  }

  return result;
}
