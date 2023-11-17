//
// Created by Robson on 14/05/2023.
//

#include "Plugin.hpp"
CS_PLUGIN_REGISTER(ModuloAB::Plugin)

namespace ModuloAB
{
  Plugin::Plugin(QObject *parent) : QObject(parent)
  {

  }
  bool Plugin::construir()
  {
    return true;
  }
  bool Plugin::destruir()
  {
    return true;
  }
  QSharedPointer<QObject> Plugin::servico(const QString &)
  {
    return QSharedPointer<QObject>();
  }
  bool Plugin::temServico(const QString &) const
  {
    return false;
  }
} // namespace Sessao