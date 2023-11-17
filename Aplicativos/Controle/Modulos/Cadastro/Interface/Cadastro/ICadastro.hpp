//
// Created by Robson on 11/06/2023.
//
#pragma once

#include <MitoR/MitoR.hpp>

namespace Cadastro
{
  const QString Cadastro_ID = "/Cadastro";
  const QString MenuCadastro_ID = Cadastro_ID + "/MenuCadastrar";
  const QString SubMenuInfoCadastro_ID = MenuCadastro_ID + "/SubMenuInfoCadastro";
  const QString ActionCadastrarEmpresa_ID = SubMenuInfoCadastro_ID + "/ActionCadastrarEmpresa";
  const QString FormCadastrarEmpresa_ID = Cadastro_ID + "/FormCadastrarEmpresa";
  const QString ActionCadastrarPlanoConta_ID = SubMenuInfoCadastro_ID + "/ActionCadastrarPlanoConta";
  const QString FormCadastrarPlanoConta_ID = Cadastro_ID + "/FormCadastrarPlanoConta";
  const QString ActionCadastrarUnidadesMedidas_ID = SubMenuInfoCadastro_ID + "/ActionCadastrarUnidadesMedidas";
  const QString FormCadastrarUnidadesMedidas_ID = Cadastro_ID + "/FormCadastrarUnidadesMedidas";
  const QString ActionCadastrarClassificacoesMateriais_ID = SubMenuInfoCadastro_ID + "/ActionCadastrarClassificacoesMateriais";
  const QString FormCadastrarClassificacoesMateriais_ID = Cadastro_ID + "/FormCadastrarClassificacoesMateriais";
  const QString ActionCadastrarFormatoMateriais_ID = SubMenuInfoCadastro_ID + "/ActionCadastrarFormatoMateriais";
  const QString FormCadastrarFormatoMateriais_ID = Cadastro_ID + "/FormCadastrarFormatoMateriais";
  const QString ActionCadastrarTiposMateriais_ID = SubMenuInfoCadastro_ID + "/ActionCadastrarTiposMateriais";
  const QString FormCadastrarTiposMateriais_ID = Cadastro_ID + "/FormCadastrarTiposMateriais";
  const QString ActionCadastrarMateriais_ID = SubMenuInfoCadastro_ID + "/ActionCadastrarMateriais";
  const QString FormCadastrarMateriais_ID = Cadastro_ID + "/FormCadastrarMateriais";
}