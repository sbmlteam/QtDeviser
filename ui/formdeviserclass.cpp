#include "formdeviserclass.h"
#include "ui_formdeviserclass.h"

#include <QFileDialog>
#include <QTableWidgetItem>
#include <QSortFilterProxyModel>

#include <model/deviserclass.h>
#include <model/deviserattribute.h>
#include <model/deviserlistofattribute.h>
#include <model/deviserconcrete.h>

#include <ui/attributesmodel.h>

FormDeviserClass::FormDeviserClass(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormDeviserClass)
    , mElement(NULL)
    , mpAttributes(NULL)
    , mpAttributesFilter(NULL)
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

    while(ui->tblAttributes->rowCount() > 0)
        ui->tblAttributes->removeRow(0);

    while(ui->tblLoAttributes->rowCount() > 0)
        ui->tblLoAttributes->removeRow(0);

    while(ui->tblInstantiations->rowCount() > 0)
        ui->tblInstantiations->removeRow(0);

    if (mElement != NULL)
    {
        ui->txtName->setText(element->getName());
        ui->txtBaseClass->setText(element->getBaseClass());
        ui->txtTypeCode->setText(element->getTypeCode());
        ui->txtXMLElementName->setText(element->getElementName());

        ui->chkHasListOf->setChecked(
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
        ui->txtMinNumChildren->setText(QString::number(element->getMinNumberChildren()));
        ui->txtMaxNumChildren->setText(QString::number(element->getMaxNumberChildren()));

        ui->txtDeclaration->setText(element->getAdditionalDeclarations());
        ui->txtImplementation->setText(element->getAdditionalDefinitions());
        ui->chkRequiresAdditionalCode->setChecked(!element->getAdditionalDeclarations().isEmpty() || !element->getAdditionalDefinitions().isEmpty());
        ui->grpAdditional->setVisible(ui->chkRequiresAdditionalCode->isChecked());

        ui->chkIsBaseClass->setChecked(element->isBaseClass() || !element->getConcretes().empty() );

        mpAttributesFilter = new QSortFilterProxyModel(this);
        mpAttributes = new AttributesModel(this, element->getAttributes());
        mpAttributesFilter->setSourceModel(mpAttributes);
        ui->tblAttributes->setModel(mpAttributesFilter);

//        foreach(auto* attrib, element->getAttributes())
//        {
//            int index = ui->tblAttributes->rowCount();
//            ui->tblAttributes->insertRow(index);
//            ui->tblAttributes->setItem(index, 0, new QTableWidgetItem(attrib->getName()));
//            ui->tblAttributes->setItem(index, 1, new QTableWidgetItem(attrib->getType()));
//            ui->tblAttributes->setItem(index, 2, new QTableWidgetItem(attrib->getElement()));
//            //ui->tblAttributes->setCellWidget(index, 3, new QCheckBox());
//            auto* tempItem = new QTableWidgetItem(attrib->getRequired());
//            tempItem->setCheckState(attrib->getRequired() ? Qt::Checked : Qt::Unchecked);
//            ui->tblAttributes->setItem(index, 3, tempItem);
//            tempItem = new QTableWidgetItem(attrib->getAbstract());
//                        tempItem->setCheckState(attrib->getAbstract() ? Qt::Checked : Qt::Unchecked);
//            //ui->tblAttributes->setCellWidget(index, 4, new QCheckBox);

//            ui->tblAttributes->setItem(index, 4, tempItem);
//            ui->tblAttributes->setItem(index, 5, new QTableWidgetItem(attrib->getXMLName()));
//        }

        foreach(auto* attrib, element->getListOfAttributes())
        {
            int index = ui->tblLoAttributes->rowCount();
            ui->tblLoAttributes->insertRow(index);
            ui->tblLoAttributes->setItem(index, 0, new QTableWidgetItem(attrib->getName()));
            ui->tblLoAttributes->setItem(index, 1, new QTableWidgetItem(attrib->getType()));
            ui->tblLoAttributes->setItem(index, 2, new QTableWidgetItem(attrib->getElement()));
            auto* tempItem = new QTableWidgetItem(attrib->getRequired());
            tempItem->setCheckState(attrib->getRequired() ? Qt::Checked : Qt::Unchecked);
            ui->tblLoAttributes->setItem(index, 3, tempItem);

            //ui->tblLoAttributes->setCellWidget(index, 3, new QCheckBox);
            //ui->tblLoAttributes->setItem(index, 3, new QTableWidgetItem(attrib->getRequired()));

            tempItem = new QTableWidgetItem(attrib->getAbstract());
                        tempItem->setCheckState(attrib->getAbstract() ? Qt::Checked : Qt::Unchecked);
            ui->tblLoAttributes->setItem(index, 4, tempItem);
            //ui->tblLoAttributes->setCellWidget(index, 4, new QCheckBox);
            ui->tblLoAttributes->setItem(index, 4, new QTableWidgetItem(attrib->getAbstract()));
            ui->tblLoAttributes->setItem(index, 5, new QTableWidgetItem(attrib->getXMLName()));
        }

        foreach(auto* concrete, element->getConcretes())
        {
            int index = ui->tblInstantiations->rowCount();
            ui->tblInstantiations->insertRow(index);
            ui->tblInstantiations->setItem(index, 0, new QTableWidgetItem(concrete->getName()));
            ui->tblInstantiations->setItem(index, 1, new QTableWidgetItem(concrete->getElement()));
            ui->tblInstantiations->setItem(index, 2, new QTableWidgetItem(concrete->getMinNumChildren()));
            ui->tblInstantiations->setItem(index, 3, new QTableWidgetItem(concrete->getMaxNumChildren()));
        }

    }    
}

void
FormDeviserClass::concreteChanged(QTableWidgetItem*)
{

}

void
FormDeviserClass::listOfAttributeChanged(QTableWidgetItem*)
{

}

void
FormDeviserClass::attributeChanged(QTableWidgetItem*)
{

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

}

void
FormDeviserClass::delListOfAttribute()
{

}

void
FormDeviserClass::delAttribute()
{

}

void
FormDeviserClass::addListOfAttribute()
{
  if (mElement == NULL) return;

  DeviserListOfAttribute * attrib = mElement->createListOfAttribute();

int index = ui->tblLoAttributes->rowCount();
ui->tblLoAttributes->insertRow(index);

ui->tblLoAttributes->setItem(index, 0, new QTableWidgetItem(attrib->getName()));
ui->tblLoAttributes->setItem(index, 1, new QTableWidgetItem(attrib->getType()));
ui->tblLoAttributes->setItem(index, 2, new QTableWidgetItem(attrib->getElement()));

auto* tempItem = new QTableWidgetItem(attrib->getRequired());
tempItem->setCheckState(attrib->getRequired() ? Qt::Checked : Qt::Unchecked);
ui->tblLoAttributes->setItem(index, 3, tempItem);
tempItem = new QTableWidgetItem(attrib->getAbstract());
            tempItem->setCheckState(attrib->getAbstract() ? Qt::Checked : Qt::Unchecked);

ui->tblLoAttributes->setItem(index, 4, tempItem);
ui->tblLoAttributes->setItem(index, 5, new QTableWidgetItem(attrib->getXMLName()));


ui->tblLoAttributes->setFocus();
ui->tblLoAttributes->setCurrentCell(index, 0);
}

void
FormDeviserClass::addConcrete()
{
  if (mElement == NULL) return;

  DeviserConcrete * concrete = mElement->createConcrete();
  int index = ui->tblInstantiations->rowCount();
  ui->tblInstantiations->insertRow(index);
  ui->tblInstantiations->setItem(index, 0, new QTableWidgetItem(concrete->getName()));
  ui->tblInstantiations->setItem(index, 1, new QTableWidgetItem(concrete->getElement()));
  ui->tblInstantiations->setItem(index, 2, new QTableWidgetItem(concrete->getMinNumChildren()));
  ui->tblInstantiations->setItem(index, 3, new QTableWidgetItem(concrete->getMaxNumChildren()));

ui->tblInstantiations->setFocus();
ui->tblInstantiations->setCurrentCell(index, 0);
}

void
FormDeviserClass::addAttribute()
{
    if (mElement == NULL) return;

    DeviserAttribute * attrib = mElement->createAttribute();

  int index = ui->tblAttributes->rowCount();
  ui->tblAttributes->insertRow(index);

  ui->tblAttributes->setItem(index, 0, new QTableWidgetItem(attrib->getName()));
  ui->tblAttributes->setItem(index, 1, new QTableWidgetItem(attrib->getType()));
  ui->tblAttributes->setItem(index, 2, new QTableWidgetItem(attrib->getElement()));

  auto* tempItem = new QTableWidgetItem(attrib->getRequired());
  tempItem->setCheckState(attrib->getRequired() ? Qt::Checked : Qt::Unchecked);
  ui->tblAttributes->setItem(index, 3, tempItem);
  tempItem = new QTableWidgetItem(attrib->getAbstract());
              tempItem->setCheckState(attrib->getAbstract() ? Qt::Checked : Qt::Unchecked);

  ui->tblAttributes->setItem(index, 4, tempItem);
  ui->tblAttributes->setItem(index, 5, new QTableWidgetItem(attrib->getXMLName()));


  ui->tblAttributes->setFocus();
  ui->tblAttributes->setCurrentCell(index, 0);
}

void
FormDeviserClass::xmlElementNameChanged(const QString&)
{
  if (mElement == NULL) return;
  mElement->setElementName(ui->txtXMLElementName->text());
}

void
FormDeviserClass::typeCodeChanged(const QString&)
{
    if (mElement == NULL) return;
    mElement->setTypeCode(ui->txtTypeCode->text());

}

void
FormDeviserClass::nameChanged(const QString&)
{
    if (mElement == NULL) return;
    mElement->setName(ui->txtName->text());

}

void
FormDeviserClass::minNoChildrenChanged(const QString&)
{
    if (mElement == NULL) return;
    mElement->setMinNumberChildren(ui->txtMinNumChildren->text().toInt());

}

void
FormDeviserClass::maxNoChildrenChanged(const QString&)
{
    if (mElement == NULL) return;
    mElement->setMaxNumberChildren(ui->txtMaxNumChildren->text().toInt());

}

void
FormDeviserClass::listOfNameChanged(const QString&)
{
    if (mElement == NULL) return;
    mElement->setListOfName(ui->txtListOfName->text());

}

void
FormDeviserClass::listOfClassNameChanged(const QString&)
{
    if (mElement == NULL) return;
    mElement->setListOfClassName(ui->txtListOfClassName->text());

}

void
FormDeviserClass::definitionChanged(const QString&)
{
    if (mElement == NULL) return;
    mElement->setAdditionalDefinitions(ui->txtImplementation->text());

}

void
FormDeviserClass::declarationChanged(const QString&)
{
    if (mElement == NULL) return;
    mElement->setAdditionalDeclarations(ui->txtDeclaration->text());

}

void
FormDeviserClass::baseClassChanged(const QString&)
{
    if (mElement == NULL) return;
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
    ui->grpInstantiations->setVisible(ui->chkIsBaseClass->isChecked());
}

void
FormDeviserClass::hasListOfStateChanged(int)
{
    ui->ctrlListOf->setVisible(ui->chkHasListOf->isChecked());
    ui->grpListOfAttributes->setVisible(ui->chkHasListOf->isChecked());

}
