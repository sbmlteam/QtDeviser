#include "attributeconstraints.h"

#include <model/devisertypes.h>

#include <util.h>

AttributeConstraints::AttributeConstraints(DeviserValidator* validator)
  : DeviserConstraint(validator)
  , mKnownElementTypes()
  , mKnownTypes(Util::getKnownTypes())
{

  mKnownElementTypes << "enum"
              << "array"
              << "element"
              << "lo_element"
              << "inline_lo_element"
              << "vector"
                 ;

}

int AttributeConstraints::analyzePackage(DeviserPackage *package)
{
  if (package == NULL) return 0;

  int count = 0;

  foreach (DeviserVersion* version, package->getVersions())
  {
    foreach (DeviserClass* element, version->getElements())
    {
      if (element->getName().isEmpty())
      {
        ADD_MESSAGE_WITH_SEVERITY(DEVISER_ERROR,
                                  "There is an unnamed class in version '"
                                  << version->toString()
                                  << "', this is a required attribute");
        ++count;
      }

      foreach(DeviserAttribute* attribute, element->getAttributes())
      {
        if (checkAttribute(attribute, element->getName()))
          ++count;
      }

      foreach (DeviserListOfAttribute* attribute, element->getListOfAttributes()) {
        if (checkAttribute(attribute, element->getName()))
          ++count;
      }

    }

    foreach (DeviserPlugin* element, version->getPlugins())
    {
      if (element->getExtensionPoint().isEmpty())
      {
        ADD_MESSAGE_WITH_SEVERITY(DEVISER_ERROR,
                                  "There is a plugin without extensionpoint in version '"
                                  << version->toString()
                                  << "', this is a required attribute");
        ++count;
      }

      foreach(DeviserAttribute* attribute, element->getAttributes())
      {
        if (checkAttribute(attribute, element->getExtensionPoint()))
          ++count;
      }
    }
  }

  return count;

}

bool AttributeConstraints::checkAttribute(DeviserAttribute *attribute,
                                      const QString& name)
{
  bool result = false;

  if (attribute->getName().isEmpty())
  {
    ADD_MESSAGE_WITH_SEVERITY(DEVISER_ERROR, "The element '"
                << name
                << "' has an unnamed attribute. This is a required attribute.");

    result = true;
  }

  if (attribute->getType() == "SIdRef" && attribute->getElement().isEmpty())
  {

    ADD_MESSAGE("The attribute '"
                << attribute->getName()
                << "' of element '"
                << name
                << "' is of type SIdRef, but has no element set. This is needed for validation purposes.");

    return true;
  }
  else if (attribute->getType() == "SIdRef")
    return false;

  if (attribute->getType().isEmpty())
  {
    ADD_MESSAGE_WITH_SEVERITY(DEVISER_ERROR,
                              "The attribute '"
                              << attribute->getName()
                              << "' has no type defined, this is a required attribute.");
    return true;
  }

  if (mKnownElementTypes.contains(attribute->getType().toLower(), Qt::CaseInsensitive))
  {
    if (attribute->getElement().isEmpty())
    {

      ADD_MESSAGE_WITH_SEVERITY(DEVISER_ERROR,
                                "The attribute '"
                                << attribute->getName()
                                << "' is of type '"
                                << attribute->getType()
                                << "' but has no element defined, this is a required attribute.");
      result = true;

    }
  }
  else if (!attribute->getElement().isEmpty())
  {
    ADD_MESSAGE_WITH_SEVERITY(DEVISER_WARNING,
                              "The attribute '"
                              << attribute->getName()
                              << "' is of type '"
                              << attribute->getType()
                              << "' but has an element '"
                              << attribute->getElement()
                              << "' defined, this attribute will not be used.");
    result = true;
  }

  if (!mKnownTypes.contains(attribute->getType().toLower(), Qt::CaseInsensitive))
  {
    ADD_MESSAGE_WITH_SEVERITY(DEVISER_WARNING,
                              "The attribute '"
                              << attribute->getName()
                              << "' is of type '"
                              << attribute->getType()
                              << "', this type is not known by DEVISER and will have to be changed manually in the generated code.");
    result = true;
  }

  return result;
}

