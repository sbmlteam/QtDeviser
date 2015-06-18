#include "formdeviserversion.h"
#include "ui_formdeviserversion.h"

FormDeviserVersion::FormDeviserVersion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDeviserVersion)
{
    ui->setupUi(this);
}

FormDeviserVersion::~FormDeviserVersion()
{
    delete ui;
}
