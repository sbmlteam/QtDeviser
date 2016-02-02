#include "haslistofconstraint.h"

#include <model/devisertypes.h>

HasListOfConstraint::HasListOfConstraint(DeviserValidator* validator)
  : DeviserConstraint(validator)
{

}

int
HasListOfConstraint::analyzePackage(DeviserPackage *package)
{
  int result = 0;

  foreach(DeviserVersion* version, package->getVersions())
  {

    foreach (DeviserClass* current , version->getElements())
    {

      bool hasListOf = current->hasListOf();

      int countUses = 0;
      foreach (DeviserClass* item, version->getElements())
      {
        if (item == current) continue;

        foreach (DeviserAttribute* attr, item->getAttributes())
        {
          if (attr->getType() != "lo_element" &&
              attr->getType() != "inline_lo_element")
            continue;
          if (attr->getElement() != current->getName())
            continue;

          ++countUses;

          if (!hasListOf)
          {
            ++result;
            ADD_MESSAGE(
                  "Class: '" << item->getName() <<
                  "' uses a list of '"<< current->getName() <<
                  "', which is not marked having a list."
                  );
          }
        }
      }

      foreach (DeviserPlugin* item, version->getPlugins())
      {
        foreach (DeviserAttribute* attr, item->getAttributes())
        {
          if (attr->getType() != "lo_element" &&
              attr->getType() != "inline_lo_element")
            continue;
          if (attr->getElement() != current->getName())
            continue;

          ++countUses;

          if (!hasListOf)
          {
            ++result;
            ADD_MESSAGE(
                  "Plugin for '" << item->getExtensionPoint() <<
                  "' uses a list of '"<< current->getName() <<
                  "', which is not marked having a list."
                  );
          }
        }

        foreach(DeviserReferenceAttribute* reference, item->getReferences())
        {
          if (reference->getName() != current->getActualListOfName())
            continue;

          ++countUses;
          if (!hasListOf)
          {
            ++result;
            ADD_MESSAGE(
                  "Plugin for '" << item->getExtensionPoint() <<
                  "' uses a list of '"<< current->getName() <<
                  "', which is not marked having a list."
                  );

          }
        }
      }

      if (hasListOf && countUses == 0)
      {
        ++result;
        ADD_MESSAGE(
              "Class: '" << current->getName() <<
              "' is marked as having a list of, but no listOf of it is used."
              );
      }

    }
  }
  return result;
}

bool
HasListOfConstraint::fixIssue(DeviserPackage* package)
{
  bool result = false;

  foreach(DeviserVersion* version, package->getVersions())
  {

    foreach (DeviserClass* current , version->getElements())
    {
      bool hasListOf = current->hasListOf();

      int countUses = 0;
      foreach (DeviserClass* item, version->getElements())
      {
        if (item == current) continue;

        foreach (DeviserAttribute* attr, item->getAttributes())
        {
          if (attr->getType() != "lo_element" &&
              attr->getType() != "inline_lo_element")
            continue;
          if (attr->getElement() != current->getName())
            continue;

          ++countUses;

          if (!hasListOf)
          {
              current->setHasListOf(true);
              result = true;
          }
        }
      }

      foreach (DeviserPlugin* item, version->getPlugins())
      {
        foreach (DeviserAttribute* attr, item->getAttributes())
        {
          if (attr->getType() != "lo_element" &&
              attr->getType() != "inline_lo_element")
            continue;
          if (attr->getElement() != current->getName())
            continue;

          ++countUses;

          if (!hasListOf)
          {
            current->setHasListOf(true);
            result = true;
          }
        }

        foreach(DeviserReferenceAttribute* reference, item->getReferences())
        {
          if (reference->getName() != current->getActualListOfName())
            continue;

          ++countUses;
          if (!hasListOf)
          {
            current->setHasListOf(true);
            result = true;
          }
        }
      }

      if (hasListOf && countUses == 0)
      {
        current->setHasListOf(false);
        result = true;
      }

    }
  }
  return result;
}
