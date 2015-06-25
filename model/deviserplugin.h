#ifndef DEVISERPLUGIN_H
#define DEVISERPLUGIN_H

#include <model/deviserbase.h>

class DeviserReferenceAttribute;
class DeviserAttribute;

class DeviserPlugin : public DeviserBase
{
    Q_OBJECT

public:
    DeviserPlugin();
    DeviserPlugin(const DeviserPlugin& other);
    virtual void initializeFrom(const QDomElement& element);

    const QString& getExtensionPoint() const { return mExtensionPoint;}
    void setExtensionPoint(const QString& extPoint) { QString oldExtPoint(mExtensionPoint); mExtensionPoint = extPoint; emit extensionPointChanged(oldExtPoint, extPoint); }

    const QString& getAdditionalDeclarations() const { return mAdditionalDeclarations;}
    void setAdditionalDeclarations(const QString& additionalDeclarations) { mAdditionalDeclarations = additionalDeclarations; emit additionalDeclarationsChanged();}

    const QString& getAdditionalDefinitions() const { return mAdditionalDefinitions;}
    void setAdditionalDefinitions(const QString& additionalDefinitions) { mAdditionalDefinitions = additionalDefinitions; emit additionalDefinitionsChanged(); }
    const QString& getTypeCode() const { return mTypeCode;}
    void setTypeCode(const QString& typeCode) { mTypeCode = typeCode; emit typeCodeChanged(); }

    const QString& getPackage() const { return mPackage;}
    void setPackage(const QString& package) { mPackage = package; emit packageChanged(); }

    const QList<DeviserReferenceAttribute*>& getReferences () const { return mReferences;}
    const QList<DeviserAttribute*>& getAttributes() const { return mAttributes;}
    QList<DeviserReferenceAttribute*>& getReferences ()  { return mReferences;}
    QList<DeviserAttribute*>& getAttributes() { return mAttributes;}

signals:
    void extensionPointChanged(const QString& oldName, const QString& newName);
    void typeCodeChanged();
    void packageChanged();
    void additionalDeclarationsChanged();
    void additionalDefinitionsChanged();


protected:
    QString mExtensionPoint;
    QString mAdditionalDeclarations;
    QString mAdditionalDefinitions;
    QString mTypeCode;
    QString mPackage;

    QList<DeviserReferenceAttribute*> mReferences ;
    QList<DeviserAttribute*> mAttributes;

};

#endif // DEVISERPLUGIN_H
