#include "formdeviserclass.h"
#include "ui_formdeviserclass.h"

#include <QFileDialog>
#include <QTableWidgetItem>
#include <QSortFilterProxyModel>
#include <QMessageBox>

#include <model/deviserclass.h>
#include <model/deviserpackage.h>
#include <model/deviserattribute.h>
#include <model/deviserlistofattribute.h>
#include <model/deviserconcrete.h>

#include <ui/attributesmodel.h>
#include <ui/loattributesmodel.h>
#include <ui/concretesmodel.h>
#include <ui/typechooserdelegate.h>
#include <ui/attributedelegate.h>

#include <util.h>

#include <set>

FormDeviserClass::FormDeviserClass(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::FormDeviserClass)
  , mElement(NULL)
  , mpAttributes(NULL)
  , mpAttributesFilter(NULL)
  , mpLoAttributes(NULL)
  , mpLoAttributesFilter(NULL)
  , mpConcretes(NULL)
  , mpConcretesFilter(NULL)
  , mbInitializing(true)
{
  ui->setupUi(this);

  AttributeDelegate* delegate1 = new AttributeDelegate(ui->tblAttributes);
  ui->tblAttributes->setItemDelegate(delegate1);
  AttributeDelegate* delegate2 = new AttributeDelegate(ui->tblLoAttributes);
  ui->tblLoAttributes->setItemDelegate(delegate2);

}

FormDeviserClass::~FormDeviserClass()
{
  delete ui;
}

void
FormDeviserClass::initializeFrom(DeviserClass* element)
{
  mElement = element;

  mbInitializing = true;

  ui->txtBaseClass->clear();
  ui->txtDeclaration->clear();
  ui->txtImplementation->clear();
  ui->txtListOfClassName->clear();
  ui->txtListOfName->clear();
  ui->txtMaxNumChildren->clear();
  ui->txtMinNumChildren->clear();
  ui->txtName->clear();
  ui->txtTypeCode->clear();
  ui->txtXMLElementName->clear();

  ui->chkHasListOf->setChecked(false);
  ui->ctrlListOf->setVisible(false);
  ui->grpListOfAttributes->setVisible(false);

  ui->chkRequiresAdditionalCode->setChecked(false);
  ui->grpAdditional->setVisible(false);

  ui->chkIsBaseClass->setChecked(false);
  ui->grpInstantiations->setVisible(false);


  ui->tblAttributes->setModel(NULL);
  if (mpAttributesFilter != NULL)
    mpAttributesFilter->deleteLater();
  if (mpAttributes != NULL)
    mpAttributes->deleteLater();

  ui->tblLoAttributes->setModel(NULL);
  if (mpLoAttributesFilter != NULL)
    mpLoAttributesFilter->deleteLater();
  if (mpLoAttributes != NULL)
    mpLoAttributes->deleteLater();

  ui->tblInstantiations->setModel(NULL);
  if (mpConcretesFilter != NULL)
    mpConcretesFilter->deleteLater();
  if (mpConcretes!= NULL)
    mpConcretes->deleteLater();


  if (mElement != NULL)
  {
    ui->txtName->setText(element->getName());
    nameModified(element->getName());
    ui->txtBaseClass->setText(element->getBaseClass());

    const QString& typeCode = element->getTypeCode();
    const QString defaultTypeCode = element->getDefaultTypeCode();
    bool haveDefault = typeCode.isEmpty() || (typeCode == defaultTypeCode);
    ui->txtTypeCode->setText(element->getTypeCode());
    typeCodeModified(element->getTypeCode());
    ui->chkUseDefault->setChecked(true);

    ui->stackTypeCode->setCurrentIndex( haveDefault ? 1 : 0);

    ui->txtXMLElementName->setText(element->getElementName());

    ui->chkHasListOf->setChecked(
          element->hasListOf() ||
          !element->getListOfAttributes().empty() ||
          !element->getListOfName().isEmpty() ||
          !element->getListOfClassName().isEmpty() ||
          element->getMaxNumberChildren() != 0
        );
    ui->ctrlListOf->setVisible(ui->chkHasListOf->isChecked());
    ui->grpListOfAttributes->setVisible(ui->chkHasListOf->isChecked());

    ui->txtListOfName->setText(element->getListOfName());
    ui->txtListOfClassName->setText(element->getListOfClassName());
    if (element->getMinNumberChildren() != 1)
    ui->txtMinNumChildren->setText(QString::number(element->getMinNumberChildren()));
    if (element->getMaxNumberChildren() != 0)
    ui->txtMaxNumChildren->setText(QString::number(element->getMaxNumberChildren()));

    ui->txtDeclaration->setText(element->getAdditionalDeclarations());
    ui->txtImplementation->setText(element->getAdditionalDefinitions());
    ui->chkRequiresAdditionalCode->setChecked(!element->getAdditionalDeclarations().isEmpty() || !element->getAdditionalDefinitions().isEmpty());
    ui->grpAdditional->setVisible(ui->chkRequiresAdditionalCode->isChecked());

    ui->chkIsBaseClass->setChecked(element->isBaseClass() || !element->getConcretes().empty() );
    ui->grpInstantiations->setVisible(ui->chkIsBaseClass->isChecked());

    mpAttributesFilter = new QSortFilterProxyModel(this);
    mpAttributes = new AttributesModel(this, &element->getAttributes());
    mpAttributesFilter->setSourceModel(mpAttributes);
    ui->tblAttributes->setModel(mpAttributesFilter);

    mpLoAttributesFilter = new QSortFilterProxyModel(this);
    mpLoAttributes = new LoAttributesModel(this, &element->getListOfAttributes());
    mpLoAttributesFilter->setSourceModel(mpLoAttributes);
    ui->tblLoAttributes->setModel(mpLoAttributesFilter);

    mpConcretesFilter = new QSortFilterProxyModel(this);
    mpConcretes = new ConcretesModel(this, &element->getConcretes());
    mpConcretesFilter->setSourceModel(mpConcretes);
    ui->tblInstantiations->setModel(mpConcretesFilter);

  }

  mbInitializing = false;
}

void
FormDeviserClass::browseDefinitionClick()
{  
  if (mElement == NULL) return;
  QString fileName = QFileDialog::getOpenFileName(this, "Select Implementation file", NULL, Util::getImplementationFilter());
  mElement->setAdditionalDefinitions(fileName);
  ui->txtImplementation->setText(fileName);
}

void
FormDeviserClass::browseDeclarationClick()
{
  if (mElement == NULL) return;
  QString fileName = QFileDialog::getOpenFileName(this, "Select Declaration file", NULL, Util::getHeaderFilter());
  mElement->setAdditionalDeclarations(fileName);
  ui->txtDeclaration->setText(fileName);
}

void
FormDeviserClass::delConcrete()
{
  const QModelIndexList& list = ui->tblInstantiations->selectionModel()->selectedIndexes();
  if (list.count() == 0) return;

  std::set<int> rows;

  foreach(const QModelIndex& index, list)
  {
    rows.insert(index.row());
  }

  std::set<int>::reverse_iterator it = rows.rbegin();
  while (it != rows.rend())
  {
    mpConcretes->removeAttribute(*it);
    ++it;
  }

}

void
FormDeviserClass::delListOfAttribute()
{
  const QModelIndexList& list = ui->tblLoAttributes->selectionModel()->selectedIndexes();
  if (list.count() == 0) return;

  std::set<int> rows;

  foreach(const QModelIndex& index, list)
  {
    rows.insert(index.row());
  }

  std::set<int>::reverse_iterator it = rows.rbegin();
  while (it != rows.rend())
  {
    mpLoAttributes->removeAttribute(*it);
    ++it;
  }

}

void
FormDeviserClass::delAttribute()
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
FormDeviserClass::addListOfAttribute()
{
  if (mElement == NULL) return;

  mpLoAttributes->beginAdding();
  mElement->createListOfAttribute();
  mpLoAttributes->endAdding();
}

void
FormDeviserClass::addConcrete()
{
  if (mElement == NULL) return;

  mpConcretes->beginAdding();
  mElement->createConcrete();
  mpConcretes->endAdding();

}

void
FormDeviserClass::addAttribute()
{
  if (mElement == NULL) return;

  mpAttributes->beginAdding();
  mElement->createAttribute();
  mpAttributes->endAdding();
}

void
FormDeviserClass::xmlElementNameChanged(const QString&)
{
  if (mElement == NULL || mbInitializing) return;
  mElement->setElementName(ui->txtXMLElementName->text());
}

void
FormDeviserClass::typeCodeChanged(const QString&)
{
  if (mElement == NULL || mbInitializing) return;
  mElement->setTypeCode(ui->txtTypeCode->text());
}

void
FormDeviserClass::nameChanged(const QString&)
{
  if (mElement == NULL || mbInitializing) return;
  mElement->setName(ui->txtName->text());

}

void
FormDeviserClass::minNoChildrenChanged(const QString&)
{
  if (mElement == NULL || mbInitializing) return;
  mElement->setMinNumberChildren(ui->txtMinNumChildren->text().toInt());

}

void
FormDeviserClass::maxNoChildrenChanged(const QString&)
{
  if (mElement == NULL || mbInitializing) return;
  mElement->setMaxNumberChildren(ui->txtMaxNumChildren->text().toInt());

}

void
FormDeviserClass::listOfNameChanged(const QString&)
{
  if (mElement == NULL || mbInitializing) return;
  mElement->setListOfName(ui->txtListOfName->text());

}

void
FormDeviserClass::listOfClassNameChanged(const QString&)
{
  if (mElement == NULL || mbInitializing) return;
  mElement->setListOfClassName(ui->txtListOfClassName->text());

}

void
FormDeviserClass::definitionChanged(const QString&)
{
  if (mElement == NULL || mbInitializing) return;
  mElement->setAdditionalDefinitions(ui->txtImplementation->text());

}

void
FormDeviserClass::declarationChanged(const QString&)
{
  if (mElement == NULL || mbInitializing) return;
  mElement->setAdditionalDeclarations(ui->txtDeclaration->text());

}

void
FormDeviserClass::baseClassChanged(const QString&)
{
  if (mElement == NULL || mbInitializing) return;
  mElement->setBaseClass(ui->txtBaseClass->text());

}

void
FormDeviserClass::requiresStateChanged(int)
{
  ui->grpAdditional->setVisible(ui->chkRequiresAdditionalCode->isChecked());
}

void
FormDeviserClass::isBaseClassStateChanged(int)
{
  if (mElement == NULL || mbInitializing) return;
  mElement->setIsBaseClass(ui->chkIsBaseClass->isChecked());

  ui->grpInstantiations->setVisible(ui->chkIsBaseClass->isChecked());
}

void
FormDeviserClass::hasListOfStateChanged(int)
{
  if (mElement == NULL || mbInitializing) return;
  mElement->setHasListOf(ui->chkHasListOf->isChecked());

  ui->ctrlListOf->setVisible(ui->chkHasListOf->isChecked());
  ui->grpListOfAttributes->setVisible(ui->chkHasListOf->isChecked());

}

void FormDeviserClass::defaultXmlElementName()
{
  if (ui->txtName->text().isEmpty()) return;
  QString newXmlElementName = Util::lowerFirst(ui->txtName->text());
  ui->txtXMLElementName->setText(newXmlElementName);
  xmlElementNameChanged(newXmlElementName);
}

void FormDeviserClass::defaultTypeCode()
{
  QString defaultTypeCode = mElement->getDefaultTypeCode();
  if (defaultTypeCode.isEmpty())
  {
    QMessageBox::critical(this, "Can't generate type code", "The type code can only be generated, once the package has been named, and the name of the class has been specified.");
    return;
  }

  ui->txtTypeCode->setText(defaultTypeCode);
  typeCodeChanged(defaultTypeCode);
}

void FormDeviserClass::defaultListOfName()
{
  if (ui->txtName->text().isEmpty())
  {
    QMessageBox::critical(this, "Can't generate name", "The listOf name can only be generated, once the class has been specified.");
    return;
  }
  QString newListOfName = QString("listOf%1")
      .arg(Util::upperFirst(Util::guessPlural(ui->txtName->text())));
  ui->txtListOfName->setText(newListOfName);
  listOfNameChanged(newListOfName);

}

void FormDeviserClass::defaultBaseClass()
{
  QString newBaseClass;
  if (mElement == NULL || mElement->getParent() == NULL  || mElement->getParent()->getLanguage().baseClass().isEmpty())
  {
    newBaseClass = "SBase";
  }
  else
  {
    newBaseClass = mElement->getParent()->getLanguage().baseClass();
  }
  ui->txtBaseClass->setText(newBaseClass);
  baseClassChanged(newBaseClass);
}

void FormDeviserClass::defaultListOfClassName()
{
  if (ui->txtName->text().isEmpty())
  {
    QMessageBox::critical(this, "Can't generate name", "The listOf class name can only be generated, once the class has been specified.");
    return;
  }

  QString newListOfClassName = Util::upperFirst( QString("listOf%1")
                                                 .arg(Util::upperFirst(Util::guessPlural(ui->txtName->text()))));
  ui->txtListOfClassName->setText(newListOfClassName);
  listOfClassNameChanged(newListOfClassName);

}

void FormDeviserClass::defaultToggled(bool isChecked)
{
  if (mbInitializing || mElement == NULL) return;

  const QString& typeCode = mElement->getTypeCode();
  if (typeCode.isEmpty() && !isChecked)
  {
    QString defaultTypecode = mElement->getDefaultTypeCode();
    mElement->setTypeCode(defaultTypecode);
    ui->txtTypeCode->setText(defaultTypecode);
    typeCodeChanged(defaultTypecode);
  }

  ui->stackTypeCode->setCurrentIndex( isChecked ? 1 : 0);

}

void
FormDeviserClass::nameModified(const QString &value)
{
  if (value.isEmpty() || QRegExp("\\s*").exactMatch(value))
    ui->txtName->setStyleSheet(Util::getErrorStyleSheet());
  else
    ui->txtName->setStyleSheet("");
}

void
FormDeviserClass::typeCodeModified(const QString &value)
{
  if (value.isEmpty() || QRegExp("\\s*").exactMatch(value))
    ui->txtTypeCode->setStyleSheet(Util::getErrorStyleSheet());
  else
    ui->txtTypeCode->setStyleSheet("");
}
