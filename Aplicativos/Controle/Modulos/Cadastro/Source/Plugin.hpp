//
// Created by Robson on 14/05/2023.
//
#pragma once

#include <MitoR/MitoR.hpp>
#include <MitoR/Modulo.hpp>
#include <MitoR/IPlugin.hpp>
#include <Sessao/IAcesso.hpp>
#include <QAction>

namespace Cadastro
{
  class Plugin : public QObject,
                 public MitoR::IPlugin
  {
    CS_OBJECT(Plugin)
    CS_PLUGIN_IID(ID_PLUGIN)

    CS_INTERFACES(Plugin)

  public:
    explicit Plugin(QObject *parent = nullptr);

    CS_SLOT_1(Public, void verificarSeguranca())
    CS_SLOT_2(verificarSeguranca)

    // Plugin interface
  public:
    bool construir() override;

    bool destruir() override;

  private:
    Sessao::IAcesso *_acesso{nullptr};
    QAction *actionCadastrarEmpresa{nullptr};
    QAction *actionCadastrarPlanoConta{nullptr};
    QAction *actionCadastrarUnidadesMedidas{nullptr};
    QAction *actionCadastrarClassificacoesMateriais{nullptr};
    QAction *actionCadastrarFormatoMateriais{nullptr};
    QAction *actionCadastrarTiposMateriais{nullptr};
    QAction *actionCadastrarMateriais{nullptr};
  };
}