#include "formdeviserplugin.h"
#include "ui_formdeviserplugin.h"

#include <model/deviserplugin.h>
#include <model/deviserclass.h>
#include <model/deviserversion.h>
#include <model/deviserattribute.h>

FormDeviserPlugin::FormDeviserPlugin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDeviserPlugin)
{
    ui->setupUi(this);
}

FormDeviserPlugin::~FormDeviserPlugin()
{
    delete ui;
}


void
FormDeviserPlugin::initializeFrom(DeviserPlugin* plugin)
{
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

    while(ui->tblAttributes->rowCount() > 0)
        ui->tblAttributes->removeRow(0);

    ui->lstChildClasses->clear();
    ui->lstDefinedClasses->clear();

    if (mPlugin != NULL)
    {
        ui->txtExtensionPoint->setText(plugin->getExtensionPoint());

        ui->chkElementFromCore->setChecked(plugin->getPackage().isEmpty() && plugin->getTypeCode().isEmpty());
        ui->txtPackage->setText(plugin->getPackage());
        ui->txtPackage->setText(plugin->getTypeCode());

        ui->chkHasAttributes->setChecked(!plugin->getAttributes().empty());
        ui->grpAttributes->setVisible(!plugin->getAttributes().empty());
        foreach(auto* attribute, plugin->getAttributes())
        {
            int rowIndex  = ui->tblAttributes->rowCount();
            ui->tblAttributes->insertRow(rowIndex);

            ui->tblAttributes->setItem(rowIndex, 0, new QTableWidgetItem(attribute->getName()));
            ui->tblAttributes->setItem(rowIndex, 1, new QTableWidgetItem(attribute->getType()));
            ui->tblAttributes->setItem(rowIndex, 2, new QTableWidgetItem(attribute->getElement()));
            auto* tempItem = new QTableWidgetItem(attribute->getRequired());
            tempItem->setCheckState(attribute->getRequired() ? Qt::Checked : Qt::Unchecked);
            ui->tblAttributes->setItem(rowIndex, 3, tempItem);
            //ui->tblAttributes->setItem(rowIndex, 3, new QTableWidgetItem(attribute->getRequired()));
            tempItem = new QTableWidgetItem(attribute->getAbstract());
            tempItem->setCheckState(attribute->getAbstract() ? Qt::Checked : Qt::Unchecked);
            ui->tblAttributes->setItem(rowIndex, 4, tempItem);
            //ui->tblAttributes->setItem(rowIndex, 4, new QTableWidgetItem(attribute->getAbstract()));
            ui->tblAttributes->setItem(rowIndex, 5, new QTableWidgetItem(attribute->getXMLName()));

        }

        ui->txtDeclaration->setText(plugin->getAdditionalDeclarations());
        ui->txtImplementation->setText(plugin->getAdditionalDefinitions());
        ui->chkRequiresAdditionalCode->setChecked(!plugin->getAdditionalDefinitions().isEmpty() ||
                                                  !plugin->getAdditionalDeclarations().isEmpty());
        ui->grpAdditional->setVisible(ui->chkRequiresAdditionalCode->isChecked());

        foreach(auto* element, plugin->getParentVersion()->getElements())
        {
            ui->lstDefinedClasses->addItem(element->getName());
        }

        foreach(auto* element, plugin->getReferences())
            ui->lstChildClasses->addItem(element->getName());



    }


}
