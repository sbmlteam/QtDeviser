#ifndef HELPBROWSER_H
#define HELPBROWSER_H

#include <QTextBrowser>
#include <QHelpEngine>
#include <QUrl>

#define  USE_WEBVIEW 0
#if USE_WEBVIEW
#include <QWebView>

class HelpBrowser : public QWebView
{
  Q_OBJECT

public:
  HelpBrowser(QWidget *parent = 0);
  HelpBrowser(QHelpEngine* helpEngine, QWidget *parent = 0);
  virtual ~HelpBrowser();

  void setHelpEngine(QHelpEngine* helpEngine);

  inline QUrl source() const
  { return url(); }

  inline QString documentTitle() const
  { return title(); }

  inline bool hasSelection() const
  { return !selectedText().isEmpty(); }

public slots:
  void load(const QUrl & url);
  void setSource(const QUrl &url);
  void home();
  void backward() { back(); }

signals:
  void sourceChanged(const QUrl &);

private:
  QHelpEngine* mpHelpEngine;
  QUrl homeUrl;
};


#else
class HelpBrowser : public QTextBrowser
{
  Q_OBJECT

public:
  HelpBrowser(QWidget *parent = 0);
  HelpBrowser(QHelpEngine* helpEngine, QWidget *parent = 0);
  virtual ~HelpBrowser();
  void setSource(const QUrl &url);

  void setHelpEngine(QHelpEngine* helpEngine);
  QVariant loadResource(int type, const QUrl &name);

private:
  QHelpEngine* mpHelpEngine;
};
#endif

#endif // HELPBROWSER_H
