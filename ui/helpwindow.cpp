#include "helpwindow.h"
#include "helpbrowser.h"
#include "ui_helpwindow.h"

#include <QHelpContentWidget>
#include <QHelpIndexWidget>
#include <QHelpSearchEngine>
#include <QHelpSearchQueryWidget>
#include <QHelpSearchResultWidget>

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

  tWidget->addTab(engine->contentWidget(), "Contents");

  QWidget *widget = new QWidget(this);
  QVBoxLayout *vLayout = new QVBoxLayout(widget);
  QHelpSearchQueryWidget* queryWidget = mpSearchEngine->queryWidget();
  QHelpSearchResultWidget* resultWidget = mpSearchEngine->resultWidget();

  vLayout->addWidget(queryWidget);
  vLayout->addWidget(resultWidget);

  widget->setLayout(vLayout);

  widget->setFocusProxy(queryWidget);

  tWidget->addTab(widget, "Search");
  //tWidget->addTab(engine->indexWidget(), "Index");

  ui->dockWidget->setWidget(tWidget);

  engine->contentWidget()->expandAll();

  connect(queryWidget, SIGNAL(search()), this, SLOT(search()));
  connect(resultWidget, SIGNAL(requestShowLink(QUrl)), ui->textBrowser, SLOT(setSource(QUrl)));

  connect(mpSearchEngine, SIGNAL(searchingStarted()), this, SLOT(searchingStarted()));
  connect(mpSearchEngine, SIGNAL(searchingFinished(int)), this, SLOT(searchingFinished(int)));

  mpSearchEngine->reindexDocumentation();

  connect(engine->contentWidget(),
          SIGNAL(linkActivated(QUrl)),
          ui->textBrowser, SLOT(setSource(QUrl)));
  connect(engine->indexWidget(),
          SIGNAL(linkActivated(QUrl, QString)),
          ui->textBrowser, SLOT(setSource(QUrl)));

  ui->textBrowser->setSource(QUrl("qthelp://org.sphinx.deviser.1.0/doc/deviser.html"));


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
