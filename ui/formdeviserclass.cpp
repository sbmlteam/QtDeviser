#include "formdeviserclass.h"
#include "ui_formdeviserclass.h"

#include <QFileDialog>
#include <QTableWidgetItem>
#include <QSortFilterProxyModel>

#include <model/deviserclass.h>
#include <model/deviserpackage.h>
#include <model/deviserattribute.h>
#include <model/deviserlistofattribute.h>
#include <model/deviserconcrete.h>

#include <ui/attributesmodel.h>
#include <ui/loattributesmodel.h>
#include <ui/concretesmodel.h>

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
    ui->txtBaseClass->setText(element->getBaseClass());
    ui->txtTypeCode->setText(element->getTypeCode());
    ui->txtXMLElementName->setText(element->getElementName());

    ui->chkHasListOf->setChecked(
          element->hasListOf() ||
          !element->getListOfAttributes().empty() ||
          !element->getListOfName().isEmpty() ||
          !element->getListOfClassName().isEmpty() ||
          element->getMaxNumberChildren() != 0 ||
        element->getMinNumberChildren() != 0
        );
    ui->ctrlListOf->setVisible(ui->chkHasListOf->isChecked());
    ui->grpListOfAttributes->setVisible(ui->chkHasListOf->isChecked());

    ui->txtListOfName->setText(element->getListOfName());
    ui->txtListOfClassName->setText(element->getListOfClassName());
    if (element->getMinNumberChildren() != 0)
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
  QString fileName = QFileDialog::getOpenFileName(this, "Select Implementation file", NULL, "C++ files (*.c, *.c++, *.cpp, *.cc, *.cxx);;All files (*.*)");
  mElement->setAdditionalDefinitions(fileName);
  ui->txtImplementation->setText(fileName);
}

void
FormDeviserClass::browseDeclarationClick()
{
  if (mElement == NULL) return;
  QString fileName = QFileDialog::getOpenFileName(this, "Select Declaration file", NULL, "Header files (*.h, *.h++, *.hpp, *.hh, *.hxx);;All files (*.*)");
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
  if (ui->txtName->text().isEmpty()) return;
  if (mElement == NULL || mElement->getParent() == NULL || mElement->getParent()->getName().isEmpty())
    return;

  QString newTypeCode = QString("SBML_%1_%2")
                             .arg(mElement->getParent()->getName().toUpper())
                             .arg(ui->txtName->text().toUpper()) ;
  ui->txtTypeCode->setText(newTypeCode);
  typeCodeChanged(newTypeCode);
}

void FormDeviserClass::defaultListOfName()
{
  if (ui->txtName->text().isEmpty()) return;
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
  if (ui->txtName->text().isEmpty()) return;
  QString newListOfClassName = Util::upperFirst( QString("listOf%1")
                                                 .arg(Util::upperFirst(Util::guessPlural(ui->txtName->text()))));
  ui->txtListOfClassName->setText(newListOfClassName);
  listOfClassNameChanged(newListOfClassName);

}
