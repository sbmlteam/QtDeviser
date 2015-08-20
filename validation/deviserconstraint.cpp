#include "deviserconstraint.h"

#include "deviservalidator.h"

DeviserConstraint::DeviserConstraint(DeviserValidator *validator)
  : QObject(validator)
  , mpValidator(validator)
  , mCanFix(false)
{

}

bool DeviserConstraint::fixIssue(DeviserPackage * /*package*/)
{
  return false;
}

bool DeviserConstraint::canFix() const
{
  return mCanFix;
}

void DeviserConstraint::addMessage(const DeviserMessage &message)
{
  if (mpValidator == NULL) return;
  mpValidator->errors().append(message);
}

