#ifndef TYPECHOOSERDELEGATE_H
#define TYPECHOOSERDELEGATE_H

#include <QStyledItemDelegate>

#include <QStringList>

class TypeChooserDelegate : public QStyledItemDelegate
{
  Q_OBJECT

public:

  TypeChooserDelegate(QObject* parent = NULL);

  virtual ~TypeChooserDelegate();

  virtual QWidget* createEditor(QWidget* parent,
                                const QStyleOptionViewItem& option,
                                const QModelIndex& index) const;

  virtual void setEditorData(QWidget* editor,
                             const QModelIndex& index) const;

  virtual void setModelData(QWidget* editor,
                            QAbstractItemModel* model,
                            const QModelIndex& index) const;
protected:

  QStringList mTypes;
};

#endif // TYPECHOOSERDELEGATE_H
