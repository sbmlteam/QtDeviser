#include "dialoguml.h"
#include "ui_dialoguml.h"

#include "mainwindow.h"

#include "model/deviserversion.h"

#include <QFileDialog>
#include <QScrollBar>
#include <QGraphicsPixmapItem>
#include <QGraphicsSvgItem>

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include <QHttpPart>
#include <QFileInfo>

#include <QTemporaryFile>

#include <cstdlib>

bool DialogUML::mRegistered = false;
QStringList DialogUML::mFileList = QStringList();

void
DialogUML::removeTemporaryFiles()
{
  foreach(QString file, mFileList)
  {
    QFile(file).remove();
  }
}

DialogUML::DialogUML(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::DialogUML)
  , mpScene(new QGraphicsScene(this))
  , mpManager(new QNetworkAccessManager(this))
  , mpDownloadManager(new QNetworkAccessManager(this))
  , mCurrent("")
{  


  if (!mRegistered)
  {
    mRegistered = true;
    std::atexit(&removeTemporaryFiles);
  }

  ui->setupUi(this);

  connect(mpManager, SIGNAL(finished(QNetworkReply*)),
              this, SLOT(downloadFinished(QNetworkReply*)));

  connect(mpDownloadManager, SIGNAL(finished(QNetworkReply*)),
              this, SLOT(downloadImageFinished(QNetworkReply*)));

  ui->graphicsView->setScene(mpScene);

  ui->progressBar->setVisible(false);

}

void
DialogUML::loadYuml(const QString& yuml)
{
  ui->txtEdit->setPlainText(yuml);

  updateGraph();

}

DialogUML::~DialogUML()
{
  delete ui;
}


void
DialogUML::updateGraph()
{
  QUrl baseUri ("http://yuml.me/diagram/"
                + ui->cmdStyle->currentText()
                + "/class/");

  QNetworkRequest request(baseUri);

  QByteArray yuml; yuml.append(ui->txtEdit->document()->toPlainText());
  yuml = yuml.replace("\r\n", ",");
  yuml = yuml.replace("\n", ",");
  yuml = yuml.replace(",,", ",");

  QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
  QHttpPart textPart;
  textPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                     QVariant("form-data; name=\"dsl_text\""));
  textPart.setBody(yuml);
  multiPart->append(textPart);
  QNetworkReply *reply = mpManager->post(request, multiPart);
  multiPart->setParent(reply);

  ui->progressBar->setVisible(true);


}


void
DialogUML::downloadFinished(QNetworkReply *reply)
{
  QByteArray data  = reply->readAll();

  if (data.isEmpty()) return;

  if (data.endsWith(".png"))
  {
    QUrl imageUrl ("http://yuml.me/"
                  + (ui->chkUseSVG->isChecked() ?  data.replace("png", "svg") : data));
    QNetworkRequest request(imageUrl);
    mpManager->get(request);
    reply->deleteLater();
    mCurrent = data;
    return;
  }

  mpScene->clear();

  QGraphicsItem* item = NULL;

  if (ui->chkUseSVG->isChecked())
  {

  QTemporaryFile file("svg");
  file.setAutoRemove(false);
  file.open();
  file.write(data);
  file.close();

  mFileList.append(file.fileName());


  item = new QGraphicsSvgItem(file.fileName());

  }
  else
  {
    QImage image;
    image.loadFromData(data);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
  }

  mpScene ->addItem(item);

  ui->graphicsView->update();

  if (ui->chkFitUML->isChecked())
    ui->graphicsView->fitInView(item, Qt::KeepAspectRatio);
  else
    ui->graphicsView->scale(1.0f, 1.0f);

  ui->tabWidget->setCurrentWidget(ui->tabYUML);

  ui->progressBar->setVisible(false);

  reply->deleteLater();
}

void
DialogUML::saveAs()
{
  if (mCurrent.isEmpty())
    return;

  QString fileName = QFileDialog::getSaveFileName(this, "Save yUML", "", "PNG files (*.png);;JPG files (*.jpg);;PDF files (*.pdf);;SVG files (*.svg);;yUML files (*.txt);;All files (*.*)");

  if (fileName.isEmpty())
    return;


  QFileInfo info(fileName);
  QString ext = info.completeSuffix().toLower();
  if (ext == "txt")
  {
     QFile file(fileName);
     if (file.open(QIODevice::WriteOnly))
     {
       file.write(ui->txtEdit->document()->toPlainText().toStdString().c_str());
       file.close();
     }
  }
  else
    exportImage(fileName,ext);

}

void
DialogUML::exportImage(const QString& filename, const QString& ext)
{
  mFileName = filename;
  QString type = mCurrent;
  type = type.replace("svg", ext);

  mpDownloadManager->get(QNetworkRequest(QUrl("http://yuml.me/" + type)));

}


void
DialogUML::downloadImageFinished(QNetworkReply *reply)
{
  QByteArray data = reply->readAll();
  QFile file(mFileName);
  file.open(QIODevice::WriteOnly);
  file.write(data);
  file.close();

  reply->deleteLater();
}


void
DialogUML::styleChanged()
{
  updateGraph();
}

void
DialogUML::fitChanged()
{
  updateGraph();
}


void
DialogUML::resizeEvent(QResizeEvent * /*event*/)
{
  if (ui->chkFitUML->isChecked())
    ui->graphicsView->fitInView(mpScene->sceneRect(), Qt::KeepAspectRatio);
}

