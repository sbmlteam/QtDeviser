#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "formdeviserpackage.h"
#include "formdeviserversion.h"
#include "formdeviserenum.h"
#include "formdevisermapping.h"
#include "formdeviserclass.h"
#include "formdeviserplugin.h"

#include "dialogabout.h"
#include "dialoguml.h"
#include "dialoggenerate.h"

#include <model/deviserpackage.h>
#include <model/deviserclass.h>
#include <model/deviserversion.h>
#include <model/devisermapping.h>
#include <model/deviserenum.h>
#include <model/deviserplugin.h>

MainWindow::MainWindow(QWidget *parent) 
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , ctrlPackage(new FormDeviserPackage(this))
  , ctrlVersion(new FormDeviserVersion(this))
  , ctrlEnum(new FormDeviserEnum(this))
  , ctrlMapping(new FormDeviserMapping(this))
  , ctrlClass(new FormDeviserClass(this))
  , ctrlPlugin(new FormDeviserPlugin(this))
  , mModel(NULL)
  , mCurrentVersion(NULL)
  , mCurrentElement(NULL)
  , mFileName()

{
  ui->setupUi(this);

  ui->stackedWidget->addWidget(ctrlPackage);
  ui->stackedWidget->addWidget(ctrlVersion);
  ui->stackedWidget->addWidget(ctrlEnum);
  ui->stackedWidget->addWidget(ctrlMapping);
  ui->stackedWidget->addWidget(ctrlClass);
  ui->stackedWidget->addWidget(ctrlPlugin);

  ui->stackedWidget->setCurrentWidget(ctrlPackage);

  newModel();

}

MainWindow::~MainWindow()
{
  delete ui;
}


void
MainWindow::showAbout()
{
  DialogAbout about;
  about.exec();
}

void
MainWindow::addClass()
{
  mCurrentElement =  getCurrentVersion()->createElement();
  updateUI();
}

void
MainWindow::addEnum()
{
  mCurrentElement =  getCurrentVersion()->createEnum();
  updateUI();
}

void
MainWindow::addPlugin()
{
  mCurrentElement =  getCurrentVersion()->createPlugin();
  updateUI();
}

void
MainWindow::addVersion()
{
  DeviserVersion* version =  mModel->createVersion();
  displayElement(version);
}

DeviserVersion*
MainWindow::getCurrentVersion()
{
    if (mCurrentVersion != NULL)
        return mCurrentVersion;

    if (mModel == NULL)
    {
        mModel = new DeviserPackage();
    }

    if (mModel->getVersions().empty())
    {
        mModel->createVersion();
    }

    mCurrentVersion = mModel->getVersions()[0];

    return mCurrentVersion;
}

void
MainWindow::editPreferences()
{

}

void
MainWindow::fixErrors()
{

}

void
MainWindow::generate()
{
  DialogGenerate generate;
  generate.exec();
}

void
MainWindow::newModel()
{
  if (mModel != NULL)
    delete mModel;

  mModel = new DeviserPackage();
  mCurrentElement = mModel;
  mFileName = "";
  updateUI();

}

void
MainWindow::updateUI()
{
  blockSignals(true);
  // build tree view
  const bool sortingEnabled = ui->treeWidget->isSortingEnabled();
  ui->treeWidget->setSortingEnabled(false);

  ui->treeWidget->clear();

  QTreeWidgetItem* packageItem = new QTreeWidgetItem(ui->treeWidget);
  packageItem->setText(0, "Package");

  foreach(auto& version, mModel->getVersions())
  {
    QTreeWidgetItem* versionItem = new QTreeWidgetItem(ui->treeWidget);
    versionItem->setText(0, version->toString());
    versionItem->setExpanded(true);

    QTreeWidgetItem* mappingItem = new QTreeWidgetItem(versionItem);
    mappingItem->setText(0, "Mappings");

    QTreeWidgetItem* classItem = new QTreeWidgetItem(versionItem);
    classItem->setText(0, "Classes");

    foreach(auto* element, version->getElements())
    {
      QTreeWidgetItem* currentItem = new QTreeWidgetItem(classItem);
      currentItem->setText(0, element->getName());
    }

    QTreeWidgetItem* pluginItem = new QTreeWidgetItem(versionItem);
    pluginItem->setText(0, "Plugins");

    foreach(auto* element, version->getPlugins())
    {
      QTreeWidgetItem* currentItem = new QTreeWidgetItem(pluginItem);
      currentItem->setText(0, element->getExtensionPoint());
    }

    QTreeWidgetItem* enumItem = new QTreeWidgetItem(versionItem);
    enumItem->setText(0, "Enums");

    foreach(auto* element, version->getEnums())
    {
      QTreeWidgetItem* currentItem = new QTreeWidgetItem(enumItem);
      currentItem->setText(0, element->getName());
    }

  }

  ui->treeWidget->setSortingEnabled(sortingEnabled);

  displayElement(mCurrentElement);

  blockSignals(false);

}

void
MainWindow::displayElement(DeviserBase* element)
{
  mCurrentElement = element;

  if (dynamic_cast<DeviserPackage*>(mCurrentElement))
  {
    ctrlPackage->initializeFrom(dynamic_cast<DeviserPackage*>(mCurrentElement));
    ui->stackedWidget->setCurrentWidget(ctrlPackage);
  }
  else if (dynamic_cast<DeviserVersion*>(mCurrentElement))
  {
    ctrlVersion->initializeFrom(dynamic_cast<DeviserVersion*>(mCurrentElement));
    ui->stackedWidget->setCurrentWidget(ctrlVersion);
  }
  else if (dynamic_cast<DeviserClass*>(mCurrentElement))
  {
    ctrlClass->initializeFrom(dynamic_cast<DeviserClass*>(mCurrentElement));
    ui->stackedWidget->setCurrentWidget(ctrlClass);
  }
  else if (dynamic_cast<DeviserPlugin*>(mCurrentElement))
  {
    ctrlPlugin->initializeFrom(dynamic_cast<DeviserPlugin*>(mCurrentElement));
    ui->stackedWidget->setCurrentWidget(ctrlPlugin);
  }
  else if (dynamic_cast<DeviserEnum*>(mCurrentElement))
  {
    ctrlEnum->initializeFrom(dynamic_cast<DeviserEnum*>(mCurrentElement));
    ui->stackedWidget->setCurrentWidget(ctrlEnum);
  }
  else if (dynamic_cast<DeviserMapping*>(mCurrentElement))
  {
    ctrlMapping->initializeFrom(mCurrentVersion);
    ui->stackedWidget->setCurrentWidget(ctrlMapping);
  }


}

void
MainWindow::openFile()
{

  QString oldDir;
  if (!mFileName.isEmpty())
  {
    oldDir = QFileInfo(mFileName).dir().dirName();
  }

  QString fileName = QFileDialog::getOpenFileName(this, "Open Deviser Description", oldDir, "XML files (*.xml);;All files (*.*)");

  if (!fileName.isEmpty())
    openFile(fileName);



}

void MainWindow::openFile(const QString& fileName)
{
  if (mModel != NULL)
    delete mModel;

  mModel = new DeviserPackage(fileName);
  mCurrentElement = mModel;
  updateUI();

}

void
MainWindow::saveFile()
{
  if (mModel == NULL) return;
}

void
MainWindow::saveFileAs()
{
  if (mModel == NULL) return;
}

void
MainWindow::saveAsFile(QString)
{
  if (mModel == NULL) return;
}

void
MainWindow::showUML()
{
  DialogUML uml;
  uml.exec();
}

void
MainWindow::validateDescription()
{

}

DeviserBase* MainWindow::getDeviserItemForTreeView(QTreeWidgetItem* item)
{
  if (mModel == NULL) return NULL;

  if (item->text(0) == "Package")
  {
    return mModel;
  }

  if (item->text(0).startsWith("Version"))
  {
    return mModel->getVersion(item->text(0));
  }

  if (item->text(0) == "Mappings")
  {
    return new DeviserMapping();

  }


  QTreeWidgetItem* parent = item->parent();
  if (parent == NULL) return NULL;

  QTreeWidgetItem* parentsParent = parent != NULL ? parent->parent() : NULL;

  mCurrentVersion = parentsParent != NULL ? mModel->getVersion(parentsParent->text(0)) :
    mModel->getVersion(parent->text(0));
  
  if (parent != NULL && parent->text(0) == "Classes")
  {
    return mCurrentVersion->getElement(item->text(0));    
  }
  
  if (parent != NULL && parent->text(0) == "Plugins")
  {
    return mCurrentVersion->getPlugin(item->text(0));
  }
  
  if (parent != NULL && parent->text(0) == "Enums")
  {
    return mCurrentVersion->getEnum(item->text(0));
  }

  return NULL;
}


void MainWindow::on_treeWidget_itemSelectionChanged()
{
  const QList<QTreeWidgetItem*>& selectedItems = ui->treeWidget->selectedItems();
  if (selectedItems.size() == 0) return;

  foreach(QTreeWidgetItem* item, selectedItems) 
  {
    DeviserBase* devItem = getDeviserItemForTreeView(item);
    if (devItem != NULL)
      displayElement(devItem);

  }

}
