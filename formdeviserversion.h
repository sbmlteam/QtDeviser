#ifndef FORMDEVISERVERSION_H
#define FORMDEVISERVERSION_H

#include <QWidget>

namespace Ui {
class FormDeviserVersion;
}

class FormDeviserVersion : public QWidget
{
    Q_OBJECT

public:
    explicit FormDeviserVersion(QWidget *parent = 0);
    ~FormDeviserVersion();

private:
    Ui::FormDeviserVersion *ui;
};

#endif // FORMDEVISERVERSION_H
