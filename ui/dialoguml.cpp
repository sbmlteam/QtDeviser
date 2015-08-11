#include "dialoguml.h"
#include "ui_dialoguml.h"

#include "mainwindow.h"

#include "model/deviserversion.h"

#include <QScrollBar>
#include <QGraphicsPixmapItem>

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include <QHttpPart>

DialogUML::DialogUML(QWidget *parent)
  :  QDialog(parent)
  ,  ui(new Ui::DialogUML)
  ,  mpScene(new QGraphicsScene(this))
  ,  mpManager(new QNetworkAccessManager(this))
{  


  ui->setupUi(this);

  connect(mpManager, SIGNAL(finished(QNetworkReply*)),
              this, SLOT(downloadFinished(QNetworkReply*)));

  ui->graphicsView->setScene(mpScene);

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

  QByteArray yuml; yuml.append(ui->txtEdit->document()->toPlainText());// .toUtf8());
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

}


void
DialogUML::downloadFinished(QNetworkReply *reply)
{
  QByteArray data  = reply->readAll();

  if (data.isEmpty()) return;

  if (data.endsWith(".png"))
  {
    QUrl imageUrl ("http://yuml.me/"
                  + data);
    QNetworkRequest request(imageUrl);
    mpManager->get(request);
    reply->deleteLater();
    return;
  }

  mpScene->clear();
  QImage image; image.loadFromData(data);
  QGraphicsPixmapItem* item =
      new QGraphicsPixmapItem(QPixmap::fromImage(image));


  mpScene ->addItem(item);
  ui->graphicsView->update();
  if (ui->chkFitUML->isChecked())
    ui->graphicsView->fitInView(item, Qt::KeepAspectRatio);
  else
    ui->graphicsView->scale(1.0f, 1.0f);

  reply->deleteLater();
}

void
DialogUML::saveAs()
{

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

