//
// Created by Robson on 01/01/2023.
//
#pragma once
#include <Sessao/IAcesso.hpp>
#include <QWidget>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui
{
  class FormCadastrarTiposPropostas;
}
QT_END_NAMESPACE

class FormCadastrarTiposPropostas : public QWidget
{
  CS_OBJECT(FormCadastrarTiposPropostas)

public:
  explicit FormCadastrarTiposPropostas(QWidget *parent = nullptr);
  ~FormCadastrarTiposPropostas() override;
  
  void novo();
  void salvar();
  void remover();

private:
  Ui::FormCadastrarTiposPropostas *ui;
  Sessao::IAcesso *_acesso{nullptr};
  
  QSqlRelationalTableModel *m_model{nullptr};
};
