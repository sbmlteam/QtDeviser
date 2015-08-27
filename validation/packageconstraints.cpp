#include "packageconstraints.h"

#include <model/deviserpackage.h>

PackageConstraints::PackageConstraints(DeviserValidator* validator)
 : DeviserConstraint(validator)
{

}


int
PackageConstraints::analyzePackage(DeviserPackage *package)
{
  int count = 0;
  if (package->getName().isEmpty())
  {
    ADD_MESSAGE_WITH_SEVERITY(DEVISER_ERROR, "Package: missing name attribute.");
    ++count;
  }

  if (package->getFullName().isEmpty())
  {
    ADD_MESSAGE_WITH_SEVERITY(DEVISER_ERROR, "Package: missing full name attribute.");
    ++count;
  }

  if (!QString::number(package->getStartNumber()).endsWith("00"))
  {
    ADD_MESSAGE_WITH_SEVERITY(DEVISER_WARNING, "Package: Number should end with 00.");
    ++count;
  }

  if (!QString::number(package->getOffset()).endsWith("00000"))
  {
    ADD_MESSAGE_WITH_SEVERITY(DEVISER_WARNING, "Package: Offset should end with 00000.");
    ++count;
  }

  return count;
}


bool
PackageConstraints::fixIssue(DeviserPackage* package)
{
  if (package->getFullName().isEmpty())
  {
    package->setFullName(package->getName());
    return true;
  }

  return false;
}
