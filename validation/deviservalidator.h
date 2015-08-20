#ifndef DEVISERVALIDATOR_H
#define DEVISERVALIDATOR_H

#include <QObject>
#include <QList>

#include <validation/devisermessage.h>


class DeviserPackage;
class DeviserConstraint;

class DeviserValidator : public QObject
{
  Q_OBJECT
public:
  explicit DeviserValidator(QObject *parent = 0);

  int validatePackage(DeviserPackage* package);
  void fixIssues(DeviserPackage* package);

  QList<DeviserMessage> errors() const;
  QList<DeviserMessage> errors();
  void setErrors(const QList<DeviserMessage> &errors);

  QList<DeviserConstraint *> constraints() const;
  void setConstraints(const QList<DeviserConstraint *> &constraints);

signals:

public slots:

protected:

protected:

  QList<DeviserConstraint*> mConstraints;
  QList<DeviserMessage> mErrors;

};

#endif // DEVISERVALIDATOR_H
