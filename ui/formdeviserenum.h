#ifndef FORMDEVISERENUM_H
#define FORMDEVISERENUM_H

#include <QWidget>

namespace Ui {
class FormDeviserEnum;
}

class DeviserEnum;
class EnumModel;
class QSortFilterProxyModel;

class FormDeviserEnum : public QWidget
{
  Q_OBJECT

public:
  explicit FormDeviserEnum(QWidget *parent = 0);
  ~FormDeviserEnum();
  void initializeFrom(DeviserEnum* devEnum);

public slots:
  void addRow();
  void quickAdd();
  void deleteRow();
  void nameChanged(const QString&);


private:
  Ui::FormDeviserEnum *ui;
  DeviserEnum* mEnum;

  EnumModel* mpValues;
  QSortFilterProxyModel* mpValuesFilter;

  bool mbInitializing;
};

#endif // FORMDEVISERENUM_H
