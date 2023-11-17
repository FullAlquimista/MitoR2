//
// Created by Robson on 15/01/2023.
//
#pragma once

#include <Sessao/IAcesso.hpp>
#include <QtCore>
#include <QtGui>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui
{
  class FormCadastrarMateriais;
}
QT_END_NAMESPACE

class FormCadastrarMateriais : public QWidget
{
  CS_OBJECT(FormCadastrarMateriais)

public:
  enum Roles
  {
    NovoItem = Qt::UserRole + 10,
    ItemEditado,
    RemoverItem,
    ItemEdicao
  };
  
  explicit FormCadastrarMateriais(QWidget *parent = nullptr);
  ~FormCadastrarMateriais() override;
  
  void novoFormulario();
  void pesquisarFormulario();
  void salvarFormulario();
  bool limparFormulario();
  void removerFormulario();
  
  void adicionar();
  void gravar();
  void excluir();

private:
  Ui::FormCadastrarMateriais *ui;
  Sessao::IAcesso *_acesso{nullptr};
  QWidget *m_wPesquisa{nullptr};
  
  QSqlRelationalTableModel *m_tMateriais{nullptr};
  QModelIndex m_idxMaterial;
  QMap<Roles, QVariant> m_rolesIdxMaterial;
  QSqlTableModel *m_tClassificacoes{nullptr};
  QModelIndex m_idxClassificacao;
  QSqlTableModel *m_tPlanoConta{nullptr};
  QModelIndex m_idxPlanoConta;
  QSqlRelationalTableModel *m_tFracionaveis{nullptr};
  QModelIndex m_idxFracionavel;
  
  void carregarTabelas();
  void mudarIndexClassificacao(QModelIndex idx);
  void mudarIndexPlanoConta(QModelIndex idx);
  void procurarIdClassificacao(int id);
  void procurarIdPlanoConta(int id);
  void mudarIndexMaterial(QModelIndex idx);
  void procurarIdMaterial(int id);
  void inserirRoleIdxMaterial(const bool v, const Roles role);
  bool obterRoleIdxMaterial(const Roles role);
  void selecionarIdClassificacao();
};

