#include "deviservalidator.h"

#include <validation/deviserconstraint.h>

#include <validation/haschildrenconstraint.h>
#include <validation/haslistofconstraint.h>
#include <validation/hasmathconstraint.h>
#include <validation/isbaseclassconstraint.h>
#include <validation/packageconstraints.h>
#include <validation/attributeconstraints.h>
#include <validation/typecodeconstraint.h>
#include <validation/enumconstraint.h>
#include <validation/instantiationconstraint.h>

DeviserValidator::DeviserValidator(QObject *parent)
  : QObject(parent)
  , mConstraints()
  , mErrors()
{
  mConstraints << new HasChildrenConstraint(this)
               << new HasListOfConstraint(this)
               << new HasMathConstraint(this)
               << new IsBaseClassConstraint(this)
               << new PackageConstraints(this)
               << new AttributeConstraints(this)
               << new TypeCodeConstraint(this)
               << new EnumConstraint(this)
               << new InstantiationConstraint(this)
                  ;
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

int
DeviserValidator::getNumErrors() const
{
  return mErrors.count();
}

int
DeviserValidator::getNumErrors(DeviserSeverity severity) const
{
  int count = 0;
  foreach(DeviserMessage* message, mErrors)
  {
    if (message->severity() == severity)
      ++count;
  }

  return count;
}
