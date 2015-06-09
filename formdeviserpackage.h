#ifndef FORMDEVISERPACKAGE_H
#define FORMDEVISERPACKAGE_H

#include <QWidget>

namespace Ui {
class FormDeviserPackage;
}

class FormDeviserPackage : public QWidget
{
    Q_OBJECT

public:
    explicit FormDeviserPackage(QWidget *parent = 0);
    ~FormDeviserPackage();

private:
    Ui::FormDeviserPackage *ui;
};

#endif // FORMDEVISERPACKAGE_H
