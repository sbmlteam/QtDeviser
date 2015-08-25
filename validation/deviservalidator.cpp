#include "deviservalidator.h"

#include <validation/deviserconstraint.h>

#include <validation/packageconstraints.h>
#include <validation/sidrefconstraint.h>

DeviserValidator::DeviserValidator(QObject *parent)
  : QObject(parent)
  , mConstraints()
  , mErrors()
{
  mConstraints << new PackageConstraints(this)
               << new SIdRefConstraint(this);
}

int DeviserValidator::validatePackage(DeviserPackage *package)
{
  int count = 0;
  mErrors.clear();

  foreach(DeviserConstraint* constraint, mConstraints)
  {
    count += constraint->analyzePackage(package);
  }

  return count;
}

void DeviserValidator::fixIssues(DeviserPackage* package)
{
  foreach(DeviserConstraint* constraint, mConstraints)
  {
    constraint->fixIssue(package);
  }
}

QList<DeviserMessage*> DeviserValidator::errors() const
{
  return mErrors;
}

QList<DeviserMessage*> DeviserValidator::errors()
{
  return mErrors;
}

void DeviserValidator::setErrors(const QList<DeviserMessage*> &errors)
{
  mErrors = errors;
}
QList<DeviserConstraint *> DeviserValidator::constraints() const
{
  return mConstraints;
}

void DeviserValidator::setConstraints(const QList<DeviserConstraint *> &constraints)
{
  mConstraints = constraints;
}


void 
DeviserValidator::addMessage(DeviserMessage* message)
{
  mErrors << message;
}
