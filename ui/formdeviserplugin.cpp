#include "formdeviserplugin.h"
#include "ui_formdeviserplugin.h"
#include "util.h"

#include <set>

#include <QFileDialog>
#include <QSortFilterProxyModel>

#include <model/deviserplugin.h>
#include <model/deviserclass.h>
#include <model/deviserversion.h>
#include <model/deviserattribute.h>

#include <ui/attributesmodel.h>
#include <ui/typechooserdelegate.h>
#include <ui/attributedelegate.h>

FormDeviserPlugin::FormDeviserPlugin(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::FormDeviserPlugin)
  , mPlugin(NULL)
  , mpAttributes(NULL)
  , mpAttributesFilter(NULL)
  , mbInitializing(true)
{
  ui->setupUi(this);

  AttributeDelegate* delegate = new AttributeDelegate(ui->tblAttributes);
  ui->tblAttributes->setItemDelegate(delegate);

}

FormDeviserPlugin::~FormDeviserPlugin()
{
  delete ui;
}


void
FormDeviserPlugin::initializeFrom(DeviserPlugin* plugin)
{
  mbInitializing = true;

  mPlugin = plugin;
  
  ui->txtDeclaration->clear();
  ui->txtExtensionPoint->clear();
  ui->txtImplementation->clear();
  ui->txtPackage->clear();
  ui->txtTypeCode->clear();

  ui->chkElementFromCore->setChecked(true);
  ui->ctrlLocation->setVisible(false);
  ui->chkHasAttributes->setChecked(false);
  ui->grpAttributes->setVisible(false);
  ui->chkRequiresAdditionalCode->setChecked(false);
  ui->grpAdditional->setVisible(false);

  ui->tblAttributes->setModel(NULL);
  if (mpAttributesFilter != NULL)
    mpAttributesFilter->deleteLater();
  if (mpAttributes != NULL)
    mpAttributes->deleteLater();

  ui->lstChildClasses->clear();
  ui->lstDefinedClasses->clear();

  if (mPlugin != NULL)
  {
    ui->txtExtensionPoint->setText(plugin->getExtensionPoint());
    extensionModified(plugin->getExtensionPoint());

    ui->chkElementFromCore->setChecked(plugin->getPackage().isEmpty() && plugin->getTypeCode().isEmpty());
    ui->txtPackage->setText(plugin->getPackage());
    ui->txtTypeCode->setText(plugin->getTypeCode());

    ui->chkHasAttributes->setChecked(!plugin->getAttributes().empty());
    ui->grpAttributes->setVisible(!plugin->getAttributes().empty());

    mpAttributesFilter = new QSortFilterProxyModel(this);
    mpAttributes = new AttributesModel(this, &plugin->getAttributes());
    mpAttributesFilter->setSourceModel(mpAttributes);
    ui->tblAttributes->setModel(mpAttributesFilter);

    ui->txtDeclaration->setText(plugin->getAdditionalDeclarations());
    ui->txtImplementation->setText(plugin->getAdditionalDefinitions());
    ui->chkRequiresAdditionalCode->setChecked(!plugin->getAdditionalDefinitions().isEmpty() ||
                                              !plugin->getAdditionalDeclarations().isEmpty());
    ui->grpAdditional->setVisible(ui->chkRequiresAdditionalCode->isChecked());

    foreach(DeviserClass* element, plugin->getParentVersion()->getElements())
    {
      ui->lstDefinedClasses->addItem(element->getName());
      if (element->hasListOf())
      {
        ui->lstDefinedClasses->addItem(element->getActualListOfName());
      }
    }

    foreach(DeviserReferenceAttribute* element, plugin->getReferences())
      ui->lstChildClasses->addItem(element->getName());



  }


  mbInitializing = false;
}

void
FormDeviserPlugin::typeCodeChanged(const QString& tc)
{
  if (mPlugin == NULL || mbInitializing) return;
  mPlugin->setTypeCode(tc);

}

void
FormDeviserPlugin::packageChanged(const QString& package)
{
  if (mPlugin == NULL || mbInitializing) return;
  mPlugin->setPackage(package);
}

void
FormDeviserPlugin::implementationChanged(const QString& implementation)
{
  if (mPlugin == NULL || mbInitializing) return;
  mPlugin->setAdditionalDefinitions(implementation);
}

void
FormDeviserPlugin::extensionPointChanged(const QString& extPoint)
{
  if (mPlugin == NULL || mbInitializing) return;
  mPlugin->setExtensionPoint(extPoint);
}

void FormDeviserPlugin::extensionModified(const QString &value)
{
  if (value.isEmpty() || QRegExp("\\s*").exactMatch(value))
    ui->txtExtensionPoint->setStyleSheet(Util::getErrorStyleSheet());
  else
    ui->txtExtensionPoint->setStyleSheet("");
}

void
FormDeviserPlugin::declarationChanged(const QString& declaration)
{
  if (mPlugin == NULL || mbInitializing) return;
  mPlugin->setAdditionalDeclarations(declaration);
}


void
FormDeviserPlugin::upClicked()
{
  if (mPlugin == NULL || mbInitializing) return;
  
  const QList<QListWidgetItem*>& selected = ui->lstChildClasses->selectedItems();
  foreach(const QListWidgetItem* item, selected)
  {
    int row = ui->lstChildClasses->row(item);
    if (row == 0) continue;
    
    QListWidgetItem* taken = ui->lstChildClasses->takeItem(row);
    ui->lstChildClasses->insertItem(row - 1, taken);
    DeviserReferenceAttribute* attribute = mPlugin->getReferences().takeAt(row);
    mPlugin->getReferences().insert(row - 1, attribute);

    ui->lstChildClasses->setCurrentRow(row - 1);
    break;
  }
}

void
FormDeviserPlugin::downClicked()
{
  if (mPlugin == NULL || mbInitializing) return;

  const QList<QListWidgetItem*>& selected = ui->lstChildClasses->selectedItems();
  foreach(const QListWidgetItem* item, selected)
  {
    int row = ui->lstChildClasses->row(item);
    if (row == ui->lstChildClasses->count()-1) continue;

    QListWidgetItem* taken = ui->lstChildClasses->takeItem(row);
    ui->lstChildClasses->insertItem(row + 1, taken);
    DeviserReferenceAttribute* attribute = mPlugin->getReferences().takeAt(row);
    mPlugin->getReferences().insert(row + 1, attribute);

    ui->lstChildClasses->setCurrentRow(row + 1);
    break;

  }
}

void
FormDeviserPlugin::addChild()
{
  if (mPlugin == NULL || mbInitializing) return;
  const QList<QListWidgetItem*>& selected = ui->lstDefinedClasses->selectedItems();
  foreach(const QListWidgetItem* item, selected)
  {
    if (mPlugin->containsReference(item->text()))
      continue;

    ui->lstChildClasses->addItem(item->text());
    mPlugin->addReference(item->text());
  }
}

void
FormDeviserPlugin::delChild()
{
  if (mPlugin == NULL || mbInitializing) return;
  const QList<QListWidgetItem*>& selected = ui->lstChildClasses->selectedItems();
  foreach(const QListWidgetItem* item, selected)
  {
    mPlugin->removeReference(item->text());
    delete ui->lstChildClasses->takeItem(ui->lstChildClasses->row(item));    
  }
}

void
FormDeviserPlugin::browseImplementation()
{
  if (mPlugin == NULL || mbInitializing) return;
  QString fileName = QFileDialog::getOpenFileName(this, "Select Implementation file", NULL, "C++ files (*.c, *.c++, *.cpp, *.cc, *.cxx);;All files (*.*)");
  mPlugin->setAdditionalDefinitions(fileName);
  ui->txtImplementation->setText(fileName);
}

void
FormDeviserPlugin::browseDeclaration()
{
  if (mPlugin == NULL || mbInitializing) return;
  QString fileName = QFileDialog::getOpenFileName(this, "Select Declaration file", NULL, "Header files (*.h, *.h++, *.hpp, *.hh, *.hxx);;All files (*.*)");
  mPlugin->setAdditionalDeclarations(fileName);
  ui->txtDeclaration->setText(fileName);
}

void
FormDeviserPlugin::delAttribute()
{
  const QModelIndexList& list = ui->tblAttributes->selectionModel()->selectedIndexes();
  if (list.count() == 0) return;

  std::set<int> rows;

  foreach(const QModelIndex& index, list)
  {
    rows.insert(index.row());
  }

  std::set<int>::reverse_iterator it = rows.rbegin();
  while (it != rows.rend())
  {
    mpAttributes->removeAttribute(*it);
    ++it;
  }
}

void
FormDeviserPlugin::addAttribute()
{
  if (mPlugin == NULL || mbInitializing) return;

  mpAttributes->beginAdding();
  mPlugin ->createAttribute();
  mpAttributes->endAdding();

}

void
FormDeviserPlugin::additionalCodeStateChanged(int)
{
  ui->grpAdditional->setVisible(ui->chkRequiresAdditionalCode->isChecked());
}

void
FormDeviserPlugin::hasAttributesStateChanged(int)
{
  ui->grpAttributes->setVisible(ui->chkHasAttributes->isChecked());
}

void
FormDeviserPlugin::fromCoreStateChanged(int)
{
  ui->ctrlLocation->setVisible(!ui->chkElementFromCore->isChecked());
}
