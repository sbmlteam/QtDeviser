#include "dialoggenerate.h"
#include "ui_dialoggenerate.h"

DialogGenerate::DialogGenerate(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::DialogGenerate)
  , mPackage(NULL)
{
  ui->setupUi(this);
}

DialogGenerate::~DialogGenerate()
{
  delete ui;
}

void
DialogGenerate::loadModel(DeviserPackage* package)
{
  mPackage = package;

}
