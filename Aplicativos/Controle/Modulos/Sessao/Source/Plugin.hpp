//
// Created by Robson on 14/05/2023.
//
#pragma once

#include <MitoR/MitoR.hpp>
#include <MitoR/Modulo.hpp>
#include <MitoR/IPlugin.hpp>
#include <MitoR/IServico.hpp>
#include "acesso.hpp"

namespace Sessao
{
  class Plugin : public QObject,
                 public MitoR::IPlugin
  {
    CS_OBJECT(Plugin)
    CS_PLUGIN_IID(ID_PLUGIN)

    CS_INTERFACES(Plugin)

  public:
    explicit Plugin(QObject *parent = nullptr);

    // Plugin interface
  public:
    bool construir() override;

    bool destruir() override;

  private:
    Sessao::IAcesso *_acesso{nullptr};
  };
}