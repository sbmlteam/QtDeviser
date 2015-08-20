#ifndef DEVISERMESSAGE_H
#define DEVISERMESSAGE_H

#include <QObject>

class DeviserConstraint;

class DeviserMessage : public QObject
{
  Q_OBJECT
public:
  explicit DeviserMessage(QObject *parent = 0,
                          QString message = "",
                          DeviserConstraint* contraint = NULL);

  DeviserMessage(const DeviserMessage& other);
  DeviserMessage& operator=(const DeviserMessage& rhs);

  QString message() const;
  void setMessage(const QString &message);

  DeviserConstraint *constraint() const;
  void setConstraint(DeviserConstraint *constraint);

signals:

public slots:

protected:
  QString mMessage;
  DeviserConstraint* mConstraint;
};

#endif // DEVISERMESSAGE_H
