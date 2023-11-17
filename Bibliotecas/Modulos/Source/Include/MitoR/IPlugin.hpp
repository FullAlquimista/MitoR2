//
// Created by Robson on 14/05/2023.
//
#pragma once

#include <MitoR/MitoR.hpp>

namespace MitoR
{
  /**
 * @brief The IPlugin class é utilizado no carregamento do módulo utilizado pelo
 * componente QPluginLoader.
 * É utilizado na construção do módulo.
 */
  class IPlugin
  {
  public:
    [[nodiscard]] virtual bool construir() = 0;

    [[nodiscard]] virtual bool destruir() = 0;
  };

} // namespace MitoR

#define ID_PLUGIN "37c8c546-4285-4ca1-b836-72263cad97ca"
CS_DECLARE_INTERFACE(MitoR::IPlugin, ID_PLUGIN)