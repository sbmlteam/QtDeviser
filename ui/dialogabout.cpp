#include "dialogabout.h"
#include "ui_dialogabout.h"
#include "deviser-version.h"

DialogAbout::DialogAbout(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogAbout)
{
  ui->setupUi(this);

  ui->label->setText(ui->label->text().replace("$$VERSION$$", DEVISER_DOTTED_VERSION));
}

DialogAbout::~DialogAbout()
{
  delete ui;
}
