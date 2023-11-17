//
// Created by Robson on 15/01/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_FormCadastrarMateriais.h" resolved

#include "formcadastrarmateriais.hpp"
#include "ui_FormCadastrarMateriais.h"
#include <mitor/gui/eventfiltermudancafocus.hpp>
#include <mitor/gui/dialogpesquisartabela.hpp>
#include <mitor/gui/dialogpesquisarct.hpp>
#include <mitor/gui/keyeventfilter.hpp>
#include <spdlog/spdlog.h>

FormCadastrarMateriais::FormCadastrarMateriais(QWidget *parent) : QWidget(parent), ui(new Ui::FormCadastrarMateriais)
{
  ui->setupUi(this);
  ui->pushButtonSelecionarClassificacao->setIcon(QApplication::style()->standardIcon(QStyle::SP_FileDialogDetailedView));
  ui->pushButtonSelecionarPlanoConta->setIcon(QApplication::style()->standardIcon(QStyle::SP_FileDialogDetailedView));
  ui->pushButtonCUp->setIcon(QApplication::style()->standardIcon(QStyle::SP_ArrowUp));
  ui->pushButtonCDown->setIcon(QApplication::style()->standardIcon(QStyle::SP_ArrowDown));
  ui->pushButtonPUp->setIcon(QApplication::style()->standardIcon(QStyle::SP_ArrowUp));
  ui->pushButtonPDown->setIcon(QApplication::style()->standardIcon(QStyle::SP_ArrowDown));
  
  auto app = QApplication::instance();
  _acesso = app->findChild<Sessao::IAcesso*>();
  if(!_acesso) {
    QMessageBox::warning(this, this->objectName(), "Falha ao obter os objetos dos módulos Acesso.");
    return;
  }
  
  carregarTabelas();
  
  ui->spinBoxIdMaterial->installEventFilter(new MitoR::Gui::EventFilterMudancaFocus(nullptr, [this](QEvent *) {
        mudarIndexMaterial(m_idxMaterial);
      }, ui->spinBoxIdMaterial));
  ui->spinBoxIdMaterial->installEventFilter(new MitoR::Gui::CallbackEventFilter([this](QObject *, QEvent *evento) {
    auto keyEvent = static_cast<QKeyEvent*>(evento);
    if(keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
      procurarIdMaterial(ui->spinBoxIdMaterial->value());
      return true;
    }
    return false;
  }, ui->spinBoxIdMaterial));
  
  // Classificações de materiais:
  QObject::connect(ui->pushButtonCUp, &QPushButton::clicked, this, [this](bool) {
    mudarIndexClassificacao(m_tClassificacoes->index(m_idxClassificacao.row() - 1, 0));
  });
  QObject::connect(ui->pushButtonCDown, &QPushButton::clicked, this, [this](bool) {
    mudarIndexClassificacao(m_tClassificacoes->index(m_idxClassificacao.row() + 1, 0));
  });
  QObject::connect(ui->lineEditIdClassificacao, &QLineEdit::returnPressed, this, [this]() {
    procurarIdClassificacao(ui->lineEditIdClassificacao->text().toInteger<int>());
  });
  auto evIdClassificacao = new MitoR::Gui::EventFilterMudancaFocus(nullptr, [this](QEvent *) {
        mudarIndexClassificacao(m_idxClassificacao);
      }, ui->lineEditIdClassificacao);
  ui->lineEditIdClassificacao->installEventFilter(evIdClassificacao);
  QObject::connect(ui->pushButtonSelecionarClassificacao, &QPushButton::clicked, this, &FormCadastrarMateriais::selecionarIdClassificacao);
  
  // Planos de contas:
  QObject::connect(ui->pushButtonPUp, &QPushButton::clicked, this, [this](bool) {
    mudarIndexPlanoConta(m_tPlanoConta->index(m_idxPlanoConta.row() - 1, 0));
  });
  QObject::connect(ui->pushButtonPDown, &QPushButton::clicked, this, [this](bool) {
    mudarIndexPlanoConta(m_tPlanoConta->index(m_idxPlanoConta.row() + 1, 0));
  });
  QObject::connect(ui->lineEditIdPlanoConta, &QLineEdit::returnPressed, this, [this]() {
    procurarIdPlanoConta(ui->lineEditIdPlanoConta->text().toInteger<int>());
  });
  auto evIdPlanoConta = new MitoR::Gui::EventFilterMudancaFocus(nullptr, [this](QEvent *) {
        mudarIndexPlanoConta(m_idxPlanoConta);
      }, ui->lineEditIdClassificacao);
  ui->lineEditIdPlanoConta->installEventFilter(evIdPlanoConta);
  QObject::connect(ui->pushButtonSelecionarPlanoConta, &QPushButton::clicked, this, [this](bool) {
    auto dialog = new MitoR::Gui::DialogPesquisarCT(m_tPlanoConta);
    if(dialog->exec() == dialog->Accepted) {
      auto index = dialog->indexSelecionado();
      mudarIndexPlanoConta(index);
    }
    dialog->deleteLater();
  });
  
  ui->comboBoxUnidadeEstoque->setModel(m_tMateriais->relationModel(2));
  ui->comboBoxUnidadeEstoque->setModelColumn(2);
  ui->comboBoxUnidadeComercial->setModel(m_tMateriais->relationModel(3));
  ui->comboBoxUnidadeComercial->setModelColumn(2);
  
  auto evDescricaoMaterial = new MitoR::Gui::EventFilterMudancaFocus([this](QEvent *) {
    m_wPesquisa = ui->lineEditDescricaoMaterial;
    ui->labelDescricaoMaterial->setStyleSheet("font-weight: bold");
  }, nullptr, ui->lineEditDescricaoMaterial);
  ui->lineEditDescricaoMaterial->installEventFilter(evDescricaoMaterial);
  
  ui->tableView->setModel(m_tFracionaveis);
  ui->tableView->setItemDelegateForColumn(2, new QSqlRelationalDelegate(ui->tableView));
  ui->tableView->setItemDelegateForColumn(3, new QSqlRelationalDelegate(ui->tableView));
  ui->tableView->setItemDelegateForColumn(10, new QSqlRelationalDelegate(ui->tableView));
  //ui->tableView->setColumnHidden(0, true);
  ui->tableView->setColumnHidden(1, true);
  
  QObject::connect(ui->pushButtonNovoFormulario, &QPushButton::clicked, this, &FormCadastrarMateriais::novoFormulario);
  QObject::connect(ui->pushButtonSalvarFormulario, &QPushButton::clicked, this, &FormCadastrarMateriais::salvarFormulario);
  QObject::connect(ui->pushButtonPesquisarFormulario, &QPushButton::clicked, this, &FormCadastrarMateriais::pesquisarFormulario);
  QObject::connect(ui->pushButtonLimparFormulario, &QPushButton::clicked, this, &FormCadastrarMateriais::limparFormulario);
  QObject::connect(ui->pushButtonRemoverFormulario, &QPushButton::clicked, this, &FormCadastrarMateriais::removerFormulario);
  
  QObject::connect(ui->pushButtonAdicionarRegistro, &QPushButton::clicked, this, &FormCadastrarMateriais::adicionar);
  QObject::connect(ui->pushButtonGravarRegistro, &QPushButton::clicked, this, &FormCadastrarMateriais::gravar);
  QObject::connect(ui->pushButtonExcluirRegistro, &QPushButton::clicked, this, &FormCadastrarMateriais::excluir);
}

FormCadastrarMateriais::~FormCadastrarMateriais()
{
  delete ui;
}
void FormCadastrarMateriais::carregarTabelas()
{
  m_tMateriais = new QSqlRelationalTableModel(this, _acesso->conexao());
  m_tMateriais->setTable("cadastro.materiais");
  if(m_tMateriais->lastError().isValid()) {
    QMessageBox::warning(this, this->objectName(), QString("Falha ao carregar a tabela.\n%1").formatArg(m_tMateriais->lastError().text()));
    return;
  }
  m_tMateriais->setRelation(2, QSqlRelation("cadastro.unidades_medidas", "id", "descricao"));
  m_tMateriais->setRelation(3, m_tMateriais->relation(2));
  m_tMateriais->setEditStrategy(QSqlTableModel::OnManualSubmit);
  m_tMateriais->select();
  
  m_tClassificacoes = new QSqlTableModel(this, _acesso->conexao());
  m_tClassificacoes->setTable("cadastro.classificacoes_materiais");
  if(m_tClassificacoes->lastError().isValid()) {
    QMessageBox::warning(this, this->objectName(), QString("Falha ao carregar a tabela.\n%1").formatArg(m_tClassificacoes->lastError().text()));
    return;
  }
  m_tClassificacoes->select();
  mudarIndexClassificacao(m_tClassificacoes->index(0, 0));
  
  m_tPlanoConta = new QSqlTableModel(this, _acesso->conexao());
  m_tPlanoConta->setTable("cadastro.planos_contas");
  if(m_tPlanoConta->lastError().isValid()) {
    QMessageBox::warning(this, this->objectName(), QString("Falha ao carregar a tabela.\n%1").formatArg(m_tPlanoConta->lastError().text()));
    return;
  }
  m_tPlanoConta->select();
  mudarIndexPlanoConta(m_tPlanoConta->index(0, 0));
  
  m_tFracionaveis = new QSqlRelationalTableModel(this, _acesso->conexao());
  m_tFracionaveis->setTable("cadastro.materiais_fracionaveis");
  if(m_tFracionaveis->lastError().isValid()) {
    QMessageBox::warning(this, this->objectName(), QString("Falha ao carregar a tabela.\n%1").formatArg(m_tFracionaveis->lastError().text()));
    return;
  }
  m_tFracionaveis->setRelation(2, QSqlRelation("cadastro.tipos_materiais", "id", "material"));
  m_tFracionaveis->setRelation(3, QSqlRelation("cadastro.formatos_materiais", "id", "descricao"));
  m_tFracionaveis->setRelation(10, QSqlRelation("cadastro.unidades_medidas", "id", "abreviacao"));
  m_tFracionaveis->setHeaderData(0, Qt::Horizontal, QString("ID"));
  m_tFracionaveis->setHeaderData(1, Qt::Horizontal, QString("ID do Material"));
  m_tFracionaveis->setHeaderData(2, Qt::Horizontal, QString("Tipo do material"));
  m_tFracionaveis->setHeaderData(3, Qt::Horizontal, QString("Formato do material"));
  m_tFracionaveis->setHeaderData(4, Qt::Horizontal, QString("D1"));
  m_tFracionaveis->setHeaderData(5, Qt::Horizontal, QString("D2"));
  m_tFracionaveis->setHeaderData(6, Qt::Horizontal, QString("D3"));
  m_tFracionaveis->setHeaderData(7, Qt::Horizontal, QString("D4"));
  m_tFracionaveis->setHeaderData(8, Qt::Horizontal, QString("D5"));
  m_tFracionaveis->setHeaderData(9, Qt::Horizontal, QString("Peso"));
  m_tFracionaveis->setHeaderData(10, Qt::Horizontal, QString("Unidade Peso"));
  m_tFracionaveis->setEditStrategy(QSqlTableModel::OnManualSubmit);
  m_tFracionaveis->select();
  m_tFracionaveis->setFilter("id_material = 0");
}
void FormCadastrarMateriais::mudarIndexClassificacao(QModelIndex idx)
{
  auto idxId = m_tClassificacoes->index(idx.row(), 0);
  if(idxId == QModelIndex())
    return;
  auto idxDescricao = m_tClassificacoes->index(idx.row(), 1);
  if(idxDescricao == QModelIndex())
    return;
  m_idxClassificacao = idxId;
  ui->lineEditIdClassificacao->setText(QString("%1").formatArg(idxId.data(Qt::DisplayRole).toInt()));
  ui->lineEditDescricaoClassificacao->setText(idxDescricao.data(Qt::DisplayRole).toString());
}
void FormCadastrarMateriais::mudarIndexPlanoConta(QModelIndex idx)
{
  auto idxId = m_tPlanoConta->index(idx.row(), 0);
  if(idxId == QModelIndex())
    return;
  auto idxDescricao = m_tPlanoConta->index(idx.row(), 1);
  if(idxDescricao == QModelIndex())
    return;
  m_idxPlanoConta = idxId;
  ui->lineEditIdPlanoConta->setText(QString("%1").formatArg(idxId.data(Qt::DisplayRole).toInt()));
  ui->lineEditDescricaoPlanoConta->setText(idxDescricao.data(Qt::DisplayRole).toString());
}
void FormCadastrarMateriais::procurarIdClassificacao(int id)
{
  for(auto r=0, max=m_tClassificacoes->rowCount(); r < max; ++r) {
    auto idxId = m_tClassificacoes->index(r, 0);
    if(idxId.data().toInt() == id) {
      mudarIndexClassificacao(idxId);
      return;
    }
  }
}
void FormCadastrarMateriais::procurarIdPlanoConta(int id)
{
  for(auto r=0, max=m_tPlanoConta->rowCount(); r < max; ++r) {
    auto idxId = m_tPlanoConta->index(r, 0);
    if(idxId.data().toInt() == id) {
      mudarIndexPlanoConta(idxId);
      return;
    }
  }
}
void FormCadastrarMateriais::mudarIndexMaterial(QModelIndex idx)
{
  auto idxId = m_tMateriais->index(idx.row(), 0);
  if(idxId == QModelIndex())
    return;
  auto idxDescricao = m_tMateriais->index(idx.row(), 1);
  if(idxDescricao == QModelIndex())
    return;
  m_idxMaterial = idxId;
  ui->spinBoxIdMaterial->setValue(idxId.data().toInt());
  ui->lineEditDescricaoMaterial->setText(idxDescricao.data().toString());
}
void FormCadastrarMateriais::novoFormulario()
{
  // Não faz nada caso já esteja editando ou adicionando um registro.
  if(obterRoleIdxMaterial(Roles::NovoItem)) {
    QMessageBox::warning(this, "Novo formulário...", "Para adicionar um novo registro, você deve primeiro limpar o formulário atual.");
    return;
  }
  auto linhaAtual = m_tMateriais->rowCount();
  if(!m_tMateriais->insertRow(linhaAtual)) {
    QMessageBox::warning(this, "Novo formulário...", QString("Falha ao inserir um novo registro.\n%1").formatArg(m_tMateriais->lastError().text()));
  }
  mudarIndexMaterial(m_tMateriais->index(linhaAtual, 0));
  spdlog::info("RowCount: {}", m_tMateriais->rowCount());
  inserirRoleIdxMaterial(true, Roles::NovoItem);
}
void FormCadastrarMateriais::pesquisarFormulario()
{
  if(!limparFormulario())
    return;
  auto lineEditDescricao = dynamic_cast<QLineEdit*>(m_wPesquisa);
  if(lineEditDescricao) {
    m_tMateriais->setFilter(QString("cadastro.materiais.descricao LIKE '%%1%'").formatArg(ui->lineEditDescricaoMaterial->text()));
    m_tMateriais->select();
    if(m_tMateriais->lastError().isValid()) {
      QMessageBox::warning(this, "Pesquisar...", QString("Falha ao efetuar a pesquisa.\n%1").formatArg(m_tMateriais->lastError().text()));
      return;
    }
    if(m_tMateriais->rowCount() > 1) {
      auto dialog = new MitoR::Gui::DialogPesquisarTabela(m_tMateriais, this);
      auto res = dialog->exec();
      if(res == dialog->Accepted) {
        mudarIndexMaterial(dialog->indexSelecionado());
        auto idxIdClassificacao = m_tMateriais->index(dialog->indexSelecionado().row(), 4);
        auto idxIdPlanoConta = m_tMateriais->index(dialog->indexSelecionado().row(), 5);
        procurarIdClassificacao(idxIdClassificacao.data().toInt());
        procurarIdPlanoConta(idxIdPlanoConta.data().toInt());
        auto idMaterial = m_tMateriais->index(dialog->indexSelecionado().row(), 0).data().toInt();
        m_tFracionaveis->setFilter(QString("id_material = %1").formatArg(idMaterial));
        inserirRoleIdxMaterial(true, Roles::ItemEdicao);
      }
    }else if (m_tMateriais->rowCount() == 1) {
      auto indexSelecionado = m_tMateriais->index(0, 0);
      mudarIndexMaterial(indexSelecionado);
      auto idxIdClassificacao = m_tMateriais->index(indexSelecionado.row(), 4);
      auto idxIdPlanoConta = m_tMateriais->index(indexSelecionado.row(), 5);
      procurarIdClassificacao(idxIdClassificacao.data().toInt());
      procurarIdPlanoConta(idxIdPlanoConta.data().toInt());
      auto idMaterial = m_tMateriais->index(indexSelecionado.row(), 0).data().toInt();
      m_tFracionaveis->setFilter(QString("id_material = %1").formatArg(idMaterial));
      inserirRoleIdxMaterial(true, Roles::ItemEdicao);
    }else {
      QMessageBox::warning(this, "Pesquisa de um material...", "Nenhum material foi encontrado com está descrição.");
    }
  }
}
void FormCadastrarMateriais::salvarFormulario()
{
  if(obterRoleIdxMaterial(Roles::NovoItem) || obterRoleIdxMaterial(Roles::ItemEdicao) || obterRoleIdxMaterial(Roles::ItemEditado)) {
    auto res = QMessageBox::question(this, "Salvar formulário...", "Você realmente deseja salvar as alterações ?", "Sim", "Não");
    if(res == 1)
      return;
    auto lReg = m_idxMaterial.row();
    m_tMateriais->setData(m_tMateriais->index(lReg, 1), ui->lineEditDescricaoMaterial->text().toUpper());
    int idEstoque = ui->comboBoxUnidadeEstoque->model()->data(ui->comboBoxUnidadeEstoque->model()->index(ui->comboBoxUnidadeEstoque->currentIndex(), 0)).toInt();
    m_tMateriais->setData(m_tMateriais->index(lReg, 2), idEstoque);
    int idComercial = ui->comboBoxUnidadeComercial->model()->data(ui->comboBoxUnidadeComercial->model()->index(ui->comboBoxUnidadeComercial->currentIndex(), 0)).toInt();
    m_tMateriais->setData(m_tMateriais->index(lReg, 3), idComercial);
    m_tMateriais->setData(m_tMateriais->index(lReg, 4), ui->lineEditIdClassificacao->text().toInteger<int>());
    m_tMateriais->setData(m_tMateriais->index(lReg, 5), ui->lineEditIdPlanoConta->text().toInteger<int>());
    m_tMateriais->submitAll();
    if(m_tMateriais->lastError().isValid()) {
      QMessageBox::warning(this, "Salvar formulário.", QString("Erro ao tentar salvar a tabela de materiais.\n%1").formatArg(m_tMateriais->lastError().text()));
      return;
    }
    if(m_tFracionaveis->rowCount() < 1)
      return;
    m_tFracionaveis->submitAll();
    if(m_tFracionaveis->lastError().isValid()) {
      QMessageBox::warning(this, "Salvar formulário.", QString("Erro ao tentar salvar a tabela de fracionável.\n%1").formatArg(m_tFracionaveis->lastError().text()));
      return;
    }
  }else if(obterRoleIdxMaterial(Roles::RemoverItem)) {
  }
}
bool FormCadastrarMateriais::limparFormulario()
{
  bool novoItem = obterRoleIdxMaterial(Roles::NovoItem);
  if(novoItem) {
    auto res = QMessageBox::question(this, "Limpar formulário...", "Um novo registro está em andamento. Deseja cancelar inserção ?", "Sim", "Não");
    if(res == 1)
      return false;
  }
  bool itemEditado = obterRoleIdxMaterial(Roles::ItemEditado);
  bool itemEdicao = obterRoleIdxMaterial(Roles::ItemEdicao);
  if(itemEditado || itemEdicao) {
    auto res = QMessageBox::question(this, "Limpar formulário...", "Uma alteração do registro está em andamento. Deseja cancelar alteração ?", "Sim", "Não");
    if(res == 1)
      return false;
  }
  bool removerItem = obterRoleIdxMaterial(Roles::RemoverItem);
  if(removerItem) {
    auto res = QMessageBox::question(this, "Limpar formulário...", "Uma remoção de um registro está em andamento. Deseja cancelar remoção ?", "Sim", "Não");
    if(res == 1)
      return false;
  }
  inserirRoleIdxMaterial(false, Roles::NovoItem);
  inserirRoleIdxMaterial(false, Roles::ItemEditado);
  inserirRoleIdxMaterial(false, Roles::ItemEdicao);
  inserirRoleIdxMaterial(false, Roles::RemoverItem);
  m_tMateriais->revertAll();
  m_idxMaterial = QModelIndex();
  m_tFracionaveis->revertAll();
  m_idxFracionavel = QModelIndex();
  ui->spinBoxIdMaterial->setValue(0);
  ui->lineEditDescricaoMaterial->clear();
  m_tFracionaveis->setFilter("id_material = 0");
  
  return true;
}
void FormCadastrarMateriais::removerFormulario()
{
  if(!obterRoleIdxMaterial(Roles::NovoItem) && !obterRoleIdxMaterial(Roles::ItemEdicao))
    return;
  if(m_idxMaterial == QModelIndex()) {
    return;
  }
  auto res = QMessageBox::question(this, "Remover formulário...", "Você realmente deseja remover este cadastro ?", "Sim", "Não");
  if(res == 1)
    return;
  m_tFracionaveis->removeRow(m_idxFracionavel.row());
  m_tFracionaveis->submitAll();
  m_tMateriais->removeRow(m_idxMaterial.row());
  m_tMateriais->submitAll();
  limparFormulario();
}
void FormCadastrarMateriais::adicionar()
{
  if(!obterRoleIdxMaterial(Roles::NovoItem) && !obterRoleIdxMaterial(Roles::ItemEdicao)) {
    QMessageBox::warning(this, "Adicionar item fracionável...", "Só pode adicionar um novo registro fracionável quando o material já estiver cadastrado.\nCadastre o material primeiro salvando o formulário.");
    return;
  }
  if(m_tFracionaveis->rowCount() > 0) {
    QMessageBox::warning(this, "Adicionar item fracionável...", "Por enquanto somente um registro de um material fracionável pode ser adicionado.");
    return;
  }
  auto linhaAtual = m_tFracionaveis->rowCount();
  m_tFracionaveis->insertRow(linhaAtual);
  m_idxFracionavel = m_tFracionaveis->index(linhaAtual, 0);
  m_tFracionaveis->setData(m_tFracionaveis->index(m_idxFracionavel.row(), 1), m_tMateriais->index(m_idxMaterial.row(), 0).data());
  ui->tableView->setCurrentIndex(m_idxFracionavel);
}
void FormCadastrarMateriais::gravar()
{
  m_tFracionaveis->submitAll();
  if(m_tFracionaveis->lastError().isValid()) {
    QMessageBox::warning(this, "Gravar registro...", QString("Erro ao tentar gravar o registro na tabela de fracionáveis.\n%1").formatArg(m_tFracionaveis->lastError().text()));
    return;
  }
}
void FormCadastrarMateriais::excluir()
{
  auto selectionModel = ui->tableView->selectionModel();
  auto idxSelecionado = m_tFracionaveis->index(selectionModel->currentIndex().row(), 0);
  if(idxSelecionado == QModelIndex()) {
    return;
  }
  m_tFracionaveis->removeRow(idxSelecionado.row());
}
bool FormCadastrarMateriais::obterRoleIdxMaterial(const Roles role)
{
  if(m_rolesIdxMaterial.contains(role))
    return m_rolesIdxMaterial[role].toBool();
  return false;
}
void FormCadastrarMateriais::inserirRoleIdxMaterial(const bool v, const Roles role)
{
  m_rolesIdxMaterial[role] = v;
}
void FormCadastrarMateriais::procurarIdMaterial(int id)
{
  m_tMateriais->setFilter(QString("cadastro.materiais.id = %1").formatArg(id));
  if(m_tMateriais->lastError().isValid()) {
    QMessageBox::warning(this, "Procurando id do material...", QString("Falha ao pesquisar o id deste material.\n%1").formatArg(m_tMateriais->lastError().text()));
    return;
  }
  if(m_tMateriais->rowCount() < 1) {
    QMessageBox::warning(this, "Procurando id do material...", QString("Não foi encontrado nenhum material com este id."));
    return;
  }
  auto idx = m_tMateriais->index(0, 0);
  mudarIndexMaterial(idx);
  auto idxIdClassificacao = m_tMateriais->index(idx.row(), 4);
  auto idxIdPlanoConta = m_tMateriais->index(idx.row(), 5);
  procurarIdClassificacao(idxIdClassificacao.data().toInt());
  procurarIdPlanoConta(idxIdPlanoConta.data().toInt());
  
  auto idMaterial = m_tMateriais->index(idx.row(), 0).data().toInt();
  m_tFracionaveis->setFilter(QString("id_material = %1").formatArg(idMaterial));
  inserirRoleIdxMaterial(true, Roles::ItemEdicao);
}
void FormCadastrarMateriais::selecionarIdClassificacao()
{
  auto dialog = new MitoR::Gui::DialogPesquisarCT(m_tClassificacoes);
  if(dialog->exec() == dialog->Accepted) {
    auto index = dialog->indexSelecionado();
    mudarIndexClassificacao(index);
    if(obterRoleIdxMaterial(Roles::NovoItem) && ui->lineEditDescricaoMaterial->text().isEmpty()) {
      auto idClassificacao = m_idxClassificacao.data().toInt();
      QSqlQuery p(_acesso->conexao());
      if (p.exec(QString(R"(
                                      SELECT * FROM cadastro.classificacoes_materiais_ct ct, cadastro.classificacoes_materiais c
                                        WHERE ct.id_no = c.id AND id_item = %1 AND nomear > 0
                                        ORDER BY id_item, nivel;)").formatArg(idClassificacao))) {
        QString descricao;
        bool umaVez = true;
        while (p.next()) {
          auto reg = p.record();
          if(!umaVez)
            descricao.append(" ");
          descricao.append(QString("%1").formatArg(reg.value("descricao").toString()));
          umaVez = false;
        }
        ui->lineEditDescricaoMaterial->setText(descricao);
      }
    }
  }
  dialog->deleteLater();
}
