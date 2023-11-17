
#pragma once

#include <QAction>
#include <QDialog>
#include <QMainWindow>
#include <QMenuBar>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QTabWidget>
#include <Sessao/IAcesso.hpp>
#include <Controle/IControle.hpp>

namespace Ui
{
  class FormCadastrarEmpresa;
}

class FormCadastrarEmpresa : public QDialog
{
  CS_OBJECT(FormCadastrarEmpresa)

  bool carregarTabelas();

  void configurarDispositivos();

  void configurarAcoes();

  bool validarPJ();

  bool salvarNovo();

  bool salvarEdicao();

  bool adicionarEndereco();

  bool removerEndereco();

  bool preencherEndereco(int index);

  void atualizarTabelaEndereco();

  bool validarEndereco();

  bool adicionarContato();

  bool removerContato();

  bool preencherContato(int index);

  void atualizarTabelaContato();

  bool validarContato();

public:
  explicit FormCadastrarEmpresa(QWidget *parent = nullptr);

  CS_SLOT_1(Public, void inicializacao())
  CS_SLOT_2(inicializacao)

  CS_SLOT_1(Public, bool salvarFormulario())
  CS_SLOT_2(salvarFormulario)

  CS_SLOT_1(Public, bool pesquisarFormulario())
  CS_SLOT_2(pesquisarFormulario)

  CS_SLOT_1(Public, bool limparFormulario())
  CS_SLOT_2(limparFormulario)

  CS_SLOT_1(Public, bool removerFormulario())
  CS_SLOT_2(removerFormulario)

protected:
  void keyPressEvent(QKeyEvent *ev) override;
  
private:
  
  Ui::FormCadastrarEmpresa *ui;
  Sessao::IAcesso *_acesso{nullptr};

  QSqlTableModel *_tPaises{nullptr};
  QSqlTableModel *_tEstados{nullptr};
  QSqlTableModel *_tCidades{nullptr};
  QSqlRelationalTableModel *_tEnderecos{nullptr};
  QSqlRelationalTableModel *_tContatos{nullptr};
  QSqlRelationalTableModel *_tTipoFornecedor{nullptr};

  // Formulário:
  enum class Estado {
    Novo,
    Alteracao
  };
  Estado _estado{Estado::Novo};
  int _idPessoa{0};
  int _idCliente{0};
  int _idFabricante{0};
  int _idFornecedor{0};
  int _idPj{0};
  QWidget *_widgetPesquisa{nullptr};
};