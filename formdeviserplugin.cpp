#include "formdeviserplugin.h"
#include "ui_formdeviserplugin.h"

FormDeviserPlugin::FormDeviserPlugin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDeviserPlugin)
{
    ui->setupUi(this);
}

FormDeviserPlugin::~FormDeviserPlugin()
{
    delete ui;
}
