//
// Created by Robson on 11/06/2023.
//
#pragma once

#include <MitoR/MitoR.hpp>
#include <Cadastro/ICadastro.hpp>

namespace Producao
{
  const QString Producao_ID = "/Producao";
  const QString MenuProducao = Producao_ID + "/MenuProducao";
  const QString SubMenuInfoProducao_ID = Cadastro::MenuCadastro_ID + "/SubMenuInfoProducao";
  const QString ActionCadastrarTiposPropostas_ID = SubMenuInfoProducao_ID + "/ActionCadastrarTiposPropostas";
  const QString FormCadastrarTiposPropostas_ID = SubMenuInfoProducao_ID + "/FormCadastrarTiposPropostas";
  const QString ActionOrcamento_ID = SubMenuInfoProducao_ID + "/ActionOrcamento";
  const QString FormOrcamento_ID = Producao_ID + "/FormOrcamento";

  const QString R_ImagenOrcamento_ID = Producao_ID + "/Imagens/Orcamento";
  const QString R_Anexo_ID = Producao_ID + "/Anexo/NomeArquivo";
}