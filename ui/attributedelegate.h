#ifndef ATTRIBUTE_DELEGATE_H
#define ATTRIBUTE_DELEGATE_H


#include <QItemDelegate>
#include <QStringList>

class AttributeDelegate : public QItemDelegate
{
public:
  AttributeDelegate(QObject* parent = NULL);

  virtual ~AttributeDelegate();

  virtual QWidget* createEditor(QWidget* parent,
                                const QStyleOptionViewItem& option,
                                const QModelIndex& index) const;

  virtual void setEditorData(QWidget* editor,
                             const QModelIndex& index) const;

  virtual void setModelData(QWidget* editor,
                            QAbstractItemModel* model,
                            const QModelIndex& index) const;

  virtual void paint(QPainter *painter,
                     const QStyleOptionViewItem &option, const QModelIndex &index) const;


protected:

  QStringList mTypes;
};

#endif // ATTRIBUTE_DELEGATE_H
