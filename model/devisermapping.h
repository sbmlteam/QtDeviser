#ifndef DEVISERMAPPING_H
#define DEVISERMAPPING_H

#include <model/deviserbase.h>

class DeviserMapping : public DeviserBase
{
    Q_OBJECT

public:
    DeviserMapping();
    DeviserMapping(const DeviserMapping& other);
    virtual void initializeFrom(const QDomElement& element);

    const QString& getName() const { return mName; }
    void setName(const QString& name) { mName = name; emit nameChanged(); }

    const QString& getPackage() const { return mPackage; }
    void setPackage(const QString& package) { mPackage = package; emit packageChanged(); }

signals:
    void nameChanged();
    void packageChanged();

protected:
    QString mName;
    QString mPackage;
};

#endif // DEVISERMAPPING_H
