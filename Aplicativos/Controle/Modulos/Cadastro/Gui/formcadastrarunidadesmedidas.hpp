//
// Created by Robson on 31/12/2022.
//
#pragma once

#include <Sessao/IAcesso.hpp>
#include <QtCore>
#include <QtGui>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui
{
  class FormCadastrarUnidadesMedidas;
}
QT_END_NAMESPACE

class FormCadastrarUnidadesMedidas : public QWidget
{
  CS_OBJECT(FormCadastrarUnidadesMedidas)

public:
  explicit FormCadastrarUnidadesMedidas(QWidget *parent = nullptr);
  ~FormCadastrarUnidadesMedidas() override;
  
  void novo();
  void salvar();
  void remover();
  
  void novoConversao();
  void salvarConversao();
  void removerConversao();
  
private:
  Ui::FormCadastrarUnidadesMedidas *ui;
  Sessao::IAcesso *_acesso{nullptr};
  
  QSqlTableModel *m_tUnidadesMedidas{nullptr};
  QSqlRelationalTableModel *m_tConversao{nullptr};
};

