//
// Created by Robson on 09/01/2023.
//

#include <MitoR/Gui/callbackpaintdelegate.hpp>
#include <QtGui>

MitoR::Gui::CallbackPaintDelegate::CallbackPaintDelegate(MitoR::Gui::CallbackPaintDelegate::PaintCallback paintFunc, QObject *parent)
    : QStyledItemDelegate(parent), m_paintFunc(paintFunc)
{
}
MitoR::Gui::CallbackPaintDelegate::~CallbackPaintDelegate()
{
}
void MitoR::Gui::CallbackPaintDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  auto opt = option;
  initStyleOption(&opt, index);
  
  if(m_paintFunc)
    m_paintFunc(painter, opt, index);
  
  QStyledItemDelegate::paint(painter, opt, index);
}
void MitoR::Gui::CallbackPaintDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  auto data = index.data();
  QStyledItemDelegate::setModelData(editor, model, index);
  auto modifiedData = index.data();
  if (data.toString() != modifiedData.toString()) {
    const_cast<CallbackPaintDelegate *>(this)->itemEditado(index);
  }
}
