//
// Created by Robson on 04/03/2023.
//
#pragma once
#include <QStyledItemDelegate>

namespace MitoR::Gui
{
  class RelationalIdDelegate : public QStyledItemDelegate
  {
    CS_OBJECT(RelationalIdDelegate)
  public:
    explicit RelationalIdDelegate(QObject *parent = nullptr);
    ~RelationalIdDelegate() override;
    
    // Métodos virtuais a serem reimplementados
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    
  };
}
