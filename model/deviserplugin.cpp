#include "deviserplugin.h"

#include "deviserreferenceattribute.h"
#include "deviserattribute.h"

DeviserPlugin::DeviserPlugin()
{

}

void
DeviserPlugin::initializeFrom(const QDomElement& element)
{
    DeviserBase::initializeFrom(element);

    mExtensionPoint = element.attribute("extensionPoint");
    mAdditionalDeclarations = element.attribute("additionalDecls");
    mAdditionalDefinitions = element.attribute("additionalDefs");
    mTypeCode = element.attribute("typecode");
    mPackage = element.attribute("package");

    initializeListFrom(mReferences, element, "reference");
    initializeListFrom(mAttributes, element, "attribute");
}
