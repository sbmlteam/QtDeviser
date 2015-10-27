#include "dialogerrors.h"
#include "ui_dialogerrors.h"

#include <QTextStream>
#include <QByteArray>
#include <QClipboard>

#include <validation/devisermessage.h>

DialogErrors::DialogErrors(const QList<DeviserMessage*>& errors,
                           QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::DialogErrors)
  , mErrors(errors)
  , mMessages()
{
  ui->setupUi(this);

  QByteArray array;
  QTextStream stream(&array, QIODevice::WriteOnly);
  stream.setCodec("UTF-8");

  setWindowTitle(
        QString("Package Validation: %1 issues found.")
        .arg(errors.count()));

  stream << QString("Package Validation: %1 issues found.")
            .arg(errors.count()) << endl << endl;

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
      stream << "Error: ";
      break;

    case DEVISER_NOTICE:
      pixmap ->setPixmap(QPixmap(":images/dialog-information.png"));
      stream << "Notice: ";
      break;

    default:
      pixmap ->setPixmap(QPixmap(":images/dialog-warning.png"));
      stream << "Warning: ";
      break;
    }
    hlayout->addWidget(pixmap);

    QLabel *label = new QLabel(message->message(), ui->scrollAreaWidgetContents);

    stream << message->message() << endl << endl;

    label->setWordWrap(true);
    hlayout->addWidget(label);

    layout->addItem(hlayout);
  }

  layout->addItem(
        new QSpacerItem(10,10, QSizePolicy::Minimum, QSizePolicy::Expanding));

  stream.flush();

  mMessages = QString::fromUtf8(array);

}

DialogErrors::~DialogErrors()
{
  delete ui;
}

void DialogErrors::copyErrors()
{
  QClipboard *clipboard = QApplication::clipboard();
  clipboard->setText(mMessages);
}
