#ifndef DEVISERPACKAGE_H
#define DEVISERPACKAGE_H

#include <model/deviserbase.h>
#include <model/deviserversion.h>


class DeviserPackage : public DeviserBase
{
    Q_OBJECT

public:
    DeviserPackage();
    DeviserPackage(const DeviserPackage& other);
    DeviserPackage(const QString& fileName);
    DeviserPackage(QDomElement& element);

    virtual void initializeFrom(const QDomElement& element);

    virtual void setParent(DeviserPackage* doc);

    virtual QString toXmlString() const;
    virtual QString toYuml(bool usecolor = true) const;

    virtual void writeAttributesTo(QXmlStreamWriter& writer) const;
    virtual void writeElementsTo(QXmlStreamWriter& writer) const;
    virtual void writeTo(QXmlStreamWriter& writer) const;

    virtual void writeTo(const QString& fileName) const;

    QList<DeviserVersion*>& getVersions() { return mVersions; }
    const QList<DeviserVersion*>& getVersions() const { return mVersions; }

    DeviserVersion* getVersion(const QString& name);

    const QString& getName() const;
    void setName(const QString& name) { mName = name; emit nameChanged(); }
    const QString& getFullName() const;
    void setFullName(const QString& fullName) { mFullName = fullName; emit fullNameChanged(); }
    int getStartNumber() const;
    void setStartNumber(int startNumber) { mStartNumber = startNumber; emit startNumberChanged(); }
    int getOffset() const;
    void setOffset(int offset) { mOffset = offset; emit offsetChanged(); }
    int getVersion() const;
    void setVersion(int version) { mVersion = version; emit versionChanged(); }
    bool isRequired() const;
    void setRequired(bool isRequired) { mRequired = isRequired; emit requiredChanged(); }
    const QString& getAdditionalDeclarations() const;
    void setAdditionalDeclarations(const QString& additionalDeclarations) { mAdditionalDeclarations = additionalDeclarations; emit additionalDeclarationsChanged();}
    const QString& getAdditionalDefinitions() const;
    void setAdditionalDefinitions(const QString& additionalDefinitions) { mAdditionalDefinitions = additionalDefinitions; emit additionalDefinitionsChanged(); }

    DeviserVersion* createVersion(int level = 0, int version = 0, int pkgVersion = 1);


signals:
    void nameChanged();
    void fullNameChanged();
    void startNumberChanged();
    void offsetChanged();
    void versionChanged();
    void requiredChanged();
    void additionalDeclarationsChanged();
    void additionalDefinitionsChanged();

protected:
    QString mName;
    QString mFullName;
    int mStartNumber;
    int mOffset;
    int mVersion;
    bool mRequired;
    QString mAdditionalDeclarations;
    QString mAdditionalDefinitions;

    QList<DeviserVersion*> mVersions;

};

#endif // DEVISERPACKAGE_H
