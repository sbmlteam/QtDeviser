#include "uniquenameconstraint.h"

#include <model/devisertypes.h>

UniqueNameConstraint::UniqueNameConstraint(DeviserValidator* validator)
  : DeviserConstraint(validator)
{

}

int
UniqueNameConstraint::analyzePackage(DeviserPackage *package)
{
  int count = 0;

  QStringList versions;

  foreach(DeviserVersion* version, package->getVersions())
  {
    if (versions.contains(version->toString()))
    {
      ADD_MESSAGE_WITH_SEVERITY(DEVISER_ERROR, "Version: '" << version->toString()
                  << "' exists multiple times.");
      ++count;
    }
    versions << version->toString();

    QStringList enums;
    QStringList classes;
    QStringList plugins;

    foreach (DeviserClass* current, version->getElements())
    {
      if (classes.contains(current->getName()))
      {
        ADD_MESSAGE_WITH_SEVERITY(DEVISER_ERROR, "Element: '" << current->getName()
                    << "' exists multiple times.");
        ++count;
      }
      classes << current->getName();
    }

    foreach (DeviserEnum* current, version->getEnums())
    {
      if (enums.contains(current->getName()))
      {
      ADD_MESSAGE_WITH_SEVERITY(DEVISER_ERROR, "Enum: '" << current->getName()
                  << "' exists multiple times.");
      ++count;
      }
      enums<< current->getName();
    }

    foreach (DeviserPlugin* current, version->getPlugins())
    {
      if (plugins.contains(current->getExtensionPoint()))
      {

      ADD_MESSAGE_WITH_SEVERITY(DEVISER_ERROR, "ExtensionPoint: '" << current->getExtensionPoint()
                  << "' exists multiple times.");
      ++count;
      }
      plugins << current->getExtensionPoint();
    }

  }

  return count;
}
