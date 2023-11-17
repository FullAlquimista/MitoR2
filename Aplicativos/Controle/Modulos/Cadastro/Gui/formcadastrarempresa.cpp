#include "formcadastrarempresa.hpp"
#include "ui_formcadastrarempresa.h"
#include <Cadastro/ICadastro.hpp>
#include <MitoR/Gui/dialogpesquisartabela.hpp>
#include <MitoR/Gui/eventfiltermudancafocus.hpp>
#include <MitoR/Gui/gui.hpp>
#include <MitoR/Sql/operacao.hpp>
#include <MitoR/Sql/validarentrada.hpp>
#include <QApplication>
#include <QCompleter>
#include <QDialog>
#include <QFocusEvent>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QRegularExpression>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QValidator>
#include <QWidget>
#include <spdlog/spdlog.h>

FormCadastrarEmpresa::FormCadastrarEmpresa(QWidget *parent) : QDialog(parent), ui(new Ui::FormCadastrarEmpresa)
{
  ui->setupUi(this);
  
  auto app = QApplication::instance();
  _acesso = app->findChild<Sessao::IAcesso*>();
  if(!_acesso)
  {
    spdlog::error("Serviços necessários não foram encontrados.");
    return;
  }

  inicializacao();
}

void FormCadastrarEmpresa::inicializacao()
{
  if (!carregarTabelas())
    return;

  configurarDispositivos();

  configurarAcoes();
}

bool FormCadastrarEmpresa::carregarTabelas()
{
  auto bd = _acesso->conexao();
  _tPaises = new QSqlTableModel(this, bd);
  _tPaises->setTable("endereco.paises");
  if (_tPaises->lastError().isValid()) {
    spdlog::warn("Não foi possível carregar a tabela endereco.paises. {}", _tPaises->lastError().text().toStdString());
    return false;
  }

  _tEstados = new QSqlTableModel(this, bd);
  _tEstados->setTable("endereco.estados");
  if (_tEstados->lastError().isValid()) {
    spdlog::warn("Não foi possível carregar a tabela endereco.estados. {}", _tEstados->lastError().text().toStdString());
    return false;
  }

  _tCidades = new QSqlTableModel(this, bd);
  _tCidades->setTable("endereco.cidades");
  if (_tCidades->lastError().isValid()) {
    spdlog::warn("Não foi possível carregar a tabela endereco.cidades. {}", _tCidades->lastError().text().toStdString());
    return false;
  }

  _tEnderecos = new QSqlRelationalTableModel(this, bd);
  _tEnderecos->setTable("cadastro.enderecos");
  if (_tEnderecos->lastError().isValid()) {
    spdlog::warn("Não foi possível carregar a tabela de endereços das pessoas. {}",
                 _tEnderecos->lastError().text().toStdString());
    return false;
  }
  _tEnderecos->setEditStrategy(QSqlTableModel::EditStrategy::OnManualSubmit);

  _tContatos = new QSqlRelationalTableModel(this, bd);
  _tContatos->setTable("cadastro.contatos");
  if (_tContatos->lastError().isValid()) {
    spdlog::warn("Não foi possível carregar a tabela de contatos das pessoas. {}",
                 _tContatos->lastError().text().toStdString());
    return false;
  }
  _tContatos->setEditStrategy(QSqlTableModel::EditStrategy::OnManualSubmit);

  _tTipoFornecedor = new QSqlRelationalTableModel(this, bd);
  _tTipoFornecedor->setTable("cadastro.tipos_fornecedores");
  if (_tTipoFornecedor->lastError().isValid()) {
    spdlog::warn("Não foi possível carregar a tabela de tipos de fornecedores. {}",
                 _tTipoFornecedor->lastError().text().toStdString());
    return false;
  }

  // Verifica a existencias das tabelas.
  QStringList tabelasRequeridas{"cadastro.index",
                                "cadastro.pessoas",
                                "cadastro.pessoas_fisicas",
                                "cadastro.pessoas_juridicas",
                                "cadastro.fornecedores",
                                "cadastro.clientes",
                                "cadastro.fabricantes"};
  auto lista = bd.tables();
  for (const auto &strTabela: lista) {
    if (tabelasRequeridas.contains(strTabela))
      tabelasRequeridas.removeOne(strTabela);
  }
  if (tabelasRequeridas.isEmpty())
    return true;
  QString fmtTabelas;
  for (const auto &str: tabelasRequeridas) {
    fmtTabelas += str;
    fmtTabelas += ", ";
  };
  spdlog::warn("As seguintes tabelas não foram entrontradas: {}", fmtTabelas.toStdString());
  return false;
}

void FormCadastrarEmpresa::configurarDispositivos()
{
  ui->pushButtonPesquisaRapida->setStatusTip(
      "Faz uma pesquisa utilizando um dos três configurarDispositivos: Nome, Razão Social ou CNPJ como fonte.");

  //auto ev1 = new MitoR::Gui::EventFilterFormatadorTexto("000.000.000/0000-00", ui->lineEditCNPJ);
  //ui->lineEditCNPJ->installEventFilter(ev1);
  auto lineEditCNPJFormatador = new MitoR::Gui::FormatLineEdit(ui->lineEditCNPJ, "000.000.000/0000-00");
  (void) lineEditCNPJFormatador;

  //auto ev2 = new MitoR::Gui::EventFilterFormatadorTexto("000.000-000", ui->lineEditCEP);
  //ui->lineEditCEP->installEventFilter(ev2);
  auto lineEditCEPFormatador = new MitoR::Gui::FormatLineEdit(ui->lineEditCEP, "000.000-000");
  (void) lineEditCEPFormatador;

  ui->comboBoxPais->setModel(_tPaises);
  ui->comboBoxPais->setModelColumn(1);

  ui->comboBoxEstado->setModel(_tEstados);
  ui->comboBoxEstado->setModelColumn(2);
  QCompleter *completerEstado = new QCompleter(_tEstados, ui->comboBoxEstado);
  completerEstado->setCompletionColumn(2);
  completerEstado->setCaseSensitivity(Qt::CaseInsensitive);
  ui->comboBoxEstado->setCompleter(completerEstado);
  ui->comboBoxEstado->setEditable(true);

  ui->comboBoxCidade->setModel(_tCidades);
  ui->comboBoxCidade->setModelColumn(3);
  QCompleter *completerCidade = new QCompleter(_tCidades, ui->comboBoxCidade);
  completerCidade->setCompletionColumn(3);
  completerCidade->setCaseSensitivity(Qt::CaseInsensitive);
  ui->comboBoxCidade->setCompleter(completerCidade);
  ui->comboBoxCidade->setEditable(true);

  ui->dateEditEndereco->setDate(QDate::currentDate());
  ui->comboBoxEndereco->setModel(_tEnderecos);
  ui->comboBoxEndereco->setModelColumn(2);
  ui->comboBoxEndereco->setEditable(true);

  ui->dateEditContato->setDate(QDate::currentDate());
  ui->comboBoxContato->setModel(_tContatos);
  ui->comboBoxContato->setModelColumn(2);
  ui->comboBoxContato->setEditable(true);

  ui->comboBoxTipoFornecedor->setModel(_tTipoFornecedor);
  ui->comboBoxTipoFornecedor->setModelColumn(1);
  _tTipoFornecedor->select();
  if (_tTipoFornecedor->rowCount() > 0) {
    ui->comboBoxTipoFornecedor->setCurrentIndex(0);
  }
  ui->labelTipoFornecedor->setHidden(true);
  ui->comboBoxTipoFornecedor->setHidden(true);
}

void FormCadastrarEmpresa::configurarAcoes()
{
  // Ações do formulário.
  QObject::connect(ui->pushButtonPesquisaRapida, &QPushButton::clicked, this, &pesquisarFormulario);
  QObject::connect(ui->pushButtonSalvar, &QPushButton::clicked, this, &salvarFormulario);
  QObject::connect(ui->pushButtonLimpar, &QPushButton::clicked, this, [this]() {
    QMessageBox pergunta(this);
    pergunta.setIcon(QMessageBox::Question);
    pergunta.setWindowTitle("Limpar formulário...");
    pergunta.setText("Deseja realmente limpar este formulário ?");
    pergunta.addButton("Sim", QMessageBox::ButtonRole::YesRole);
    auto btNao = pergunta.addButton("Não", QMessageBox::ButtonRole::NoRole);
    pergunta.exec();
    if (btNao == pergunta.clickedButton()) {
      return;
    }

    this->_idPessoa = 0;
    this->_idPj = 0;
    this->_idCliente = 0;
    this->_idFornecedor = 0;
    this->_idFabricante = 0;
    this->_estado = Estado::Novo;
    this->_widgetPesquisa = nullptr;

    this->limparFormulario();
    this->atualizarTabelaEndereco();
    this->atualizarTabelaContato();
  });
  QObject::connect(ui->pushButtonRemover, &QPushButton::clicked, this, &removerFormulario);

  QObject::connect(ui->pushButtonAdicionarEndereco, &QPushButton::clicked, this,
                   [this]() { if (this->validarEndereco()) this->adicionarEndereco(); });
  QObject::connect(ui->pushButtonRemoverEndereco, &QPushButton::clicked, this, &removerEndereco);

  QObject::connect(ui->pushButtonAdicionarContato, &QPushButton::clicked, this,
                   [this]() { if (this->validarContato()) this->adicionarContato(); });
  QObject::connect(ui->pushButtonRemoverContato, &QPushButton::clicked, this, &removerContato);

  QObject::connect(ui->checkBoxFornecedor, &QCheckBox::stateChanged, this, [this](int state) {
    if (state == Qt::CheckState::Checked) {
      ui->labelTipoFornecedor->setHidden(false);
      ui->comboBoxTipoFornecedor->setHidden(false);
    } else if (state == Qt::CheckState::Unchecked) {
      ui->labelTipoFornecedor->setHidden(true);
      ui->comboBoxTipoFornecedor->setHidden(true);
    }
  });

  // Ao mudar de campo.
  ui->lineEditNomeFantasia->installEventFilter(new MitoR::Gui::EventFilterMudancaFocus([this](QEvent*) {
    this->_widgetPesquisa = ui->lineEditNomeFantasia;
    this->ui->labelNomeFantasia->setStyleSheet(
        "font-weight: bold;");
    this->ui->labelRazaoSocial->setStyleSheet(
        "font-weight: normal;");
    this->ui->labelCNPJ->setStyleSheet(
        "font-weight: normal;");
  },
                                                                                       {}, ui->lineEditNomeFantasia));
  ui->lineEditRazaoSocial->installEventFilter(new MitoR::Gui::EventFilterMudancaFocus([this](QEvent*) {
    this->_widgetPesquisa = ui->lineEditRazaoSocial;
    this->ui->labelNomeFantasia->setStyleSheet(
        "font-weight: normal;");
    this->ui->labelRazaoSocial->setStyleSheet(
        "font-weight: bold;");
    this->ui->labelCNPJ->setStyleSheet(
        "font-weight: normal;");
  },
                                                                                      {}, ui->lineEditRazaoSocial));
  ui->lineEditCNPJ->installEventFilter(new MitoR::Gui::EventFilterMudancaFocus([this](QEvent*) {
    this->_widgetPesquisa = ui->lineEditCNPJ;
    this->ui->labelNomeFantasia->setStyleSheet(
        "font-weight: normal;");
    this->ui->labelRazaoSocial->setStyleSheet(
        "font-weight: normal;");
    this->ui->labelCNPJ->setStyleSheet(
        "font-weight: bold;");
  },
                                                                               {}, ui->lineEditCNPJ));

  // Endereços.
  connect(ui->comboBoxPais, cs_mp_cast<int>(&QComboBox::currentIndexChanged), this, [this](int index) {
    auto mIdx = ui->comboBoxPais->model()->index(index, 0);
    if (mIdx.isValid()) {
      int idPais = mIdx.data().toInt();
      this->_tEstados->setFilter(QString("id_pais = %1").formatArg(idPais));
    }
  });
  connect(ui->comboBoxEstado, cs_mp_cast<int>(&QComboBox::currentIndexChanged), this, [this](int index) {
    auto mIdxIdPais = ui->comboBoxEstado->model()->index(index, 1);
    auto mIdxIdEstado = ui->comboBoxEstado->model()->index(index, 0);
    if (mIdxIdPais.isValid() && mIdxIdEstado.isValid()) {
      int idPais = mIdxIdPais.data().toInt();
      int idEstado = mIdxIdEstado.data().toInt();
      this->_tCidades->setFilter(QString("id_pais = %1 AND id_estado = %2").formatArg(idPais).formatArg(idEstado));
    }
  });
  _tPaises->select();
  _tEstados->select();
  _tCidades->select();
  connect(ui->comboBoxEndereco, cs_mp_cast<int>(&QComboBox::currentIndexChanged), this, [this](int index) {
    this->preencherEndereco(index);
  });

  // Contatos.
  connect(ui->comboBoxContato, cs_mp_cast<int>(&QComboBox::currentIndexChanged), this, [this](int index) {
    this->preencherContato(index);
  });
}

bool FormCadastrarEmpresa::salvarFormulario()
{
  if (_estado == Estado::Novo) {
    QMessageBox pergunta(this);
    pergunta.setIcon(QMessageBox::Question);
    pergunta.setWindowTitle("Novo formulário...");
    pergunta.setText("Deseja salvar um novo registro ?");
    auto btSim = pergunta.addButton("Sim", QMessageBox::ButtonRole::YesRole);
    pergunta.addButton("Não", QMessageBox::ButtonRole::NoRole);
    pergunta.exec();
    if (btSim == pergunta.clickedButton()) {
      return salvarNovo();
    }
  } else if (_estado == Estado::Alteracao) {
    QMessageBox pergunta(this);
    pergunta.setIcon(QMessageBox::Question);
    pergunta.setWindowTitle("Edição do formulário...");
    pergunta.setText(QString("Deseja salvar as alterações deste registro com id '%1' ?").formatArg(_idPessoa));
    auto btSim = pergunta.addButton("Sim", QMessageBox::ButtonRole::YesRole);
    pergunta.addButton("Não", QMessageBox::ButtonRole::NoRole);
    pergunta.exec();
    if (btSim == pergunta.clickedButton()) {
      return salvarEdicao();
    }
  }
  return false;
}

bool FormCadastrarEmpresa::salvarNovo()
{
  if (!validarPJ())
    return false;
  
  auto bd = _acesso->conexao();
  switch (MitoR::Erro e = [this, &bd]() -> MitoR::Erro {
    if (!bd.transaction()) {
      return MitoR::Erro{MitoR::Erro::Falha, QString("Não foi possível criar uma transação no banco de dados! %1").formatArg(
                                                         bd.lastError().text())};
    }
    // Cadastro de uma pessoa.
    {
      MitoR::Sql::InserirRegistrosComIndex inserirPessoas(bd, "pessoas", "cadastro");
      auto r = inserirPessoas.registroSemValores();
      r.setValue("nome", ui->lineEditNomeFantasia->text().toUpper());
      if (!inserirPessoas.enviar(r)) {
        return MitoR::Erro{MitoR::Erro::Falha, "Não foi possível inserir uma nova entidade pessoa!"};
      }
      auto res = inserirPessoas.ultimoRegistroInserido();
      this->_idPessoa = res.value(0).toInt();
    }
    // Cadastro de uma pessoa júridica.
    {
      MitoR::Sql::InserirRegistrosComIndex inserirPJ(bd, "pessoas_juridicas", "cadastro");
      auto r = inserirPJ.registroSemValores();
      r.setValue("id_pessoa", this->_idPessoa);
      r.setValue("razao_social", ui->lineEditRazaoSocial->text().toUpper());
      QString cnpj = ui->lineEditCNPJ->text().remove(QRegularExpression("^0"));
      cnpj.remove(QRegularExpression("[-,./]"));
      r.setValue("cnpj", cnpj);
      QString ie = ui->lineEditIE->text().remove(QRegularExpression("^0"));
      ie.remove(QRegularExpression("[-,./]"));
      r.setValue("ie", ie);
      r.setValue("data_fundacao", ui->dateEditFundacao->date());
      if (!inserirPJ.enviar(r)) {
        return MitoR::Erro{MitoR::Erro::Falha,
                           "Não foi possível inserir uma nova classificação pessoa jurídica!"};
      }
      auto res = inserirPJ.ultimoRegistroInserido();
      this->_idPj = res.value(0).toInt();
    }
    // Classificação de uma pessoa jurídica.
    this->_idFabricante = 0;
    if (ui->checkBoxFabricante->isChecked()) {
      {
        MitoR::Sql::InserirRegistrosComIndex inserirFabricantes(bd, "fabricantes", "cadastro");
        auto r = inserirFabricantes.registroSemValores();
        r.setValue("id_pessoa", this->_idPessoa);
        r.setValue("id_pessoa_juridica", this->_idPj);
        if (!inserirFabricantes.enviar(r)) {
          return MitoR::Erro{MitoR::Erro::Falha,
                             "Não foi possível inserir uma nova classificação como fabricante!"};
        }
        auto res = inserirFabricantes.ultimoRegistroInserido();
        this->_idFabricante = res.value(0).toInt();
      }
    }
    this->_idCliente = 0;
    if (ui->checkBoxCliente->isChecked()) {
      {
        MitoR::Sql::InserirRegistrosComIndex inserirClientes(bd, "clientes", "cadastro");
        auto r = inserirClientes.registroSemValores();
        r.setValue("id_pessoa", this->_idPessoa);
        r.setValue("id_pessoa_juridica", this->_idPj);
        if (!inserirClientes.enviar(r)) {
          return MitoR::Erro{MitoR::Erro::Falha,
                             "Não foi possível inserir uma nova classificação como cliente!"};
        }
        auto res = inserirClientes.ultimoRegistroInserido();
        this->_idCliente = res.value(0).toInt();
      }
    }
    this->_idFornecedor = 0;
    if (ui->checkBoxFornecedor->isChecked()) {
      {
        MitoR::Sql::InserirRegistrosComIndex inserirFornecedores(bd, "fornecedores", "cadastro");
        auto r = inserirFornecedores.registroSemValores();
        r.setValue("id_pessoa", this->_idPessoa);
        r.setValue("id_pessoa_juridica", this->_idPj);
        r.setValue("id_tipo_fornecedor",
                   this->_tTipoFornecedor->index(ui->comboBoxTipoFornecedor->currentIndex(), 0).data().toInt());
        if (!inserirFornecedores.enviar(r)) {
          return MitoR::Erro{MitoR::Erro::Falha,
                             "Não foi possível inserir uma nova classificação como fornecedor!"};
        }
        auto res = inserirFornecedores.ultimoRegistroInserido();
        this->_idFornecedor = res.value(0).toInt();
      }
    }

    if (!bd.commit()) {
      return MitoR::Erro{MitoR::Erro::Falha, "Não foi possível efetuar a transação no banco de dados!"};
    }

    if (this->ui->comboBoxEndereco->currentText().isEmpty() == false && this->validarEndereco()) {
      if (!this->adicionarEndereco()) {
        spdlog::warn("Não foi possível inserir o novo endereço para a pessoa júridica!");
      }
    }

    if (this->ui->comboBoxContato->currentText().isEmpty() == false && this->validarContato()) {
      if (!this->adicionarContato()) {
        spdlog::warn("Não foi possível inserir o novo contato para a pessoa júridica!");
      }
    }

    _estado = Estado::Alteracao;
    return MitoR::Erro{MitoR::Erro::Sucesso, ""};
  }()) {
    case MitoR::Erro::Sucesso: {
      return true;
    } break;
    case MitoR::Erro::Falha: {
      if (!bd.rollback()) {
        return MitoR::Erro{MitoR::Erro::Falha,
                           QString("Não foi possível rebobinar a transação no banco de dados! {}").formatArg(
                                       bd.lastError().text())};
      }
      spdlog::warn(e.msg.toStdString());
      QMessageBox::warning(this, "Novo registro...", e.msg);
    } break;
  }
  return false;
}

bool FormCadastrarEmpresa::salvarEdicao()
{
  if (!validarPJ())
    return false;
  
  auto bd = _acesso->conexao();
  switch (MitoR::Erro e = [this, &bd]() -> MitoR::Erro {
    QSqlQuery p(bd);
    if (!bd.transaction()) {
      return MitoR::Erro{MitoR::Erro::Falha, QString("Não foi possível criar uma transação no banco de dados! {}").formatArg(
                                                         bd.lastError().text())};
    }
    p.prepare("UPDATE cadastro.pessoas SET nome = ? WHERE id = ?;");
    p.bindValue(0, ui->lineEditNomeFantasia->text().toUpper());
    p.bindValue(1, _idPessoa);
    if (!p.exec()) {
      return MitoR::Erro{MitoR::Erro::Falha, QString("Não foi possível salvar a entidade pessoa! {}").formatArg(
                                                         p.lastError().text())};
    }
    p.prepare(
        "UPDATE cadastro.pessoas_juridicas SET razao_social = ?, cnpj = ?, ie = ?, data_fundacao = ? WHERE id_Pessoa = ?;");
    p.bindValue(0, ui->lineEditRazaoSocial->text().toUpper());
    QString cnpj = ui->lineEditCNPJ->text().remove(QRegularExpression("^0"));
    cnpj.remove(QRegularExpression("[-,./]"));
    p.bindValue(1, cnpj);
    QString ie = ui->lineEditIE->text().remove(QRegularExpression("^0"));
    ie.remove(QRegularExpression("[-,./]"));
    p.bindValue(2, ie);
    p.bindValue(3, ui->dateEditFundacao->date());
    p.bindValue(4, this->_idPessoa);
    if (!p.exec()) {
      return MitoR::Erro{MitoR::Erro::Falha, QString("Não foi possível salvar a classificação pessoa jurídica! {}").formatArg(
                                                         p.lastError().text())};
    }
    if (ui->checkBoxFabricante->isChecked()) {
      if (this->_idFabricante == 0) {
        MitoR::Sql::InserirRegistrosComIndex inserirFabricantes(bd, "fabricantes", "cadastro");
        {
          auto r = inserirFabricantes.registroSemValores();
          r.setValue("id_pessoa", this->_idPessoa);
          r.setValue("id_pessoa_juridica", this->_idPj);
          if (!inserirFabricantes.enviar(r)) {
            return MitoR::Erro{MitoR::Erro::Falha,
                               QString("Não foi possível inserir uma nova classificação como fabricante! {}").formatArg(
                                           p.lastError().text())};
          }
          auto res = inserirFabricantes.ultimoRegistroInserido();
          this->_idFabricante = res.value(0).toInt();
        }
      } else {
        // ...
      }
    } else if (this->_idFabricante != 0) {
      p.prepare("DELETE FROM cadastro.fabricantes WHERE id = ?;");
      p.bindValue(0, this->_idFabricante);
      if (!p.exec()) {
        return MitoR::Erro{MitoR::Erro::Falha,
                           QString("Não foi possível remover a classificação como fabricante! {}").formatArg(
                                       p.lastError().text())};
      }
    }
    if (ui->checkBoxCliente->isChecked()) {
      if (this->_idCliente == 0) {
        MitoR::Sql::InserirRegistrosComIndex inserirClientes(bd, "clientes", "cadastro");
        {
          auto r = inserirClientes.registroSemValores();
          r.setValue("id_pessoa", this->_idPessoa);
          r.setValue("id_pessoa_juridica", this->_idPj);
          if (!inserirClientes.enviar(r)) {
            return MitoR::Erro{MitoR::Erro::Falha,
                               QString("Não foi possível inserir uma nova classificação como cliente! {}").formatArg(
                                           p.lastError().text())};
          }
          auto res = inserirClientes.ultimoRegistroInserido();
          this->_idCliente = res.value(0).toInt();
        }
      } else {
        // ...
      }
    } else if (this->_idCliente != 0) {
      p.prepare("DELETE FROM cadastro.clientes WHERE id = ?;");
      p.bindValue(0, this->_idCliente);
      if (!p.exec()) {
        return MitoR::Erro{MitoR::Erro::Falha, QString("Não foi possível remover a classificação como cliente! {}").formatArg(
                                                           p.lastError().text())};
      }
    }
    if (ui->checkBoxFornecedor->isChecked()) {
      if (this->_idFornecedor == 0) {
        MitoR::Sql::InserirRegistrosComIndex inserirFornecedores(bd, "fornecedores", "cadastro");
        {
          auto r = inserirFornecedores.registroSemValores();
          r.setValue("id_pessoa", this->_idPessoa);
          r.setValue("id_pessoa_juridica", this->_idPj);
          r.setValue("id_tipo_fornecedor",
                     this->_tTipoFornecedor->index(ui->comboBoxTipoFornecedor->currentIndex(), 0).data().toInt());
          if (!inserirFornecedores.enviar(r)) {
            return MitoR::Erro{MitoR::Erro::Falha,
                               QString("Não foi possível inserir uma nova classificação como fornecedor! {}").formatArg(
                                           p.lastError().text())};
          }
          auto res = inserirFornecedores.ultimoRegistroInserido();
          this->_idFornecedor = res.value(0).toInt();
        }
      } else {
        p.prepare("UPDATE cadastro.fornecedores SET id_tipo_fornecedor=? WHERE id=?;");
        p.bindValue(0, this->_tTipoFornecedor->index(ui->comboBoxTipoFornecedor->currentIndex(), 0).data().toInt());
        p.bindValue(1, this->_idFornecedor);
        if (!p.exec()) {
          return MitoR::Erro{MitoR::Erro::Falha,
                             QString("Não foi possível alterar a classificação do fornecedor! {}").formatArg(
                                         p.lastError().text())};
        }
      }
    } else if (this->_idFornecedor != 0) {
      p.prepare("DELETE FROM cadastro.fornecedores WHERE id = ?;");
      p.bindValue(0, this->_idFornecedor);
      if (!p.exec()) {
        return MitoR::Erro{MitoR::Erro::Falha,
                           QString("Não foi possível remover a classificação como fornecedor! {}").formatArg(
                                       p.lastError().text())};
      }
    }

    int indexEndereco = ui->comboBoxEndereco->currentIndex();
    if (indexEndereco >= 0) {
      auto idEndereco = this->_tEnderecos->index(indexEndereco, 0).data().toInt();
      p.prepare(
          "UPDATE cadastro.enderecos SET nome = ?, data = ?, logradouro = ?, numero = ?, complemento = ?, bairro = ?, id_uf = ?, id_cidade = ?, cep = ?, id_pais = ? WHERE id = ?;");
      p.bindValue(0, ui->comboBoxEndereco->currentText().toUpper());
      p.bindValue(1, ui->dateEditEndereco->date());
      p.bindValue(2, ui->lineEditLogradouro->text().toUpper());
      p.bindValue(3, ui->lineEditNumero->text().toUpper());
      p.bindValue(4, ui->lineEditComplemento->text().toUpper());
      p.bindValue(5, ui->lineEditBairro->text().toUpper());
      p.bindValue(6, ui->comboBoxEstado->model()->index(ui->comboBoxEstado->currentIndex(), 0).data().toInt());
      p.bindValue(7, ui->comboBoxCidade->model()->index(ui->comboBoxCidade->currentIndex(), 0).data().toInt());
      QString cep = ui->lineEditCEP->text().remove(QRegularExpression("^0"));
      cep.remove(QRegularExpression("[-,./]"));
      p.bindValue(8, cep);
      p.bindValue(9, ui->comboBoxPais->model()->index(ui->comboBoxPais->currentIndex(), 0).data().toInt());
      p.bindValue(10, idEndereco);
      if (!p.exec()) {
        return MitoR::Erro{MitoR::Erro::Falha,
                           QString("Não foi possível salvar o endereço! {}").formatArg(p.lastError().text())};
      }
    }

    int indexContato = ui->comboBoxContato->currentIndex();
    if (indexContato >= 0) {
      auto idContato = this->_tContatos->index(indexContato, 0).data().toInt();
      MitoR::Sql::AtualizarRegistros atualizarContato(bd, "contatos", "cadastro");
      auto reg = atualizarContato.registroSemValores();
      reg.setValue("id", idContato);
      reg.setValue("id_pessoa", this->_idPessoa);
      reg.setValue("nome", ui->comboBoxContato->currentText().toUpper());
      reg.setValue("email", ui->lineEditEmail->text().toUpper());
      reg.setValue("telefone", ui->lineEditTelefone->text().toUpper());
      reg.setValue("data", ui->dateEditContato->date());
      reg.setValue("cargo", ui->lineEditCargo->text().toUpper());
      if (atualizarContato.enviar(reg) == false) {
        return MitoR::Erro{MitoR::Erro::Falha, "Não foi possível atualizar o registro do contato!"};
      }
    }

    if (!bd.commit()) {
      return MitoR::Erro{MitoR::Erro::Falha, QString("Não foi possível efetuar a transação no banco de dados! {}").formatArg(
                                                         bd.lastError().text())};
    }
    return MitoR::Erro{MitoR::Erro::Sucesso, ""};
  }()) {
    case MitoR::Erro::Sucesso: {
      return true;
    } break;
    case MitoR::Erro::Falha: {
      if (!bd.rollback()) {
        return MitoR::Erro{MitoR::Erro::Falha,
                           QString("Não foi possível rebobinar a transação no banco de dados! {}").formatArg(
                                       bd.lastError().text())};
      }
      spdlog::warn(e.msg.toStdString());
      QMessageBox::warning(this, "Salvar registro...", e.msg);
    } break;
  }
  return false;
}

bool FormCadastrarEmpresa::adicionarEndereco()
{
  auto bd = _acesso->conexao();
  MitoR::Sql::InserirRegistrosComIndex inserirEndereco(bd, "enderecos", "cadastro");
  auto reg = inserirEndereco.registroSemValores();
  reg.setValue("id_pessoa", _idPessoa);
  reg.setValue("nome", ui->comboBoxEndereco->currentText().toUpper());
  reg.setValue("data", ui->dateEditEndereco->date());
  reg.setValue("logradouro", ui->lineEditLogradouro->text().toUpper());
  reg.setValue("numero", ui->lineEditNumero->text().toUpper());
  reg.setValue("complemento", ui->lineEditComplemento->text().toUpper());
  reg.setValue("bairro", ui->lineEditBairro->text().toUpper());
  reg.setValue("id_uf", ui->comboBoxEstado->model()->index(ui->comboBoxEstado->currentIndex(), 0).data().toInt());
  reg.setValue("id_cidade", ui->comboBoxCidade->model()->index(ui->comboBoxCidade->currentIndex(), 0).data().toInt());
  QString cep = ui->lineEditCEP->text().remove(QRegularExpression("^0"));
  cep.remove(QRegularExpression("[-,./]"));
  reg.setValue("cep", cep);
  reg.setValue("id_pais", ui->comboBoxPais->model()->index(ui->comboBoxPais->currentIndex(), 0).data().toInt());
  reg.setValue("ativo", 1);
  if (!inserirEndereco.enviar(reg)) {
    spdlog::warn("Não foi possível adicionar um novo endereço.");
    return false;
  }
  atualizarTabelaEndereco();

  return true;
}

bool FormCadastrarEmpresa::removerEndereco()
{
  if (_estado != Estado::Alteracao || ui->comboBoxEndereco->currentIndex() == -1) {
    QMessageBox::warning(this, "Remover registro de endereço", "Pesquise um registro para tentar remove-lo.");
    return false;
  }
  QMessageBox pergunta(this);
  pergunta.setIcon(QMessageBox::Question);
  pergunta.setWindowTitle("Remover endereço...");
  pergunta.setText(QString("Deseja remover este endereço ?"));
  pergunta.addButton("Sim", QMessageBox::ButtonRole::YesRole);
  auto btNao = pergunta.addButton("Não", QMessageBox::ButtonRole::NoRole);
  pergunta.exec();
  if (btNao == pergunta.clickedButton()) {
    return false;
  }
  auto idxRemover = _tEnderecos->index(ui->comboBoxEndereco->currentIndex(), 0);
  if (_tEnderecos->removeRow(idxRemover.row()) == false) {
    spdlog::warn("Falha ao tentar remover o registro do endereço. {}", idxRemover.data().toInt());
    QMessageBox::warning(this, "Remover registro de endereço", "Não foi possível remover o endereço.");
    _tEnderecos->revertAll();
    return false;
  }
  _tEnderecos->submitAll();
  return true;
}

bool FormCadastrarEmpresa::preencherEndereco(int index)
{
  if (index < 0)
    return false;

  QSqlRecord reg = _tEnderecos->record(index);
  ui->dateEditEndereco->setDate(reg.value("data").toDate());
  ui->lineEditLogradouro->setText(reg.value("logradouro").toString());
  ui->lineEditCEP->clear();
  ui->lineEditCEP->insert(reg.value("cep").toString());
  ui->lineEditNumero->setText(reg.value("numero").toString());
  ui->lineEditComplemento->setText(reg.value("complemento").toString());
  ui->lineEditBairro->setText(reg.value("bairro").toString());
  ui->comboBoxPais->setCurrentIndex(0);
  int idEstado = reg.value("id_uf").toInt();
  for (int row = 0; row < ui->comboBoxEstado->model()->rowCount(); row++) {
    auto idx = ui->comboBoxEstado->model()->index(row, 0);
    int id = idx.data().toInt();
    if (idEstado == id) {
      ui->comboBoxEstado->setCurrentIndex(idx.row());
      break;
    }
  }
  int idCidade = reg.value("id_cidade").toInt();
  _tCidades->select();
  for (int row = 0; row < ui->comboBoxCidade->model()->rowCount(); row++) {
    auto idx = ui->comboBoxCidade->model()->index(row, 0);
    int id = idx.data().toInt();
    if (idCidade == id) {
      ui->comboBoxCidade->setCurrentIndex(idx.row());
      break;
    }
  }
  return true;
}

void FormCadastrarEmpresa::atualizarTabelaEndereco()
{
  this->_tEnderecos->setFilter(QString("id_pessoa = %1").formatArg(this->_idPessoa));
  this->_tEnderecos->select();
}

bool FormCadastrarEmpresa::adicionarContato()
{
  auto bd = _acesso->conexao();
  MitoR::Sql::InserirRegistrosComIndex inserirContato(bd, "contatos", "cadastro");
  auto reg = inserirContato.registroSemValores();
  reg.setValue("id_pessoa", this->_idPessoa);
  reg.setValue("nome", ui->comboBoxContato->currentText());
  reg.setValue("email", ui->lineEditEmail->text());
  reg.setValue("telefone", ui->lineEditTelefone->text());
  reg.setValue("data", ui->dateEditContato->date());
  reg.setValue("cargo", ui->lineEditCargo->text());
  if (inserirContato.enviar(reg) == false) {
    QMessageBox::warning(this, "Adicionar contato", "Não foi possível adicionar o contato.");
    return false;
  }

  this->atualizarTabelaContato();
  return true;
}

bool FormCadastrarEmpresa::removerContato()
{
  int idx = ui->comboBoxContato->currentIndex();
  if (_estado != Estado::Alteracao || idx == -1) {
    QMessageBox::warning(this, "Remover registro de contato", "Pesquise um registro para tentar remove-lo.");
    return false;
  }
  QMessageBox pergunta(this);
  pergunta.setIcon(QMessageBox::Question);
  pergunta.setWindowTitle("Remover contato...");
  pergunta.setText(QString("Deseja remover este contato ?"));
  pergunta.addButton("Sim", QMessageBox::ButtonRole::YesRole);
  auto btNao = pergunta.addButton("Não", QMessageBox::ButtonRole::NoRole);
  pergunta.exec();
  if (btNao == pergunta.clickedButton()) {
    return false;
  }

  auto idxRemover = this->_tContatos->index(ui->comboBoxContato->currentIndex(), 0);
  if (_tContatos->removeRows(idxRemover.row(), 1) == false) {
    spdlog::warn("Falha ao tentar remover o registro do contato. {}", idxRemover.data().toInt());
    QMessageBox::warning(this, "Remover registro de contato",
                         "Não foi possível remover o registro ou não foi encontrado.");
  }
  _tContatos->submitAll();
  return true;
}

bool FormCadastrarEmpresa::preencherContato(int index)
{
  if (index < 0)
    return false;

  auto reg = _tContatos->record(index);
  ui->lineEditEmail->setText(reg.value("email").toString());
  ui->lineEditTelefone->clear();
  ui->lineEditTelefone->insert(reg.value("telefone").toString());
  ui->dateEditContato->setDate(reg.value("data").toDate());
  ui->lineEditCargo->setText(reg.value("cargo").toString());

  return true;
}

void FormCadastrarEmpresa::atualizarTabelaContato()
{
  this->_tContatos->setFilter(QString("id_pessoa = %1").formatArg(this->_idPessoa));
  this->_tContatos->select();
}

bool FormCadastrarEmpresa::pesquisarFormulario()
{
  auto bd = _acesso->conexao();
  QSqlQuery p(bd);

  switch (MitoR::Erro e = [&]() -> MitoR::Erro {
    if (!this->_widgetPesquisa)
      return MitoR::Erro{MitoR::Erro::Falha,
                         "Preencha um dos três configurarDispositivos de pesquisa rápida.\nNome Fantasia, Razão Social ou CNPJ."};
    QString cmd = R"(select p.id, pj.id as id_pessoa_juridica, nome, razao_social, cnpj, ie, data_fundacao from cadastro.pessoas as p, cadastro.pessoas_juridicas as pj where pj.id_pessoa = p.id AND %1)";
    QString pesquisa;
    if (this->_widgetPesquisa == ui->lineEditNomeFantasia) {
      pesquisa = QString("p.nome LIKE '%%1%'").formatArg(ui->lineEditNomeFantasia->text().toUpper());
    } else if (this->_widgetPesquisa == ui->lineEditRazaoSocial) {
      pesquisa = QString("pj.razao_social LIKE '%%1%'").formatArg(ui->lineEditRazaoSocial->text().toUpper());
    } else {
      QString cnpj = ui->lineEditCNPJ->text().remove(QRegularExpression("^0"));
      cnpj.remove(QRegularExpression("[-,./]"));
      pesquisa = QString("pj.cnpj LIKE '%%1%'").formatArg(cnpj);
    }
    QString cmdFormatado = cmd.formatArg(pesquisa);
    if (this->ui->checkBoxFabricante->isChecked()) {
      cmdFormatado = QString(
                         "select t.id, t.id_pessoa_juridica, nome, razao_social, cnpj, ie, data_fundacao from (%1) as t inner join cadastro.fabricantes as c on t.id = c.id_pessoa")
                         .formatArg(
                             cmdFormatado);
    }
    if (this->ui->checkBoxFornecedor->isChecked()) {
      cmdFormatado = QString(
                         "select t.id, t.id_pessoa_juridica, nome, razao_social, cnpj, ie, data_fundacao from (%1) as t inner join cadastro.fornecedores as c on t.id = c.id_pessoa")
                         .formatArg(
                             cmdFormatado);
    }
    if (this->ui->checkBoxCliente->isChecked()) {
      cmdFormatado = QString(
                         "select t.id, t.id_pessoa_juridica, nome, razao_social, cnpj, ie, data_fundacao from (%1) as t inner join cadastro.clientes as c on t.id = c.id_pessoa")
                         .formatArg(
                             cmdFormatado);
    }
    if (!p.exec(cmdFormatado)) {
      return MitoR::Erro{MitoR::Erro::Falha, p.lastError().text()};
    }
    QSqlRecord registroSelecionado;
    if (p.size() > 1) {
      auto queryTable = new QSqlQueryModel;
      queryTable->setQuery(p);
      queryTable->setHeaderData(0, Qt::Horizontal, QString("ID"));
      queryTable->setHeaderData(1, Qt::Horizontal, QString("ID Pessoa"));
      queryTable->setHeaderData(2, Qt::Horizontal, QString("Nome"));
      queryTable->setHeaderData(3, Qt::Horizontal, QString("Razão Social"));
      queryTable->setHeaderData(4, Qt::Horizontal, QString("CNPJ"));
      queryTable->setHeaderData(5, Qt::Horizontal, QString("IE"));
      queryTable->setHeaderData(6, Qt::Horizontal, QString("Data da Fundação"));
      auto dialogPesquisar = MitoR::Gui::DialogPesquisarTabela(queryTable);
      //dialogPesquisar->setHidden(false);
      auto res = dialogPesquisar.exec();
      if (!res)
        return MitoR::Erro{MitoR::Erro::Falha, "Nenhum registro selecionado."};
      auto idx = dialogPesquisar.indexSelecionado();
      registroSelecionado = queryTable->record(idx.row());
      _idPessoa = registroSelecionado.value("id").toInt();
      _idPj = registroSelecionado.value("id_pessoa_juridica").toInt();
    } else {
      if (p.next()) {
        registroSelecionado = p.record();
        _idPessoa = registroSelecionado.value("id").toInt();
        _idPj = registroSelecionado.value("id_pessoa_juridica").toInt();
      } else {
        ui->pushButtonLimpar->click();
        return MitoR::Erro{MitoR::Erro::Falha, "Não foi encontrado nenhum registro."};
      }
    }

    if (_idPessoa != 0) {
      this->ui->lineEditNomeFantasia->setText(registroSelecionado.value("nome").toString());
      this->ui->lineEditRazaoSocial->setText(registroSelecionado.value("razao_social").toString());
      this->ui->lineEditCNPJ->clear();
      this->ui->lineEditCNPJ->insert(registroSelecionado.value("cnpj").toString());
      this->ui->lineEditIE->setText(registroSelecionado.value("ie").toString());
      this->ui->dateEditFundacao->setDate(registroSelecionado.value("data_fundacao").toDate());
      // Seleciona caso seja um cliente.
      p.prepare("SELECT * FROM cadastro.clientes WHERE id_pessoa = ?;");
      p.bindValue(0, _idPessoa);
      if (!p.exec()) {
        return MitoR::Erro{MitoR::Erro::Falha, p.lastError().text()};
      }
      if (p.next()) {
        auto registro = p.record();
        _idCliente = p.value("id").toInt();
        this->ui->checkBoxCliente->setChecked(true);
      } else {
        _idCliente = 0;
        this->ui->checkBoxCliente->setChecked(false);
      }
      // Seleciona caso seja um fabricante.
      p.prepare("SELECT * FROM cadastro.fabricantes WHERE id_pessoa = ?;");
      p.bindValue(0, _idPessoa);
      if (!p.exec()) {
        return MitoR::Erro{MitoR::Erro::Falha, p.lastError().text()};
      }
      if (p.next()) {
        auto registro = p.record();
        _idFabricante = p.value("id").toInt();
        this->ui->checkBoxFabricante->setChecked(true);
      } else {
        _idFabricante = 0;
        this->ui->checkBoxFabricante->setChecked(false);
      }
      // Seleciona caso seja um fornecedor.
      p.prepare("SELECT * FROM cadastro.fornecedores WHERE id_pessoa = ?;");
      p.bindValue(0, _idPessoa);
      if (!p.exec()) {
        return MitoR::Erro{MitoR::Erro::Falha, p.lastError().text()};
      }
      if (p.next()) {
        auto registro = p.record();
        _idFornecedor = p.value("id").toInt();
        this->ui->checkBoxFornecedor->setChecked(true);
        int idtipofornecedor = p.value("id_tipo_fornecedor").toInt();
        for (int r = 0; r < this->_tTipoFornecedor->rowCount(); r++) {
          auto idx = this->_tTipoFornecedor->index(r, 0);
          if (idx.data().toInt() == idtipofornecedor) {
            ui->comboBoxTipoFornecedor->setCurrentIndex(idx.row());
          }
        }
      } else {
        _idFornecedor = 0;
        this->ui->checkBoxFornecedor->setChecked(false);
      }

      // Endereço.
      this->atualizarTabelaEndereco();
      if (this->_tEnderecos->rowCount() > 0) {
        this->ui->comboBoxEndereco->setCurrentIndex(0);
      }

      // Contato.
      this->atualizarTabelaContato();
      if (this->_tContatos->rowCount() > 0) {
        this->ui->comboBoxContato->setCurrentIndex(0);
      }
    }
    _estado = Estado::Alteracao;

    return MitoR::Erro{MitoR::Erro::Sucesso, ""};
  }()) {
    case MitoR::Erro::Sucesso: {
      return true;
    } break;
    case MitoR::Erro::Falha: {
      QMessageBox::warning(this, "Pesquisar registro", QString("%1").formatArg(e.msg));
    } break;
  }
  return false;
}

bool FormCadastrarEmpresa::limparFormulario()
{
  this->ui->labelNomeFantasia->setStyleSheet("");
  this->ui->lineEditNomeFantasia->clear();
  this->ui->labelRazaoSocial->setStyleSheet("");
  this->ui->lineEditRazaoSocial->clear();
  this->ui->labelCNPJ->setStyleSheet("");
  this->ui->lineEditCNPJ->clear();
  this->ui->lineEditIE->clear();
  if (this->_tTipoFornecedor->rowCount() > 0)
    this->ui->comboBoxTipoFornecedor->setCurrentIndex(0);

  this->ui->checkBoxCliente->setChecked(false);
  this->ui->checkBoxFabricante->setChecked(false);
  this->ui->checkBoxFornecedor->setChecked(false);

  this->ui->comboBoxEndereco->lineEdit()->setText("FATURAMENTO");
  this->ui->lineEditBairro->clear();
  this->ui->lineEditCEP->clear();
  this->ui->lineEditComplemento->clear();
  this->ui->lineEditLogradouro->clear();
  this->ui->lineEditNumero->clear();
  this->ui->dateEditEndereco->setDate(QDate::currentDate());

  this->ui->comboBoxContato->lineEdit()->setText("TELEFONE FIXO");
  this->ui->lineEditEmail->clear();
  this->ui->lineEditTelefone->clear();
  this->ui->dateEditContato->setDate(QDate::currentDate());
  this->ui->lineEditCargo->clear();

  return true;
}

bool FormCadastrarEmpresa::removerFormulario()
{
  auto bd = _acesso->conexao();
  QSqlQuery p(bd);
  if (_estado != Estado::Alteracao) {
    QMessageBox::warning(this, "Remover registro", "Pesquise um registro para tentar remove-lo.");
    return false;
  }
  QMessageBox pergunta(this);
  pergunta.setIcon(QMessageBox::Question);
  pergunta.setWindowTitle("Remover formulário...");
  pergunta.setText(QString("Deseja realmente remover este registro ?"));
  pergunta.addButton("Sim", QMessageBox::ButtonRole::YesRole);
  auto btNao = pergunta.addButton("Não", QMessageBox::ButtonRole::NoRole);
  pergunta.exec();
  if (btNao == pergunta.clickedButton()) {
    return false;
  }

  switch (MitoR::Erro e = [&]() -> MitoR::Erro {
    if (!bd.transaction()) {
      return MitoR::Erro{MitoR::Erro::Falha, QString("Não foi possível criar uma transação no banco de dados! {}").formatArg(
                                                         bd.lastError().text())};
    }
    if (this->_idFabricante != 0) {
      p.prepare("DELETE FROM cadastro.fabricantes WHERE id = ?;");
      p.bindValue(0, this->_idFabricante);
      if (!p.exec()) {
        return MitoR::Erro{MitoR::Erro::Falha,
                           QString("Não foi possível remover a classificação como fornecedor! {}").formatArg(
                                       p.lastError().text())};
      }
    }
    if (this->_idCliente != 0) {
      p.prepare("DELETE FROM cadastro.clientes WHERE id = ?;");
      p.bindValue(0, this->_idCliente);
      if (!p.exec()) {
        return MitoR::Erro{MitoR::Erro::Falha, QString("Não foi possível remover a classificação como cliente! {}").formatArg(
                                                           p.lastError().text())};
      }
    }
    if (this->_idFornecedor != 0) {
      p.prepare("DELETE FROM cadastro.fornecedores WHERE id = ?;");
      p.bindValue(0, this->_idFornecedor);
      if (!p.exec()) {
        return MitoR::Erro{MitoR::Erro::Falha,
                           QString("Não foi possível remover a classificação como fornecedor! {}").formatArg(
                                       p.lastError().text())};
      }
    }
    p.prepare("DELETE FROM cadastro.pj WHERE id = ?;");
    p.bindValue(0, this->_idPj);
    if (!p.exec()) {
      return MitoR::Erro{MitoR::Erro::Falha, QString("Não foi possível remover a classificação como pj! {}").formatArg(
                                                         p.lastError().text())};
    }
    p.prepare("DELETE FROM cadastro.enderecos WHERE id_pessoa = ?;");
    p.bindValue(0, this->_idPessoa);
    if (!p.exec()) {
      return MitoR::Erro{MitoR::Erro::Falha, QString("Não foi possível deletar todos os endereços desta pessoa! {}").formatArg(
                                                         p.lastError().text())};
    }
    p.prepare("DELETE FROM cadastro.contatos WHERE id_pessoa = ?;");
    p.bindValue(0, this->_idPessoa);
    if (!p.exec()) {
      return MitoR::Erro{MitoR::Erro::Falha, QString("Não foi possível deletar todos os contatos desta pessoa! {}").formatArg(
                                                         p.lastError().text())};
    }
    p.prepare("DELETE FROM cadastro.pessoas WHERE id = ?");
    p.bindValue(0, this->_idPessoa);
    if (!p.exec()) {
      return MitoR::Erro{MitoR::Erro::Falha,
                         QString("Não foi possível remover a pessoa! {}").formatArg(p.lastError().text())};
    }

    if (!bd.commit()) {
      return MitoR::Erro{MitoR::Erro::Falha, QString("Não foi possível efetuar a transação no banco de dados! {}").formatArg(
                                                         bd.lastError().text())};
    }
    ui->pushButtonLimpar->click();

    return MitoR::Erro{MitoR::Erro::Sucesso, ""};
  }()) {
    case MitoR::Erro::Sucesso: {
      return true;
    } break;
    case MitoR::Erro::Falha: {
      if (!bd.rollback()) {
        return MitoR::Erro{MitoR::Erro::Falha,
                           QString("Não foi possível rebobinar a transação no banco de dados! {}").formatArg(
                                       bd.lastError().text())};
      }
      QMessageBox::warning(this, "Remover registro", QString("%1").formatArg(e.msg));
    } break;
  }
  return false;
}

bool FormCadastrarEmpresa::validarPJ()
{
  static QRegularExpression expressaoNomes("^\\w( ?[\\w\\d.,-_&]+)+");
  static QRegularExpression expressaoNumerica("^\\d\\d+");
  static QRegularExpressionValidator *validacaoNomes = new QRegularExpressionValidator(expressaoNomes, this);
  static QRegularExpressionValidator *validacaoNumerica = new QRegularExpressionValidator(expressaoNumerica, this);
  static QString texto;
  static int nPos = 0;

  texto = ui->lineEditNomeFantasia->text();
  nPos = 0;
  if (validacaoNomes->validate(texto, nPos) != QValidator::State::Acceptable) {
    QMessageBox::warning(this, "Salvar", QString::fromUtf8("O nome fantasia digitado está inválido. Verifique a sintaxe.\nObs: Um nome não pode começar com espaço ou terminar com espaço."));
    return false;
  }
  texto = ui->lineEditRazaoSocial->text();
  nPos = 0;
  if (validacaoNomes->validate(texto, nPos) != QValidator::State::Acceptable) {
    QMessageBox::warning(this, "Salvar", QString::fromUtf8("A razão social digitada está inválida. Verifique a sintaxe.\nObs: Um nome não pode começar com espaço ou terminar com espaço."));
    return false;
  }
  texto = ui->lineEditCNPJ->text().remove(QRegularExpression("[-,./]"));
  if (!validarCNPJ(texto)) {
    QMessageBox::warning(this, "Salvar", QString::fromUtf8("O CNPJ digitado é inválido."));
    return false;
  }
  texto = ui->lineEditIE->text().remove(QRegularExpression("[-,./]"));
  if (!validacaoNumerica->validate(texto, nPos)) {
    QMessageBox::warning(this, "Salvar", QString::fromUtf8("A IE digitada é inválida."));
    return false;
  }
  if (!ui->checkBoxCliente->isChecked() && !ui->checkBoxFabricante->isChecked() && !ui->checkBoxFornecedor->isChecked()) {
    QMessageBox::warning(this, "Salvar", QString::fromUtf8("Escolha uma classificação para o cadastro."));
    return false;
  }

  return true;
}

bool FormCadastrarEmpresa::validarEndereco()
{
  if (ui->comboBoxEndereco->currentText().isEmpty()) {
    QMessageBox::warning(this, "Endereços", "O campo que identifica um endereço não pode estar vazio.");
    return false;
  }
  if (ui->lineEditLogradouro->text().isEmpty()) {
    QMessageBox::warning(this, "Endereços", "O campo logradouro não pode estar vazio.");
    return false;
  }
  if (ui->comboBoxPais->currentIndex() < 0) {
    QMessageBox::warning(this, "Endereços", "Selecione um país.");
    return false;
  }
  if (ui->comboBoxEstado->currentIndex() < 0) {
    QMessageBox::warning(this, "Endereços", "Selecione um estado.");
    return false;
  }
  if (ui->comboBoxCidade->currentIndex() < 0) {
    QMessageBox::warning(this, "Endereços", "Selecione uma cidade.");
    return false;
  }
  return true;
}

bool FormCadastrarEmpresa::validarContato()
{
  if (this->ui->comboBoxContato->currentText().isEmpty()) {
    QMessageBox::warning(this, "Contatos", "O campo de identificação de um contato não pode estar vazio.");
    return false;
  }
  return true;
}

void FormCadastrarEmpresa::keyPressEvent(QKeyEvent *ev)
{
  if (ev->type() == QEvent::KeyPress) {
    if (ev->key() == Qt::Key_Escape) {
      ev->ignore();
      return;
    }
  }
  ev->accept();
}
