#include "attributedelegate.h"
#include "attributesmodel.h"
#include "util.h"

#include <QCheckBox>
#include <QComboBox>


AttributeDelegate::AttributeDelegate(QObject* parent /*= NULL*/)
  : QItemDelegate(parent)
  , mTypes(Util::getKnownTypes())
{

}


AttributeDelegate::~AttributeDelegate()
{

}

QWidget *
AttributeDelegate::createEditor(QWidget *parent,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index) const
{
  switch (index.column())
  {
    case AttributesModel::TYPE:
    {
      // Create the combobox and populate it
      QComboBox* cb = new QComboBox(parent);
      foreach(QString str, mTypes)
        cb->addItem(str);
      foreach(QString str, Util::getUserDefinedTypes())
        cb->addItem(str);
      return cb;
    }

    case AttributesModel::REQUIRED:
    {
      QCheckBox* cb = new QCheckBox(parent);
      cb->setStyleSheet("QCheckBox {margin-left: 43%; margin-right: 57%;}");
      return cb;
    }

    case AttributesModel::ABSTRACT:
    {
      QCheckBox* cb = new QCheckBox(parent);
      cb->setStyleSheet("QCheckBox {margin-left: 43%; margin-right: 57%;}");
      return cb;
    }

    default:
      return QItemDelegate::createEditor(parent, option, index);
    }
}

void
AttributeDelegate::setEditorData(QWidget *editor,
                                const QModelIndex &index) const
{
  switch (index.column())
  {

    case AttributesModel::TYPE:
    {
      QComboBox* cb = qobject_cast<QComboBox*>(editor);

      QString currentText = index.data(Qt::EditRole).toString();
      int cbIndex = cb->findText(currentText);
      if (cbIndex >= 0)
        cb->setCurrentIndex(cbIndex);
      break;
    }

    case AttributesModel::REQUIRED:
    {
      QCheckBox* cb = qobject_cast<QCheckBox*>(editor);
      cb->setChecked(index.data(Qt::EditRole).toBool());
      break;
    }

    case AttributesModel::ABSTRACT:
    {
      QCheckBox* cb = qobject_cast<QCheckBox*>(editor);
      cb->setChecked(index.data(Qt::EditRole).toBool());
      break;
    }

    default:
      QItemDelegate::setEditorData(editor, index);
      break;

  }

}

void
AttributeDelegate::setModelData(QWidget *editor,
                               QAbstractItemModel *model,
                               const QModelIndex &index) const
{
  switch (index.column())
  {

    case AttributesModel::TYPE:
    {
      QComboBox* cb = qobject_cast<QComboBox*>(editor);
      model->setData(index, cb->currentText(), Qt::EditRole);
      break;
    }

    case AttributesModel::REQUIRED:
    {
      QCheckBox* cb = qobject_cast<QCheckBox*>(editor);
      model->setData(index, cb->isChecked(), Qt::EditRole);
      break;
    }

    case AttributesModel::ABSTRACT:
    {
      QCheckBox* cb = qobject_cast<QCheckBox*>(editor);
      model->setData(index, cb->isChecked(), Qt::EditRole);
      break;
    }

    default:
      QItemDelegate::setModelData(editor, model, index);
      break;

  }

}

void
AttributeDelegate::paint(QPainter *painter,
                        const QStyleOptionViewItem &option,
                        const QModelIndex &index) const
{
  switch (index.column())
  {

    case AttributesModel::REQUIRED:
    {
      bool enabled = index.data().toBool();

      drawCheck(painter, option, option.rect, enabled ? Qt::Checked : Qt::Unchecked);
      drawFocus(painter, option, option.rect);
      return;
    }

    case AttributesModel::ABSTRACT:
    {
      QModelIndex typeIndex = index.model()->index(index.row(), AttributesModel::TYPE);
      QString type = typeIndex.data().toString();

      if (type == "element" || type == "inline_lo_element" || type == "lo_element")
      {
        bool enabled = index.data().toBool();
        drawCheck(painter, option, option.rect, enabled ? Qt::Checked : Qt::Unchecked);
        drawFocus(painter, option, option.rect);
      }
      return;
    }

    default:
    case AttributesModel::TYPE:
  {
      QItemDelegate::paint(painter, option, index);
      return;
  }

  }

}
