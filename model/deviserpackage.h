#ifndef DEVISERPACKAGE_H
#define DEVISERPACKAGE_H

#include <model/deviserbase.h>
#include <model/deviserversion.h>


class DeviserPackage : public DeviserBase
{
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

protected:
    QString mName;
    QString mFullName;
    int mStartNumber;
    int mOffset;
    int mVersion;
    bool mRequired;
    QString mAdditionalDeclarations;
    QString mAdditionalDefinitions;

    QList<DeviserVersion> mVersions;

    DeviserVersion* mCurrentVersion;


};

#endif // DEVISERPACKAGE_H
