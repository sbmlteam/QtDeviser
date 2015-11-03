#include "haschildrenconstraint.h"

#include <model/devisertypes.h>

HasChildrenConstraint::HasChildrenConstraint(DeviserValidator* validator)
  : DeviserConstraint(validator)
{

}


int
HasChildrenConstraint::analyzePackage(DeviserPackage *package)
{
  int result = 0;

  foreach(DeviserVersion* version, package->getVersions())
  {
    foreach (DeviserClass* item, version->getElements())
    {
      bool hasChildren = item->hasChildren();
      int numChildren = 0;

      foreach (DeviserAttribute* attr, item->getAttributes())
      {
        if ((attr->getType() == "element" && attr->getName() != "math") ||
            attr->getType() == "lo_element" ||
            attr->getType() == "inline_lo_element")
          ++numChildren;
      }

      foreach (DeviserListOfAttribute* attr, item->getListOfAttributes())
      {
        if (attr->getType() == "element" ||
            attr->getType() == "lo_element" ||
            attr->getType() == "inline_lo_element")
          ++numChildren;
      }

      if (hasChildren && numChildren == 0)
      {
        ADD_MESSAGE_WITH_SEVERITY(DEVISER_IGNORE, "Class: '" << item->getName() << "' has hasChildren=true, but no children.");
      }

      if (!hasChildren && numChildren > 0)
      {
        ADD_MESSAGE_WITH_SEVERITY(DEVISER_IGNORE, "Class: '" << item->getName() << "' has hasChildren=false, but children.");
      }
    }
  }


  return result;
}

bool
HasChildrenConstraint::fixIssue(DeviserPackage* package)
{
  bool result = false;

  foreach(DeviserVersion* version, package->getVersions())
  {
    foreach (DeviserClass* item, version->getElements())
    {
      bool hasChildren = item->hasChildren();
      int numChildren = 0;

      foreach (DeviserAttribute* attr, item->getAttributes())
      {
        if ((attr->getType() == "element" && attr->getName() != "math") ||
            attr->getType() == "lo_element" ||
            attr->getType() == "inline_lo_element")
          ++numChildren;
      }

      foreach (DeviserListOfAttribute* attr, item->getListOfAttributes())
      {
        if (attr->getType() == "element" ||
            attr->getType() == "lo_element" ||
            attr->getType() == "inline_lo_element")
          ++numChildren;
      }

      if (hasChildren && numChildren == 0)
      {
        item->setHasChildren(false);
        result = true;
      }

      if (!hasChildren && numChildren > 0)
      {
        item->setHasChildren(true);
        result = true;
      }
    }
  }


  return result;
}
