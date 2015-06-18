#ifndef FORMDEVISERPACKAGE_H
#define FORMDEVISERPACKAGE_H

#include <QWidget>

namespace Ui {
class FormDeviserPackage;
}

class DeviserPackage;

class FormDeviserPackage : public QWidget
{
    Q_OBJECT

public:
    explicit FormDeviserPackage(QWidget *parent = 0);
    ~FormDeviserPackage();

    void initializeFrom(DeviserPackage* package);

private:
    Ui::FormDeviserPackage *ui;
    DeviserPackage* mPackage;
};

#endif // FORMDEVISERPACKAGE_H
