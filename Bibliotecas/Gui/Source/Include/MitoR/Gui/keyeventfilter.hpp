//
// Created by Robson on 13/01/2023.
//
#pragma once
#include <MitoR/MitoR.hpp>
#include <QObject>
#include <functional>

namespace MitoR::Gui
{
  class EXP_IMP_DECL CallbackEventFilter : public QObject
  {
    CS_OBJECT(CallbackEventFilter)
  public:
    
    explicit CallbackEventFilter(std::function<bool(QObject *, QEvent *)> predicado, QObject *parent = nullptr);

  protected:
    bool eventFilter(QObject *obj, QEvent *evento) override;
    
  private:
    std::function<bool(QObject *, QEvent *)> m_predicado;
  };
}

