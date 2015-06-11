#include "formdevisermapping.h"
#include "ui_formdevisermapping.h"

FormDeviserMapping::FormDeviserMapping(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDeviserMapping)
{
    ui->setupUi(this);
}

FormDeviserMapping::~FormDeviserMapping()
{
    delete ui;
}
