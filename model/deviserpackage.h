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

    DeviserVersion* getVersion(const QString& name);

    const QString& getName() const;
    const QString& getFullName() const;
    int getStartNumber() const;
    int getOffset() const;
    int getVersion() const;
    bool getRequired() const;
    const QString& getAdditionalDeclarations() const;
    const QString& getAdditionalDefinitions() const;

    DeviserVersion* createVersion(int level = 0, int version = 0, int pkgVersion = 1);

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
