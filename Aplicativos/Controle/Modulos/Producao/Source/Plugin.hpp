//
// Created by Robson on 14/05/2023.
//
#pragma once

#include <MitoR/MitoR.hpp>
#include <MitoR/Modulo.hpp>
#include <MitoR/IPlugin.hpp>
#include <MitoR/IServico.hpp>
#include <Sessao/IAcesso.hpp>
#include <QAction>

namespace Producao
{
  class Plugin : public QObject,
                 public MitoR::IPlugin,
                 public MitoR::IServico
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

    // Servico interface
  public:
    QSharedPointer<QObject> servico(const QString &IDS) override;
    bool temServico(const QString &IDS) const override;

    CS_SLOT_1(Public, void verificarSeguranca())
    CS_SLOT_2(verificarSeguranca)

  private:
    Sessao::IAcesso *_acesso{nullptr};
    QAction *actionFormCadastrarTiposPropostas{nullptr};
    QAction *actionFormOrcamento{nullptr};
  };
}