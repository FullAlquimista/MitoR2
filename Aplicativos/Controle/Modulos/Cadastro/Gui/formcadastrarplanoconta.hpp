//
// Created by Robson on 24/12/2022.
//
#pragma once

#include <QtGui>
#include <QtSql>
#include <Sessao/IAcesso.hpp>

QT_BEGIN_NAMESPACE
namespace Ui
{
  class FormCadastrarPlanoConta;
}
QT_END_NAMESPACE

class FormCadastrarPlanoConta : public QWidget
{
  CS_OBJECT(FormCadastrarPlanoConta)

public:
  enum ColumnRoles {
    ClousureTableId = Qt::UserRole + 10,
    ClousureTableIdItem = Qt::UserRole + 11,
    ClousureTableIdNo = Qt::UserRole + 12,
    ClousureTableNivel = Qt::UserRole + 13,
    TableId = Qt::UserRole + 14,
    Estado = Qt::UserRole + 20
  };
  
  explicit FormCadastrarPlanoConta(QWidget *parent = nullptr);
  ~FormCadastrarPlanoConta() override;
  
  CS_SLOT_1(Public, void novo(bool))
  CS_SLOT_2(novo)
  CS_SLOT_1(Public, void salvar(bool))
  CS_SLOT_2(novo)
  CS_SLOT_1(Public, void remover(bool))
  CS_SLOT_2(remover)

private:
  Ui::FormCadastrarPlanoConta *ui;
  Sessao::IAcesso *_acesso{nullptr};
  QStandardItemModel *_model{nullptr};
  
  QSqlQueryModel *_tPlanosContaCt{nullptr};
  void atualizarTabelaPlanosConta();
  void carregarPlanosConta();
  MitoR::Erro atualizarIndex(const QModelIndex &index);
  MitoR::Erro inserirIndex(const QModelIndex &index);
  MitoR::Erro apagarIndex(const QModelIndex &index);
};
