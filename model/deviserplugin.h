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
    DeviserPlugin(const DeviserPlugin& other) {}
    virtual void initializeFrom(const QDomElement& element);

    const QString& getExtensionPoint() const { return mExtensionPoint;}
    const QString& getAdditionalDeclarations() const { return mAdditionalDeclarations;}
    const QString& getAdditionalDefinitions() const { return mAdditionalDefinitions;}
    const QString& getTypeCode() const { return mTypeCode;}
    const QString& getPackage() const { return mPackage;}

    const QList<DeviserReferenceAttribute*>& getReferences () const { return mReferences;}
    const QList<DeviserAttribute*>& getAttributes() const { return mAttributes;}

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
