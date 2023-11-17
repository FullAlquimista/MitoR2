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
  class FormCadastrarTiposMateriais;
}
QT_END_NAMESPACE

class FormCadastrarTiposMateriais : public QWidget
{
  CS_OBJECT(FormCadastrarTiposMateriais)

public:
  explicit FormCadastrarTiposMateriais(QWidget *parent = nullptr);
  ~FormCadastrarTiposMateriais() override;
  
  void novo();
  void salvar();
  void remover();

private:
  Ui::FormCadastrarTiposMateriais *ui;
  Sessao::IAcesso *_acesso{nullptr};
  
  QSqlRelationalTableModel *m_model{nullptr};
};
