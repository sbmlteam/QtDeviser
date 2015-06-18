#ifndef FORMDEVISERPLUGIN_H
#define FORMDEVISERPLUGIN_H

#include <QWidget>

namespace Ui {
class FormDeviserPlugin;
}

class DeviserPlugin;

class FormDeviserPlugin : public QWidget
{
    Q_OBJECT

public:
    explicit FormDeviserPlugin(QWidget *parent = 0);
    ~FormDeviserPlugin();

    void initializeFrom(DeviserPlugin* plugin);

private:
    Ui::FormDeviserPlugin *ui;
    DeviserPlugin* mPlugin;
};

#endif // FORMDEVISERPLUGIN_H
