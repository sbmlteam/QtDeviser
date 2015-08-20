#ifndef DEVISERCONSTRAINT_H
#define DEVISERCONSTRAINT_H

#include <QObject>
#include <QTextStream>
#include <QString>

#include <validation/deviservalidator.h>
#include <validation/devisermessage.h>

#include <sstream>

#define ADD_MESSAGE(args)\
{\
  QString message;\
  QTextStream str(&message); str << args;\
  addMessage(new DeviserMessage(NULL, message, this));\
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

  void addMessage(DeviserMessage *message);

  DeviserValidator *mpValidator;
  bool mCanFix;

};

#endif // DEVISERCONSTRAINT_H
