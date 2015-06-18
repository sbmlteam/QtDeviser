#include "formdeviserclass.h"
#include "ui_formdeviserclass.h"

#include <model/deviserclass.h>
#include <model/deviserattribute.h>
#include <model/deviserlistofattribute.h>
#include <model/deviserconcrete.h>

FormDeviserClass::FormDeviserClass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDeviserClass),
    mElement(NULL)
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

        ui->chkIsBaseClass->setChecked(element->getIsBaseClass() || !element->getConcretes().empty() );

        foreach(auto* attrib, element->getAttributes())
        {
            int index = ui->tblAttributes->rowCount();
            ui->tblAttributes->insertRow(index);
            ui->tblAttributes->setItem(index, 0, new QTableWidgetItem(attrib->getName()));
            ui->tblAttributes->setItem(index, 1, new QTableWidgetItem(attrib->getType()));
            ui->tblAttributes->setItem(index, 2, new QTableWidgetItem(attrib->getElement()));
            //ui->tblAttributes->setCellWidget(index, 3, new QCheckBox());
            auto* tempItem = new QTableWidgetItem(attrib->getRequired());
            tempItem->setCheckState(attrib->getRequired() ? Qt::Checked : Qt::Unchecked);
            ui->tblAttributes->setItem(index, 3, tempItem);
            tempItem = new QTableWidgetItem(attrib->getAbstract());
                        tempItem->setCheckState(attrib->getAbstract() ? Qt::Checked : Qt::Unchecked);
            //ui->tblAttributes->setCellWidget(index, 4, new QCheckBox);

            ui->tblAttributes->setItem(index, 4, tempItem);
            ui->tblAttributes->setItem(index, 5, new QTableWidgetItem(attrib->getXMLName()));
        }

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
