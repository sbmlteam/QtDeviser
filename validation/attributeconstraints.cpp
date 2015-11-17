#include "attributeconstraints.h"

#include <model/devisertypes.h>

AttributeConstraints::AttributeConstraints(DeviserValidator* validator)
  : DeviserConstraint(validator)
  , mKnownElementTypes()
  , mKnownTypes()
{

  mKnownElementTypes << "enum"
              << "array"
              << "element"
              << "lo_element"
              << "inline_lo_element"
                 ;

  mKnownTypes << mKnownElementTypes
              << "string"
              << "double"
              << "bool"
              << "boolean"
              << "int"
              << "uint"
              << "unsigned int"
              << "positive int"
              << "non-negative int"
              << "integer"
              << "unsigned integer"
              << "positive integer"
              << "non-negative integer"
              << "id"
              << "idref"
              << "sid"
              << "sidref"
              << "unitsid"
              << "unitsidref"
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
  if (attribute->getType() == "SIdRef" && attribute->getElement().isEmpty())
  {

    ADD_MESSAGE("The attribute '"
                << attribute->getName()
                << "' of plugin '"
                << name
                << "' is of type SIdRef, but has no element set. This is needed for validation purposes.");

    return true;
  }

  if (attribute->getType().isEmpty())
  {
    ADD_MESSAGE_WITH_SEVERITY(DEVISER_ERROR,
                              "The attribute '"
                              << attribute->getName()
                              << "' has no type defined, this is a required attribute for that type.");
    return true;
  }

  if (mKnownElementTypes.contains(attribute->getType().toLower()))
  {
    if (attribute->getElement().isEmpty())
    {

      ADD_MESSAGE_WITH_SEVERITY(DEVISER_ERROR,
                                "The attribute '"
                                << attribute->getName()
                                << "' is of type '"
                                << attribute->getType()
                                << "' but has no element defined, this is a required attribute for that type.");
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

  if (!mKnownTypes.contains(attribute->getType().toLower()))
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

