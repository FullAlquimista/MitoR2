//
// Created by Robson on 27/05/2023.
//
#pragma once
#include "MitoR/MitoR.hpp"
#include "../Source/acesso.hpp"
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QStandardItemModel>
#include <QWidget>
#include <spdlog/spdlog.h>

QT_BEGIN_NAMESPACE
namespace Ui
{
  class FormGerenciarUsuarios;
}
QT_END_NAMESPACE

class FormGerenciarUsuarios : public QWidget
{
  CS_OBJECT(FormGerenciarUsuarios)

public:
  using Json = nlohmann::json;

  struct Erro {
    enum {
      ErroComando = -2,
      Falha = -1,
      Sucesso = 0
    };
    operator int()
    {
      return erro;
    }
    int erro = Falha;
    QString msg{};
  };

  explicit FormGerenciarUsuarios(QWidget *parent = nullptr);
  ~FormGerenciarUsuarios() override;

protected:
  void novo();
  void pesquisar();
  void salvar();
  bool limpar();
  void remover();

  void atualizarDiretivas();

private:
  Ui::FormGerenciarUsuarios *ui;
  Sessao::Acesso *_acesso;

  struct Registro {
    int id{};
    QString usuario;
    QString nomePrevilegio;
    Json jDiretiva;
  }_registro;

  enum Roles {
    JsonPathRole = Qt::UserRole + 1
  };
  QStandardItemModel _modelo;

  void preencherModelo();
  void alterarEstadoFormulario(int novoEstado);
};
