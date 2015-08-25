#ifndef DEVISERMESSAGE_H
#define DEVISERMESSAGE_H

#include <QObject>

class DeviserConstraint;

enum DeviserSeverity
{
  DEVISER_NOTICE,
  DEVISER_WARNING,
  DEVISER_ERROR,
  DEVISER_FATAL_ERROR
};


class DeviserMessage : public QObject
{
  Q_OBJECT
public:
  explicit DeviserMessage(QObject *parent = 0,
                          const QString& message = "",
                          DeviserSeverity severity = DEVISER_WARNING,
                          DeviserConstraint* constraint = NULL);

  DeviserMessage(const DeviserMessage& other);
  DeviserMessage& operator=(const DeviserMessage& rhs);

  QString message() const;
  void setMessage(const QString &message);

  DeviserConstraint *constraint() const;
  void setConstraint(DeviserConstraint *constraint);

  DeviserSeverity severity() const;
  void setSeverity(const DeviserSeverity &severity);

signals:

public slots:

protected:
  QString mMessage;
  DeviserConstraint* mConstraint;
  DeviserSeverity mSeverity;
};

#endif // DEVISERMESSAGE_H
