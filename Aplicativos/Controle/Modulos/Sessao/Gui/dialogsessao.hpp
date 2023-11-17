//
// Created by Robson on 27/05/2023.
//
#pragma once

#include <QDialog>
#include <QSqlDatabase>
#include <Sessao/IAcesso.hpp>

QT_BEGIN_NAMESPACE
namespace Ui
{
  class DialogSessao;
}
QT_END_NAMESPACE

class DialogSessao : public QDialog
{
  CS_OBJECT(DialogSessao)

public:
  explicit DialogSessao(QWidget *parent = nullptr);
  ~DialogSessao() override;

  const char *ChaveUltimoUsuarioLogado = "/Aplicativos/Controle/Servidor/ultimoUsuario";

protected:
  void 	closeEvent (QCloseEvent *event) override;

private:
  Ui::DialogSessao *ui;
  Sessao::IAcesso *_acesso{nullptr};
};
