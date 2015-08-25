#include "devisermessage.h"

DeviserMessage::DeviserMessage(QObject *parent,
                               const QString& message /*= ""*/,
                               DeviserSeverity severity /*= DEVISER_WARNING*/,
                               DeviserConstraint* constraint /*= NULL*/)
  : QObject(parent)
  , mMessage(message)
  , mConstraint(constraint)
  , mSeverity(severity)
{

}

DeviserMessage::DeviserMessage(const DeviserMessage &other)
  : QObject()
  , mMessage(other.mMessage)
  , mConstraint(other.mConstraint)
{

}

DeviserMessage&
DeviserMessage::operator=(const DeviserMessage& rhs)
{
  if (&rhs != this)
  {
    mMessage = rhs.mMessage;
    mConstraint = rhs.mConstraint;
  }

  return *this;
}

QString DeviserMessage::message() const
{
  return mMessage;
}

void DeviserMessage::setMessage(const QString &message)
{
  mMessage = message;
}

DeviserConstraint *DeviserMessage::constraint() const
{
  return mConstraint;
}

void DeviserMessage::setConstraint(DeviserConstraint *constraint)
{
  mConstraint = constraint;
}
DeviserSeverity DeviserMessage::severity() const
{
  return mSeverity;
}

void DeviserMessage::setSeverity(const DeviserSeverity &severity)
{
  mSeverity = severity;
}

