#include "dialogdisplaynumbers.h"
#include "ui_dialogdisplaynumbers.h"

#include <QFile>
#include <QTextStream>

DialogDisplayNumbers::DialogDisplayNumbers(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogDisplayNumbers)
{
  ui->setupUi(this);

  QFile data(":/internal_numbering_within_packages.txt");
  data.open(QIODevice::ReadOnly);
  QTextStream in(&data);
  QString str = in.readAll();
  data.close();

  str = "<pre>" +  str + "</pre>";

  ui->textBrowser->setHtml(str);

}

DialogDisplayNumbers::~DialogDisplayNumbers()
{
  delete ui;
}
