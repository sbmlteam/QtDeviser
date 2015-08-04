#include "dialoguml.h"
#include "ui_dialoguml.h"

DialogUML::DialogUML(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogUML)
{
  ui->setupUi(this);
}

DialogUML::~DialogUML()
{
  delete ui;
}
