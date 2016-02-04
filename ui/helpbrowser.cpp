#include "helpbrowser.h"

#include <QNetworkReply>
#include <QByteArray>
#include <QNetworkRequest>
#include <QNetworkAccessManager>


#include <QDir>
#include <QAction>
#include <QDesktopServices>

#define  USE_WEBVIEW 0

#if USE_WEBVIEW

#include <QWebPage>
#include <QWebFrame>
#include <QTimer>

class HelpNetworkReply : public QNetworkReply
{
public:
  HelpNetworkReply(const QNetworkRequest &request, const QByteArray &fileData,
                   const QString &mimeType);

  virtual void abort();

  virtual qint64 bytesAvailable() const
  { return data.length() + QNetworkReply::bytesAvailable(); }

protected:
  virtual qint64 readData(char *data, qint64 maxlen);

private:
  QByteArray data;
  qint64 origLen;
};

HelpNetworkReply::HelpNetworkReply(const QNetworkRequest &request,
                                   const QByteArray &fileData, const QString &mimeType)
  : data(fileData), origLen(fileData.length())
{
  setRequest(request);
  setOpenMode(QIODevice::ReadOnly);

  setHeader(QNetworkRequest::ContentTypeHeader, mimeType);
  setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(origLen));
  QTimer::singleShot(0, this, SIGNAL(metaDataChanged()));
  QTimer::singleShot(0, this, SIGNAL(readyRead()));
}

void HelpNetworkReply::abort()
{
  // nothing to do
}

#include <qglobal.h>

#include <iostream>

qint64 HelpNetworkReply::readData(char *buffer, qint64 maxlen)
{
  

  qint64 len = qMin(qint64(data.length()), maxlen);
  if (len) {
    memcpy(buffer, data.constData(), len);
    data.remove(0, len);
    std::cout << buffer;
  }
  if (!data.length())
    QTimer::singleShot(0, this, SIGNAL(finished()));
  return len;
}

class HelpNetworkAccessManager : public QNetworkAccessManager
{
public:
  HelpNetworkAccessManager(QHelpEngine *engine, QObject *parent);

protected:
  virtual QNetworkReply *createRequest(Operation op,
                                       const QNetworkRequest &request, QIODevice *outgoingData = 0);

private:
  QHelpEngine *helpEngine;
};

HelpNetworkAccessManager::HelpNetworkAccessManager(QHelpEngine *engine,
                                                   QObject *parent)
  : QNetworkAccessManager(parent), helpEngine(engine)
{
}

QNetworkReply *HelpNetworkAccessManager::createRequest(Operation op,
                                                       const QNetworkRequest &request, QIODevice *outgoingData)
{
  const QString& scheme = request.url().scheme();
  if (scheme == QLatin1String("qthelp") || scheme == QLatin1String("about")) {
    const QUrl& url = request.url();
    QString mimeType = url.toString();
    if (mimeType.endsWith(QLatin1String(".svg"))
        || mimeType.endsWith(QLatin1String(".svgz"))) {
      mimeType = QLatin1String("image/svg+xml");
    }
    else if (mimeType.endsWith(QLatin1String(".css"))) {
      mimeType = QLatin1String("text/css");
    }
    else if (mimeType.endsWith(QLatin1String(".js"))) {
      mimeType = QLatin1String("text/javascript");
    } else {
      mimeType = QLatin1String("text/html");
    }
    return new HelpNetworkReply(request, helpEngine->fileData(url), mimeType);
  }
  return QNetworkAccessManager::createRequest(op, request, outgoingData);
}

class HelpPage : public QWebPage
{
public:
  HelpPage(QWidget *central, QHelpEngine *engine, QObject *parent);

protected:
  virtual QWebPage *createWindow(QWebPage::WebWindowType);

  virtual bool acceptNavigationRequest(QWebFrame *frame,
                                       const QNetworkRequest &request, NavigationType type);

private:
  QWidget *centralWidget;
  QHelpEngine *helpEngine;
};

HelpPage::HelpPage(QWidget *central, QHelpEngine *engine, QObject *parent)
  : QWebPage(parent), centralWidget(central), helpEngine(engine)
{
}

QWebPage *HelpPage::createWindow(QWebPage::WebWindowType)
{
  return new HelpPage(centralWidget, helpEngine, this);
}

static bool isLocalUrl(const QUrl &url)
{
  const QString scheme = url.scheme();
  if (scheme.isEmpty()
      || scheme == QLatin1String("file")
      || scheme == QLatin1String("qrc")
      || scheme == QLatin1String("data")
      || scheme == QLatin1String("qthelp")
      || scheme == QLatin1String("about"))
    return true;
  return false;
}

bool HelpPage::acceptNavigationRequest(QWebFrame *,
                                       const QNetworkRequest &request, QWebPage::NavigationType)
{
  const QUrl &url = request.url();
  if (isLocalUrl(url)) {
    if (url.path().endsWith(QLatin1String("pdf"))) {
      QString fileName = url.toString();
      fileName = QDir::tempPath() + QDir::separator() + fileName.right
          (fileName.length() - fileName.lastIndexOf(QChar('/')));

      QFile tmpFile(QDir::cleanPath(fileName));
      if (tmpFile.open(QIODevice::ReadWrite)) {
        tmpFile.write(helpEngine->fileData(url));
        tmpFile.close();
      }
      QDesktopServices::openUrl(QUrl(tmpFile.fileName()));
      return false;
    }
    return true;
  }

  QDesktopServices::openUrl(url);
  return false;
}




HelpBrowser::HelpBrowser(QWidget* parent)
  : QWebView(parent)
  , mpHelpEngine(NULL)
{
//  settings()->setAttribute(QWebSettings::PluginsEnabled, false);
//  settings()->setAttribute(QWebSettings::JavaEnabled, false);
  QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
  QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptEnabled, true);
  connect(this, SIGNAL(urlChanged(QUrl)), this, SIGNAL(sourceChanged(QUrl)));
  setAcceptDrops(false);
}

HelpBrowser::HelpBrowser(QHelpEngine* helpEngine, QWidget *parent)
  : QWebView(parent)
  , mpHelpEngine(helpEngine)
{
  settings()->setAttribute(QWebSettings::JavascriptEnabled, true);

//  settings()->setAttribute(QWebSettings::PluginsEnabled, false);
//  settings()->setAttribute(QWebSettings::JavaEnabled, false);
//
  connect(this, SIGNAL(urlChanged(QUrl)), this, SIGNAL(sourceChanged(QUrl)));
  setAcceptDrops(false);
}

HelpBrowser::~HelpBrowser()
{
}

void HelpBrowser::setHelpEngine(QHelpEngine* helpEngine)
{
  mpHelpEngine = helpEngine;

  setPage(new HelpPage((QWidget*)parent(), helpEngine, this));

  page()->setNetworkAccessManager(new HelpNetworkAccessManager(helpEngine, this));

  QAction* action = pageAction(QWebPage::OpenLinkInNewWindow);
  action->setText(tr("Open Link in New Tab"));
  if (!parent())
    action->setVisible(false);

  pageAction(QWebPage::DownloadLinkToDisk)->setVisible(false);
  pageAction(QWebPage::DownloadImageToDisk)->setVisible(false);
  pageAction(QWebPage::OpenImageInNewWindow)->setVisible(false);

}

//QVariant
//HelpBrowser::loadResource(int type, const QUrl& name)
//{
//  //if (mpHelpEngine != NULL &&  name.scheme() == "qthelp")
//    return QVariant(mpHelpEngine->fileData(name));
//  //else
//  //  return QTextBrowser::loadResource(type, name);
//}

#include <QDebug>
void HelpBrowser::setSource(const QUrl &url)
{
   qDebug() << page()->currentFrame()->toHtml();

  if (!homeUrl.isValid())
    homeUrl = url;

  load(url);
}

void HelpBrowser::home()
{
  if (homeUrl.isValid())
    setSource(homeUrl);
}

void HelpBrowser::load(const QUrl& url)
{
  if (mpHelpEngine != NULL &&  url.scheme() == "qthelp")
  {
    QWebView::load("file:///C:/DropBoxSBML/Dropbox/sbmlteam/deviser/qthelp/" + QFileInfo(url.path()).fileName());
  }
    //QWebView::setHtml(mpHelpEngine->fileData(url));
  else
    QWebView::load(url);
}

#else //USE_WEBVIEW

HelpBrowser::HelpBrowser(QWidget* parent)
  : QTextBrowser(parent)
  , mpHelpEngine(NULL)
{
}

HelpBrowser::HelpBrowser(QHelpEngine* helpEngine, QWidget *parent)
  : QTextBrowser(parent)
  , mpHelpEngine(helpEngine)
{
}

HelpBrowser::~HelpBrowser()
{
}

void HelpBrowser::setHelpEngine(QHelpEngine* helpEngine)
{
  mpHelpEngine = helpEngine;
}

QVariant
HelpBrowser::loadResource(int type, const QUrl& name)
{
  if (mpHelpEngine != NULL &&  name.scheme() == "qthelp")
    return QVariant(mpHelpEngine->fileData(name));
  else
    return QTextBrowser::loadResource(type, name);
}


void HelpBrowser::setSource(const QUrl &url)
{
  if (!url.isValid())
    return;

  if ( url.scheme() != "qthelp")
  {
    QDesktopServices::openUrl(url);
    return;
  }

  QUrl u = mpHelpEngine->findFile(url);
  if (u.isValid()) {
    QTextBrowser::setSource(u);
    return;
  }

}

#endif //USE_WEBVIEW

