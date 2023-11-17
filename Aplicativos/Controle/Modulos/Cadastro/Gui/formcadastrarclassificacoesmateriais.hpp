//
// Created by Robson on 01/01/2023.
//
#pragma once
#include <Sessao/IAcesso.hpp>
#include <QtCore>
#include <QtGui>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui
{
  class FormCadastrarClassificacoesMateriais;
}
QT_END_NAMESPACE

class FormCadastrarClassificacoesMateriais : public QWidget
{
  CS_OBJECT(FormCadastrarClassificacoesMateriais)

public:
  enum Roles {
    CT_ID = Qt::UserRole + 1,
    CT_Item_ID,
    CT_No_ID,
    CT_Nivel,
    C_ID,
    C_Descricao,
    C_Nomear,
    Adicionar,
    Atualizar,
    Remover
  };
  using Erro = MitoR::Erro;
  
  explicit FormCadastrarClassificacoesMateriais(QWidget *parent = nullptr);
  ~FormCadastrarClassificacoesMateriais() override;
  
  void novo();
  void salvar();
  void remover();

private:
  Ui::FormCadastrarClassificacoesMateriais *ui;
  Sessao::IAcesso *_acesso{nullptr};
  
  QStandardItemModel *m_model{nullptr};
  
  void carregarModelo();
  bool consultarClassificacoes(QSqlQuery &consulta);
  void preencherPapeisItem(const QSqlRecord &reg, QStandardItem *item);
  Erro adicionarItemTabela(QStandardItem *novoItem, QSqlQuery &consulta);
  void adicionarPapeisNovoItem(const QSqlRecord &reg, QStandardItem *novoItem);
  Erro removerItemTabela(QStandardItem *item, QSqlQuery &consulta);
  
  CS_SLOT_1(Private, void itemAtualizado(const QModelIndex &index))
  CS_SLOT_2(itemAtualizado)
};
