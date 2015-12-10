#include "typechooserdelegate.h"

#include <QComboBox>

#include <util.h>

TypeChooserDelegate::TypeChooserDelegate(QObject *parent)
  : QStyledItemDelegate(parent)
  , mTypes(Util::getKnownTypes())
{

}

TypeChooserDelegate::~TypeChooserDelegate()
{

}

QWidget *
TypeChooserDelegate::createEditor(QWidget *parent,
                                  const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
{
  // ComboBox ony in column 2
  if (index.column() != 1)
    return QStyledItemDelegate::createEditor(parent, option, index);

  // Create the combobox and populate it
  QComboBox* cb = new QComboBox(parent);
  foreach(QString str, mTypes)
    cb->addItem(str);
  foreach(QString str, Util::getUserDefinedTypes())
    cb->addItem(str);
  return cb;
}

void
TypeChooserDelegate::setEditorData(QWidget *editor,
                                   const QModelIndex &index) const
{
  if (QComboBox* cb = qobject_cast<QComboBox*>(editor))
  {
    QString currentText = index.data(Qt::EditRole).toString();
    int cbIndex = cb->findText(currentText);
    if (cbIndex >= 0)
      cb->setCurrentIndex(cbIndex);
  }
  else
  {
    QStyledItemDelegate::setEditorData(editor, index);
  }
}

void
TypeChooserDelegate::setModelData(QWidget *editor,
                                  QAbstractItemModel *model,
                                  const QModelIndex &index) const
{
  if (QComboBox* cb = qobject_cast<QComboBox*>(editor))
  {
      model->setData(index, cb->currentText(), Qt::EditRole);
  }
  else
  {
      QStyledItemDelegate::setModelData(editor, model, index);
  }
}

