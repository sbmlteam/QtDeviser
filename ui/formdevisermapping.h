#ifndef FORMDEVISERMAPPING_H
#define FORMDEVISERMAPPING_H

#include <QWidget>

namespace Ui {
class FormDeviserMapping;
}

class FormDeviserMapping : public QWidget
{
    Q_OBJECT

public:
    explicit FormDeviserMapping(QWidget *parent = 0);
    ~FormDeviserMapping();

private:
    Ui::FormDeviserMapping *ui;
};

#endif // FORMDEVISERMAPPING_H
