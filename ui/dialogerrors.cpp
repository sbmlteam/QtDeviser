#include "dialogerrors.h"
#include "ui_dialogerrors.h"

#include <validation/devisermessage.h>

DialogErrors::DialogErrors(const QList<DeviserMessage*>& errors,
                           QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::DialogErrors)
  , mErrors(errors)
{
  ui->setupUi(this);

  setWindowTitle(
        QString("Package Validation: %1 issues found.")
        .arg(errors.count()));

  ui->lblCount->setText(QString("Package Validation: %1 issues found.")
                        .arg(errors.count()));

  QLayout* layout = ui->scrollAreaWidgetContents->layout();
  if (layout == NULL)
  {
    layout = new QVBoxLayout(ui->scrollAreaWidgetContents);
  }

  foreach(DeviserMessage* message, errors)
  {
    QHBoxLayout *hlayout = new QHBoxLayout();
    QLabel *pixmap = new QLabel(ui->scrollAreaWidgetContents);
    pixmap->setMaximumWidth(50);
    pixmap->setMaximumHeight(50);
    pixmap->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    switch (message->severity()) {
    case DEVISER_ERROR:
    case DEVISER_FATAL_ERROR:
      pixmap ->setPixmap(QPixmap(":images/dialog-error.png"));
      break;

    case DEVISER_NOTICE:
      pixmap ->setPixmap(QPixmap(":images/dialog-information.png"));
      break;

    default:
      pixmap ->setPixmap(QPixmap(":images/dialog-warning.png"));
      break;
    }
    hlayout->addWidget(pixmap);

    QLabel *label = new QLabel(message->message(), ui->scrollAreaWidgetContents);
    label->setWordWrap(true);
    hlayout->addWidget(label);

    layout->addItem(hlayout);
  }

  layout->addItem(
        new QSpacerItem(10,10, QSizePolicy::Minimum, QSizePolicy::Expanding));

}

DialogErrors::~DialogErrors()
{
  delete ui;
}
