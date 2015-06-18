#ifndef FORMDEVISERENUM_H
#define FORMDEVISERENUM_H

#include <QWidget>

namespace Ui {
class FormDeviserEnum;
}

class DeviserEnum;
class FormDeviserEnum : public QWidget
{
    Q_OBJECT

public:
    explicit FormDeviserEnum(QWidget *parent = 0);
    ~FormDeviserEnum();
    void initializeFrom(DeviserEnum* devEnum);

public slots:
    void addRow();
    void deleteRow();


private:
    Ui::FormDeviserEnum *ui;
    DeviserEnum* mEnum;
};

#endif // FORMDEVISERENUM_H
