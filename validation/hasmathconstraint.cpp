#include "hasmathconstraint.h"

#include <model/devisertypes.h>

HasMathConstraint::HasMathConstraint(DeviserValidator* validator)
  : DeviserConstraint(validator)
{

}

int
HasMathConstraint::analyzePackage(DeviserPackage *package)
{
  int result = 0;

  foreach(DeviserVersion* version, package->getVersions())
  {
    foreach (DeviserClass* item, version->getElements())
    {
      bool hasMath = item->hasMath();
      int numChildren = 0;
      foreach (DeviserAttribute* attr, item->getAttributes())
      {
        if (attr->getName() == "math")
          ++numChildren;
      }

      foreach (DeviserListOfAttribute* attr, item->getListOfAttributes())
      {
        if (attr->getName() == "math")
          ++numChildren;
      }

      if (hasMath && numChildren == 0)
      {
        ADD_MESSAGE_WITH_SEVERITY(DEVISER_IGNORE,
              "Class: '" << item->getName()
              <<"' has hasMath=true, but no math child."
              );
      }

      if (!hasMath && numChildren > 0)
      {
        ADD_MESSAGE_WITH_SEVERITY(DEVISER_IGNORE,
              "Class: '" << item->getName()
              <<"' has a child 'math' but hasMath=false"
              );
      }
    }
  }
  return result;
}

bool
HasMathConstraint::fixIssue(DeviserPackage* package)
{
  int result = 0;

  foreach(DeviserVersion* version, package->getVersions())
  {
    foreach (DeviserClass* item, version->getElements())
    {
      bool hasMath = item->hasMath();
      int numChildren = 0;
      foreach (DeviserAttribute* attr, item->getAttributes())
      {
        if (attr->getName() == "math")
          ++numChildren;
      }

      foreach (DeviserListOfAttribute* attr, item->getListOfAttributes())
      {
        if (attr->getName() == "math")
          ++numChildren;
      }

      if (hasMath && numChildren == 0)
      {
        DeviserAttribute* mathAttr = new DeviserAttribute();
        mathAttr -> setName("math");
        mathAttr -> setType("element");
        mathAttr -> setElement("ASTNode*");
        mathAttr -> setParent(package);
        mathAttr -> setParentVersion(version);

        item ->getAttributes() << mathAttr;

        result = true;
      }

      if (!hasMath && numChildren > 0)
      {
        item->setHasMath(true);
        result = true;
      }
    }
  }
  return result;
}
