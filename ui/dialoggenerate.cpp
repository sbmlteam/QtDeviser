#include "dialoggenerate.h"
#include "ui_dialoggenerate.h"

DialogGenerate::DialogGenerate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGenerate)
{
    ui->setupUi(this);
}

DialogGenerate::~DialogGenerate()
{
    delete ui;
}
