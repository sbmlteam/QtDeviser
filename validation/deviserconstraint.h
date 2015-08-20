#ifndef DEVISERCONSTRAINT_H
#define DEVISERCONSTRAINT_H

#include <QObject>

#include <validation/deviservalidator.h>
#include <validation/devisermessage.h>

#include <sstream>

#define ADD_MESSAGE(args)\
{\
  std::stringstream str; str << args;\
  addMessage(DeviserMessage(NULL, str.str().c_str(), this));\
}\

class DeviserPackage;

class DeviserConstraint : public QObject
{
  Q_OBJECT
public:
  explicit DeviserConstraint(DeviserValidator *validator);

  virtual int analyzePackage(DeviserPackage* package) = 0;
  virtual bool fixIssue(DeviserPackage* package);
  virtual bool canFix() const;

signals:

public slots:

protected:

  void addMessage(const DeviserMessage &message);

  DeviserValidator *mpValidator;
  bool mCanFix;

};

#endif // DEVISERCONSTRAINT_H
