//
// Created by Robson on 14/01/2023.
//
#pragma once

#include <Sessao/IAcesso.hpp>
#include <QtCore>
#include <QtGui>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui
{
  class FormCadastrarFormatoMateriais;
}
QT_END_NAMESPACE

class FormCadastrarFormatoMateriais : public QWidget
{
  CS_OBJECT(FormCadastrarFormatoMateriais)

public:
  explicit FormCadastrarFormatoMateriais(QWidget *parent = nullptr);
  ~FormCadastrarFormatoMateriais() override;
  
  void novo();
  void salvar();
  void remover();
  

private:
  Ui::FormCadastrarFormatoMateriais *ui;
  Sessao::IAcesso *_acesso{nullptr};
  
  QSqlTableModel *m_model{nullptr};
};
