#include <QClipboard>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QActionGroup>
#include <QCloseEvent>
#include <QMimeData>
#include <QUrl>

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
#include "dialogpreferences.h"
#include "dialogerrors.h"

#include <model/deviserpackage.h>
#include <model/deviserclass.h>
#include <model/deviserversion.h>
#include <model/devisermapping.h>
#include <model/deviserenum.h>
#include <model/deviserplugin.h>
#include <model/devisersettings.h>

#include <validation/devisermessage.h>

#include <sstream>

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

  refreshRecentFiles();

  resize(DeviserSettings::getInstance()->getWidth(),
         DeviserSettings::getInstance()->getHeight());

  newModel();

}

MainWindow::~MainWindow()
{
  delete ui;
}

void
MainWindow::showAbout()
{
  DialogAbout about(this);
  about.exec();
}

void MainWindow::showAboutQt()
{
  QMessageBox::aboutQt(this, "Qt");
}

DeviserVersion*
MainWindow::getCurrentVersion()
{
  if (mCurrentVersion != NULL)
    return mCurrentVersion;

  if (mModel == NULL)
  {
    mModel = new DeviserPackage();
    connect(mModel, SIGNAL(modifiedChanged()), this, SLOT(documentModified()));
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
  DialogPreferences preferences(mModel, this);
  preferences.loadSettings();
  if (preferences.exec() == QDialog::Accepted)
    preferences.saveSettings();
}

void
MainWindow::fixErrors()
{
  mValidator.fixIssues(mModel);
  updateUI();
}

void
MainWindow::generate()
{
  if (askForSaveOrStop())
    return;

  int count = mValidator.validatePackage(mModel);
  if (count > 0 &&
      (mValidator.getNumErrors(DEVISER_ERROR) > 0 ||
       mValidator.getNumErrors(DEVISER_FATAL_ERROR) > 0 ))
  {
    if (validateDescription() == QDialog::Rejected)
      return;
  }

  DialogGenerate generate(this);
  generate.loadModel(mModel, mCurrentVersion, mFileName);
  generate.exec();
}

void
MainWindow::newModel()
{
  if (askForSaveOrStop())
    return;

  if (mModel != NULL)
  {
    mCurrentElement = NULL;
    mCurrentVersion = NULL;
    delete mModel;
  }

  mModel = new DeviserPackage();
  connect(mModel, SIGNAL(modifiedChanged()), this, SLOT(documentModified()));

  mCurrentElement = mModel;
  mCurrentVersion = mModel->getVersions()[0];
  mFileName = "";
  setCurrentFile(mFileName);
  updateUI();
  mModel->setModified(false);

}

void
fillExpandedMap(const QTreeWidgetItem* item, std::map<QString, bool> &expandedMap)
{
  expandedMap[item->text(0)] = item->isExpanded();
  for (int i = 0; i < item->childCount(); ++i)
  {
    QTreeWidgetItem* child = item->child(i);
    fillExpandedMap(child, expandedMap);
  }
}

void
fillExpandedMap(const QTreeWidget* widget, std::map<QString, bool> &expandedMap)
{
  for (int i = 0; i < widget->topLevelItemCount(); ++i)
  {
    QTreeWidgetItem* item = widget->topLevelItem(i);
    fillExpandedMap(item, expandedMap);
  }
}

void
MainWindow::updateUI()
{
  blockSignals(true);

  std::map<QString, bool> expandedMap;
  fillExpandedMap(ui->treeWidget, expandedMap);

  // build tree view
  const bool sortingEnabled = ui->treeWidget->isSortingEnabled();
  ui->treeWidget->setSortingEnabled(false);

  ui->treeWidget->clear();

  QTreeWidgetItem* packageItem = new QTreeWidgetItem(ui->treeWidget);
  packageItem->setText(0, "Package");

  foreach(DeviserVersion* version, mModel->getVersions())
  {
    disconnect(version, SIGNAL(identityChanged(const QString&, const QString&,const DeviserVersion*)),
      this, SLOT(treeElementRenamed(QString, QString,const DeviserVersion*)));
    connect(version, SIGNAL(identityChanged(const QString&, const QString&,const DeviserVersion*)),
      this, SLOT(treeElementRenamed(QString, QString,const DeviserVersion*)));


    QTreeWidgetItem* versionItem = new QTreeWidgetItem(ui->treeWidget);
    versionItem->setText(0, version->toString());
    versionItem->setExpanded(expandedMap[version->toString()]);

    QTreeWidgetItem* mappingItem = new QTreeWidgetItem(versionItem);
    mappingItem->setText(0, "Mappings");

    QTreeWidgetItem* classItem = new QTreeWidgetItem(versionItem);
    classItem->setText(0, "Classes");
    classItem->setExpanded(expandedMap["Classes"]);

    foreach(DeviserClass* element, version->getElements())
    {
      disconnect(element, SIGNAL(nameChanged(const QString&, const QString&,const DeviserVersion*)),
        this, SLOT(treeElementRenamed(QString, QString,const DeviserVersion*)));
      connect(element, SIGNAL(nameChanged(const QString&, const QString&,const DeviserVersion*)),
        this, SLOT(treeElementRenamed(QString, QString,const DeviserVersion*)));

      QTreeWidgetItem* currentItem = new QTreeWidgetItem(classItem);
      currentItem->setText(0, element->getName());
    }

    QTreeWidgetItem* pluginItem = new QTreeWidgetItem(versionItem);
    pluginItem->setText(0, "Plugins");
    pluginItem->setExpanded(expandedMap["Plugins"]);

    foreach(DeviserPlugin* element, version->getPlugins())
    {
      disconnect(element, SIGNAL(extensionPointChanged(const QString&, const QString&,const DeviserVersion*)),
        this, SLOT(treeElementRenamed(QString, QString,const DeviserVersion*)));
      connect(element, SIGNAL(extensionPointChanged(const QString&, const QString&,const DeviserVersion*)),
        this, SLOT(treeElementRenamed(QString, QString,const DeviserVersion*)));

      QTreeWidgetItem* currentItem = new QTreeWidgetItem(pluginItem);
      currentItem->setText(0, element->getExtensionPoint());
    }

    QTreeWidgetItem* enumItem = new QTreeWidgetItem(versionItem);
    enumItem->setText(0, "Enums");
    enumItem->setExpanded(expandedMap["Enums"]);

    foreach(DeviserEnum* element, version->getEnums())
    {
      disconnect(element, SIGNAL(nameChanged(const QString&, const QString&,const DeviserVersion*)),
        this, SLOT(treeElementRenamed(QString, QString,const DeviserVersion*)));
      connect(element, SIGNAL(nameChanged(const QString&, const QString&,const DeviserVersion*)),
        this, SLOT(treeElementRenamed(QString, QString,const DeviserVersion*)));

      QTreeWidgetItem* currentItem = new QTreeWidgetItem(enumItem);
      currentItem->setText(0, element->getName());
    }

  }

  ui->treeWidget->setSortingEnabled(sortingEnabled);

  displayElement(mCurrentElement);

  selectTreeItem(mCurrentElement);

  blockSignals(false);

}

void
MainWindow::addClass()
{
  mCurrentElement = getCurrentVersion()->createElement();
  connect(mCurrentElement, SIGNAL(nameChanged(const QString&, const QString&,const DeviserVersion*)),
          this, SLOT(treeElementRenamed(QString,QString,const DeviserVersion*)));
  updateUI();
}

void
MainWindow::addEnum()
{
  mCurrentElement = getCurrentVersion()->createEnum();
  connect(mCurrentElement, SIGNAL(nameChanged(const QString&, const QString&,const DeviserVersion*)),
          this, SLOT(treeElementRenamed(QString,QString,const DeviserVersion*)));
  updateUI();
}

void
MainWindow::addPlugin()
{
  mCurrentElement = getCurrentVersion()->createPlugin();
  connect(mCurrentElement, SIGNAL(extensionPointChanged(const QString&, const QString&,const DeviserVersion*)),
          this, SLOT(treeElementRenamed(QString,QString,const DeviserVersion*)));
  updateUI();
}

void
MainWindow::addVersion()
{
  mCurrentVersion = mModel->createVersion();
  mCurrentElement = mCurrentVersion;

  connect(mCurrentElement, SIGNAL(identityChanged(const QString&, const QString&,const DeviserVersion*)),
          this, SLOT(treeElementRenamed(QString,QString,const DeviserVersion*)));
  updateUI();
}

void
MainWindow::treeElementRenamed(const QString& oldId, const QString& newId,
                               const DeviserVersion* version)
{
  QList<QTreeWidgetItem*> items = ui->treeWidget->findItems(oldId, Qt::MatchExactly | Qt::MatchRecursive);
  QString parentVersion = version == NULL ? "" : version->toString();

  foreach(QTreeWidgetItem* item, items)
  {
    QString currentParent = item->parent() == NULL ? "" : item->parent()->parent()->text(0);
    if (parentVersion == currentParent)
    {
      item->setText(0, newId);
      break;
    }
  }
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
    mCurrentVersion = dynamic_cast<DeviserVersion*>(mCurrentElement);
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
    oldDir = QFileInfo(mFileName).dir().absolutePath();
  }

  QString fileName = QFileDialog::getOpenFileName(this, "Open Deviser Description", oldDir, "XML files (*.xml);;All files (*.*)");

  if (!fileName.isEmpty())
    openFile(fileName);

}

void MainWindow::openFile(const QString& fileName)
{
  if (askForSaveOrStop())
    return;

  if (mModel != NULL)
  {
    mCurrentElement = NULL;
    mCurrentVersion = NULL;
    delete mModel;
  }

  mFileName = fileName;
  mModel = new DeviserPackage(fileName);
  connect(mModel, SIGNAL(modifiedChanged()), this, SLOT(documentModified()));

  mCurrentElement = mModel;
  mCurrentVersion = getCurrentVersion();

  setCurrentFile(mFileName);
  updateUI();

  DeviserSettings::getInstance()->addRecentFile(fileName);
  refreshRecentFiles();

  mModel->setModified(false);

}

void
MainWindow::setCurrentFile(const QString& fileName)
{
  mFileName = fileName;
  setWindowModified(false);
  QString shownName = fileName;
  if (mFileName.isEmpty())
    shownName = "untitled.xml";

  setWindowFilePath(shownName);
}

void
MainWindow::saveFile()
{
  if (mModel == NULL) return;
  if (mFileName.isEmpty())
  {
    saveFileAs();
    return;
  }

  saveAsFile(mFileName);
}

void
MainWindow::saveFileAs()
{
  if (mModel == NULL) return;
  QString oldDir;
  if (!mFileName.isEmpty())
  {
    oldDir = QFileInfo(mFileName).dir().absolutePath();
  }
  QString fileName = QFileDialog::getSaveFileName(this, "Save Deviser Description", oldDir, "XML files (*.xml);;All files (*.*)");

  if (!fileName.isEmpty())
    saveAsFile(fileName);

}

void
MainWindow::saveAsFile(const QString& name)
{
  if (mModel == NULL) return;

  mFileName = name;
  mModel->writeTo(mFileName);
  setCurrentFile(mFileName);

}

void
MainWindow::showUML()
{
  DialogUML uml(this);
  uml.loadYuml(getCurrentVersion()->toYuml(true));
  uml.exec();
}

int
MainWindow::validateDescription()
{
  int count = mValidator.validatePackage(mModel);

  if (count == 0)
  {
    QMessageBox::information(this, "Package Validation",
                             "No validation issues have been found.",
                             QMessageBox::Ok, QMessageBox::Ok);
    return QDialog::Accepted;
  }
  else
  {
    DialogErrors errors(mValidator.errors(), this);
    return errors.exec();
  }
}

QTreeWidgetItem *
MainWindow::getTreeItemForDeviserItem(DeviserBase *item)
{
  if (mModel == NULL || item == NULL) return NULL;

  if (dynamic_cast<DeviserPackage*>(item) != NULL)
  {
    return ui->treeWidget->topLevelItem(0);
  }

  DeviserVersion* version = dynamic_cast<DeviserVersion*>(item);
  if (version != NULL)
  {
    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i)
    {
      QTreeWidgetItem* treeItem = ui->treeWidget->topLevelItem(i);
      if (version->toString() == treeItem->text(0))
        return treeItem;
    }
  }

  version = item->getParentVersion();

  if (version == NULL) return NULL;

  QTreeWidgetItem* versionItem = getTreeItemForDeviserItem(version);
  if (versionItem == NULL) return NULL;


  DeviserPlugin* plugin = dynamic_cast<DeviserPlugin*> (item);
  if (plugin != NULL)
  {
    QList<QTreeWidgetItem*> items = ui->treeWidget->findItems(plugin->getExtensionPoint(), Qt::MatchExactly | Qt::MatchRecursive);
    foreach(QTreeWidgetItem* treeItem, items)
    {
      if (treeItem->parent()->parent() == versionItem)
        return treeItem;
    }
  }

  DeviserClass* element = dynamic_cast<DeviserClass*> (item);
  if (element != NULL)
  {
    QList<QTreeWidgetItem*> items = ui->treeWidget->findItems(element->getName(), Qt::MatchExactly | Qt::MatchRecursive);
    foreach(QTreeWidgetItem* treeItem, items)
    {
      if (treeItem->parent()->parent() == versionItem)
        return treeItem;
    }
  }

  DeviserEnum* pEnum = dynamic_cast<DeviserEnum*> (item);
  if (pEnum != NULL)
  {
    QList<QTreeWidgetItem*> items = ui->treeWidget->findItems(pEnum->getName(), Qt::MatchExactly | Qt::MatchRecursive);
    foreach(QTreeWidgetItem* treeItem, items)
    {
      if (treeItem->parent()->parent() == versionItem)
        return treeItem;
    }
  }

  return NULL;
}


DeviserBase*
MainWindow::getDeviserItemForTreeView(QTreeWidgetItem* item)
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

void
MainWindow::selectTreeItem(DeviserBase *item)
{
  QTreeWidgetItem *treeItem = getTreeItemForDeviserItem(item);
  if (treeItem == NULL) return;
  treeItem->setSelected(true);
  ui->treeWidget->setCurrentItem(treeItem, 0, QItemSelectionModel::Select);
}


void
MainWindow::selectionChanged()
{
  const QList<QTreeWidgetItem*>& selectedItems = ui->treeWidget->selectedItems();
  if (selectedItems.size() == 0) return;

  foreach(QTreeWidgetItem* item, selectedItems)
  {
    DeviserBase* devItem = getDeviserItemForTreeView(item);
    if (devItem == NULL)
      continue;

    displayElement(devItem);
    break;
  }

}

void
MainWindow::deleteSelected()
{
  const QList<QTreeWidgetItem*>& selectedItems = ui->treeWidget->selectedItems();
  if (selectedItems.size() == 0) return;

  foreach(QTreeWidgetItem* item, selectedItems)
  {
    DeviserBase* devItem = getDeviserItemForTreeView(item);
    if (devItem == NULL || dynamic_cast<DeviserMapping*>(devItem) != NULL)
      continue;

    if (QMessageBox::question(this, QString("Delete %1?").arg(item->text(0)), QString("Are you sure you want to delete the element '%1'?").arg(item->text(0)))
        == QMessageBox::No)
      break;


    if (dynamic_cast<DeviserVersion*>(devItem) != NULL)
    {
      QTreeWidgetItem* toBeDeleted = ui->treeWidget->takeTopLevelItem(ui->treeWidget->indexOfTopLevelItem(item));
      if (toBeDeleted != NULL)
        delete toBeDeleted;

      int index = mModel->getVersions().indexOf(dynamic_cast<DeviserVersion*>(devItem));
      if (index != -1)
        delete mModel->getVersions().takeAt(index);
    }
    else
    {
      if (item->parent() != NULL && mCurrentVersion != NULL)
      {

        if (dynamic_cast<DeviserEnum*>(devItem) != NULL)
        {
          DeviserEnum* element = dynamic_cast<DeviserEnum*>(devItem);
          int index = mCurrentVersion->getEnums().indexOf(element);
          if (index != -1)
            delete mCurrentVersion->getEnums().takeAt(index);

        }
        else if (dynamic_cast<DeviserClass*>(devItem) != NULL)
        {
          DeviserClass* element = dynamic_cast<DeviserClass*>(devItem);
          int index = mCurrentVersion->getElements().indexOf(element);
          if (index != -1)
            delete mCurrentVersion->getElements().takeAt(index);
        }
        else if (dynamic_cast<DeviserPlugin*>(devItem) != NULL)
        {
          DeviserPlugin* element = dynamic_cast<DeviserPlugin*>(devItem);
          int index = mCurrentVersion->getPlugins().indexOf(element);
          if (index != -1)
            delete mCurrentVersion->getPlugins().takeAt(index);
        }

        QTreeWidgetItem* toBeDeleted = item->parent()->takeChild(item->parent()->indexOfChild(item));
        if (toBeDeleted != NULL)
          delete toBeDeleted;
      }
    }

    break;
  }
}



void
MainWindow::copyUML()
{
  const QList<QTreeWidgetItem*>& selectedItems = ui->treeWidget->selectedItems();
  if (selectedItems.size() == 0) return;

  foreach(QTreeWidgetItem* item, selectedItems)
  {
    DeviserBase* devItem = getDeviserItemForTreeView(item);
    if (devItem == NULL || dynamic_cast<DeviserMapping*>(devItem) != NULL)
      continue;

    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(devItem->toYuml(true));
    return;
  }

}

void
MainWindow::copyXML()
{
  const QList<QTreeWidgetItem*>& selectedItems = ui->treeWidget->selectedItems();
  if (selectedItems.size() == 0) return;

  foreach(QTreeWidgetItem* item, selectedItems)
  {
    DeviserBase* devItem = getDeviserItemForTreeView(item);
    if (devItem == NULL || dynamic_cast<DeviserMapping*>(devItem) != NULL)
      continue;

    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(devItem->toXmlString());
    return;
  }

}



void
MainWindow::duplicateSelected()
{
  const QList<QTreeWidgetItem*>& selectedItems = ui->treeWidget->selectedItems();
  if (selectedItems.size() == 0) return;

  foreach(QTreeWidgetItem* item, selectedItems)
  {
    DeviserBase* devItem = getDeviserItemForTreeView(item);
    if (devItem == NULL || dynamic_cast<DeviserMapping*>(devItem) != NULL)
      continue;

    if (dynamic_cast<DeviserVersion*>(devItem) != NULL)
    {

      DeviserVersion* current = dynamic_cast<DeviserVersion*>(devItem);
      DeviserVersion* newItem = new DeviserVersion(*current);

      int pkgVersion = current->getPkgVersion();
      while(mModel->getVersion(
              current->getLevel(),
              current->getVersion(),
              pkgVersion
              ))
        ++pkgVersion;

      newItem->setPkgVersion(pkgVersion);

      mModel->getVersions().append(newItem);

      mCurrentVersion = newItem;
      mCurrentElement = newItem;

      updateUI();

    }
    else if (dynamic_cast<DeviserEnum*>(devItem) != NULL)
    {
      DeviserEnum* current = dynamic_cast<DeviserEnum*>(devItem);
      DeviserEnum* newItem = new DeviserEnum(*current);

      newItem->setName(newItem->getName() + "_copy");
      mCurrentVersion->getEnums().append(newItem);
      newItem->setParentVersion(mCurrentVersion);
      mCurrentElement = newItem;

      updateUI();

    }
    else if (dynamic_cast<DeviserClass*>(devItem) != NULL)
    {
      DeviserClass* current = dynamic_cast<DeviserClass*>(devItem);
      DeviserClass* newItem = new DeviserClass(*current);

      newItem->setName(newItem->getName() + "_copy");
      mCurrentVersion->getElements().append(newItem);
      newItem->setParentVersion(mCurrentVersion);
      mCurrentElement = newItem;

      updateUI();
    }
    else if (dynamic_cast<DeviserPlugin*>(devItem) != NULL)
    {
      DeviserPlugin* current = dynamic_cast<DeviserPlugin*>(devItem);
      DeviserPlugin* newItem = new DeviserPlugin(*current);

      newItem->setExtensionPoint(newItem->getExtensionPoint() + "_copy");
      mCurrentVersion->getPlugins().append(newItem);
      newItem->setParentVersion(mCurrentVersion);

      mCurrentElement = newItem;

      updateUI();
    }

    break;
  }
}

void MainWindow::refreshRecentFiles()
{
  ui->menuRecentFiles->clear();

  QStringList recentFiles = DeviserSettings::getInstance()->getRecentFiles();
  int count = 0;
  foreach(QString filename, recentFiles)
  {
    QFileInfo info(filename);
    if (!info.exists())
    {
      DeviserSettings::getInstance()->removeRecentFile(filename);
      continue;
    }

    QAction* action = ui->menuRecentFiles->addAction(QString("&%1 %2")
                      .arg(QString::number(++count), info.fileName()));
    action->setData(filename);
  }

}

void MainWindow::openRecentFile(QAction *action)
{
  QString filename = action->data().toString();
  if (filename.isEmpty())
    return;

  openFile(filename);
}


void MainWindow::documentModified()
{
  if (mModel == NULL) return;

  setWindowModified(mModel->getModified());
}

bool MainWindow::askForSaveOrStop()
{
  if (mModel == NULL || !mModel->getModified()) return false;

  switch(QMessageBox::question(this, "Save Changes?",
                               "The document contains unsaved changes\n"
                               "Do you want to save the changes before exiting?",
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                               QMessageBox::Save))
  {
  case QMessageBox::Save:
    saveFile();
    return false;

  case QMessageBox::Discard:
    return false;

  default:
    return true;
  }
}

void MainWindow::reloadDocument()
{
  if (mFileName.isEmpty()) return;
  openFile(mFileName);
}

void MainWindow::generateContextMenuForTree(const QPoint& point)
{
  QMenu menu;

  menu.addAction(ui->actionAdd_Class);
  menu.addAction(ui->actionAdd_Plugin);
  menu.addAction(ui->actionAdd_Enum);
  menu.addAction(ui->actionAdd_Version);

  QTreeWidgetItem* item = ui->treeWidget->itemAt(point);

  if (item != NULL)
  {
    DeviserBase* deviserItem = getDeviserItemForTreeView(item);

    if (deviserItem != NULL)
    {
      bool isPlugin = dynamic_cast<DeviserPlugin*> (deviserItem) != NULL;
      bool isClass = dynamic_cast<DeviserClass*> (deviserItem) != NULL;
      bool isEnum = dynamic_cast<DeviserEnum*> (deviserItem) != NULL;
      bool isVersion = dynamic_cast<DeviserVersion*> (deviserItem) != NULL;
      bool isPackage = dynamic_cast<DeviserPackage*> (deviserItem) != NULL;
      bool isCommon = isVersion || isClass || isPlugin || isEnum;

      QAction* sep1 = new QAction(this);
      sep1->setSeparator(true);
      QAction* sep2 = new QAction(this);
      sep2->setSeparator(true);
      QAction* sep3 = new QAction(this);
      sep3->setSeparator(true);

      if (isCommon)
      {
        menu.addAction(sep1);
        menu.addAction(ui->actionDuplicate);
      }

      if (isCommon || isPackage)
      {
        menu.addAction(sep2);
        menu.addAction(ui->actionCopyXML);
        menu.addAction(ui->actionCopyUML);
      }

      if (isCommon)
      {
        menu.addAction(sep3);
        menu.addAction(ui->actionDeleteSelected);
      }

    }

  }

  menu.exec(ui->treeWidget->mapToGlobal(point));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  if (askForSaveOrStop())
  {
    event->ignore();
  }
  else
  {
    DeviserSettings::getInstance()->setWidth(width());
    DeviserSettings::getInstance()->setHeight(height());
    DeviserSettings::getInstance()->saveSettings();
    event->accept();
  }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
  if (e->mimeData()->hasUrls())
  {
    e->acceptProposedAction();
  }
}

void MainWindow::dropEvent(QDropEvent *e)
{
  foreach (const QUrl &url, e->mimeData()->urls())
  {
    // open only first file that is dropped
    const QString &fileName = url.toLocalFile();
    openFile(fileName);
    return;
  }
}
