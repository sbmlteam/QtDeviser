#ifndef FORMDEVISERMAPPING_H
#define FORMDEVISERMAPPING_H

#include <QWidget>

namespace Ui {
class FormDeviserMapping;
}

class DeviserVersion;
class MappingModel;
class QSortFilterProxyModel;

class FormDeviserMapping : public QWidget
{
  Q_OBJECT

public:
  explicit FormDeviserMapping(QWidget *parent = 0);
  ~FormDeviserMapping();

  void initializeFrom(DeviserVersion* version);

private:
  Ui::FormDeviserMapping *ui;
  DeviserVersion* mVersion;

  MappingModel* mpMappings;
  QSortFilterProxyModel* mpMappingFilter;
};

#endif // FORMDEVISERMAPPING_H
