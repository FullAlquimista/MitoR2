//
// Created by Robson on 08/06/2023.
//
#pragma once

#include <MitoR/MitoR.hpp>
#include <Controle/IControle.hpp>

namespace Sessao
{
  const QString Sessao_ID = "/Sessao";
  const QString DialogSessao_ID = Sessao_ID + "/DialogSessao";
  const QString SubMenuSessao_ID = Sessao_ID + "/Sessao";
  const QString ActionAcessar_ID = SubMenuSessao_ID + "/ActionAcessar";
  const QString MenuGerenciar_ID = Sessao_ID + "/MenuGerenciar";
  const QString ActionGerenciarUsuarios_ID = MenuGerenciar_ID + "/ActionGerenciarUsuarios";
  const QString FormGerenciarUsuarios_ID = Sessao_ID + "/FormGerenciarUsuarios";
}