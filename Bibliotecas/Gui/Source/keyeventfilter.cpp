//
// Created by Robson on 13/01/2023.
//

#include "mitor/gui/keyeventfilter.hpp"
#include <QKeyEvent>

MitoR::Gui::CallbackEventFilter::CallbackEventFilter(std::function<bool(QObject *, QEvent *)> predicado, QObject *parent)
  : QObject(parent), m_predicado(predicado)
{
}
bool MitoR::Gui::CallbackEventFilter::eventFilter(QObject *obj, QEvent *evento)
{
  return m_predicado(obj, evento);
}
