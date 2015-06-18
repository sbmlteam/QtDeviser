#ifndef FORMDEVISERPLUGIN_H
#define FORMDEVISERPLUGIN_H

#include <QWidget>

namespace Ui {
class FormDeviserPlugin;
}

class FormDeviserPlugin : public QWidget
{
    Q_OBJECT

public:
    explicit FormDeviserPlugin(QWidget *parent = 0);
    ~FormDeviserPlugin();

private:
    Ui::FormDeviserPlugin *ui;
};

#endif // FORMDEVISERPLUGIN_H
