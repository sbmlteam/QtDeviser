#include "helpwindow.h"
#include <ui/helpbrowser.h>
#include "ui_helpwindow.h"

#include <QHelpContentWidget>
#include <QHelpIndexWidget>
#include <QHelpSearchEngine>
#include <QHelpSearchQueryWidget>
#include <QHelpSearchResultWidget>
#include <QTimer>

#include <QVBoxLayout>

HelpWindow::HelpWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::HelpWindow)
  , mpHelpEngine(NULL)
  , mpSearchEngine(NULL)
{
  ui->setupUi(this);
}

void HelpWindow::setHelpEngine(QHelpEngine* engine)
{
  mpHelpEngine = engine;
  mpSearchEngine = engine->searchEngine();

  ui->textBrowser->setHelpEngine(engine);

  QTabWidget* tWidget = new QTabWidget;
  tWidget->setMaximumWidth(200);


  QWidget *widget = new QWidget(this);
  QVBoxLayout *vLayout = new QVBoxLayout(widget);

  QHelpSearchQueryWidget* queryWidget = mpSearchEngine->queryWidget();
  QHelpSearchResultWidget* resultWidget = mpSearchEngine->resultWidget();
  QHelpContentWidget * contentWidget = engine->contentWidget();

  vLayout->addWidget(queryWidget);
  vLayout->addWidget(resultWidget);

  widget->setLayout(vLayout);
  widget->setFocusProxy(queryWidget);

  mpSearchEngine->reindexDocumentation();

  tWidget->addTab(contentWidget, "Contents");
  tWidget->addTab(widget, "Search");

  // no use in displaying the index for now as we don't
  // have one specified yet
  //tWidget->addTab(engine->indexWidget(), "Index");

  ui->dockWidget->setWidget(tWidget);

  connect(queryWidget, SIGNAL(search()), this, SLOT(search()));
  connect(resultWidget, SIGNAL(requestShowLink(QUrl)), ui->textBrowser, SLOT(setSource(QUrl)));

  connect(contentWidget,
          SIGNAL(linkActivated(QUrl)),
          ui->textBrowser, SLOT(setSource(QUrl)));
  connect(engine->indexWidget(),
          SIGNAL(linkActivated(QUrl, QString)),
          ui->textBrowser, SLOT(setSource(QUrl)));


  contentWidget->setItemsExpandable(true);


  ui->textBrowser->setSource(QUrl("qthelp://org.sphinx.deviser.1.0/doc/deviser.html"));


  // expanding the content for whatever reason does not work
  // right away, so we delay it for a bit.
  QTimer::singleShot(100, contentWidget, SLOT(expandAll()));

}

HelpWindow::~HelpWindow()
{
  delete ui;
}

void HelpWindow::search()
{
  if (mpHelpEngine == NULL || mpSearchEngine == NULL) return;

  QList<QHelpSearchQuery> query = mpSearchEngine->queryWidget()->query();
  mpSearchEngine->search(query);

}
