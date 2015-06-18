#ifndef FORMDEVISERENUM_H
#define FORMDEVISERENUM_H

#include <QWidget>

namespace Ui {
class FormDeviserEnum;
}

class FormDeviserEnum : public QWidget
{
    Q_OBJECT

public:
    explicit FormDeviserEnum(QWidget *parent = 0);
    ~FormDeviserEnum();

public slots:
    void addRow();
    void deleteRow();


private:
    Ui::FormDeviserEnum *ui;
};

#endif // FORMDEVISERENUM_H
