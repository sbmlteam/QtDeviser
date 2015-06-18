#ifndef FORMDEVISERVERSION_H
#define FORMDEVISERVERSION_H

#include <QWidget>

namespace Ui {
class FormDeviserVersion;
}

class DeviserVersion;

class FormDeviserVersion : public QWidget
{
    Q_OBJECT

public:
    explicit FormDeviserVersion(QWidget *parent = 0);
    ~FormDeviserVersion();

    void initializeFrom(DeviserVersion* version);

private:
    Ui::FormDeviserVersion *ui;
    DeviserVersion* mVersion;
};


#endif // FORMDEVISERVERSION_H
