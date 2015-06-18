#ifndef FORMDEVISERCLASS_H
#define FORMDEVISERCLASS_H

#include <QWidget>

namespace Ui {
class FormDeviserClass;
}

class FormDeviserClass : public QWidget
{
    Q_OBJECT

public:
    explicit FormDeviserClass(QWidget *parent = 0);
    ~FormDeviserClass();

private:
    Ui::FormDeviserClass *ui;
};

#endif // FORMDEVISERCLASS_H
