//
// Created by Robson on 09/01/2023.
//
#pragma once

#include <MitoR/MitoR.hpp>
#include <QStyledItemDelegate>
#include <functional>

namespace MitoR::Gui
{
  class EXP_IMP_DECL CallbackPaintDelegate : public QStyledItemDelegate
  {
    CS_OBJECT(CallbackPaintDelegate)
  public:
    using PaintCallback = std::function<void (QPainter *painter, QStyleOptionViewItem &option, const QModelIndex &index)>;
    
    explicit CallbackPaintDelegate(PaintCallback paintFunc = nullptr, QObject *parent = nullptr);
    ~CallbackPaintDelegate() override;

    CS_SIGNAL_1(Public, void itemEditado(const QModelIndex &index))
    CS_SIGNAL_2(itemEditado, index)
    
  protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    
  private:
    PaintCallback m_paintFunc;
  };
}