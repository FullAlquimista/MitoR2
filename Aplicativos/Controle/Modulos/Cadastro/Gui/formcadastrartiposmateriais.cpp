//
// Created by Robson on 01/01/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_FormCadastrarTiposMateriais.h" resolved

#include "formcadastrartiposmateriais.hpp"
#include "ui_FormCadastrarTiposMateriais.h"
#include <QtCore>
#include <QtGui>
#include <spdlog/spdlog.h>

FormCadastrarTiposMateriais::FormCadastrarTiposMateriais(QWidget *parent) : QWidget(parent), ui(new Ui::FormCadastrarTiposMateriais)
{
  ui->setupUi(this);
  
  // Carregando modulos acesso e sessao.
  auto app = QApplication::instance();
  _acesso = app->findChild<Sessao::IAcesso*>();
  if(!_acesso) {
    spdlog::warn("Falha ao carregar os serviços da sessão.");
    return;
  }
  
  m_model = new QSqlRelationalTableModel(this, _acesso->conexao());
  m_model->setTable("cadastro.tipos_materiais");
  if(m_model->lastError().isValid()) {
    QMessageBox::warning(this, this->objectName(), QString("Falha ao carregar a tabela.\n%1").formatArg(m_model->lastError().text()));
    return;
  }
  m_model->setHeaderData(0, Qt::Horizontal, QString("ID"));
  m_model->setHeaderData(1, Qt::Horizontal, QString("Material"));
  m_model->setHeaderData(2, Qt::Horizontal, QString("Peso Especifico"));
  m_model->setHeaderData(3, Qt::Horizontal, QString("Unidade Estoque"));
  m_model->setRelation(3, {"cadastro.unidades_medidas", "id", "abreviacao"});
  if(m_model->relationModel(3)->lastError().isValid()){
    QMessageBox::warning(this, this->objectName(), QString("Falha ao carregar a tabela.\n%1").formatArg(m_model->lastError().text()));
    return;
  }
  m_model->setHeaderData(4, Qt::Horizontal, QString("Unidade Compra"));
  m_model->setRelation(4, {"cadastro.unidades_medidas", "id", "abreviacao"});
  if(m_model->relationModel(4)->lastError().isValid()){
    QMessageBox::warning(this, this->objectName(), QString("Falha ao carregar a tabela.\n%1").formatArg(m_model->lastError().text()));
    return;
  }
  m_model->setHeaderData(5, Qt::Horizontal, QString("Plano de contas"));
  m_model->setRelation(5, {"cadastro.planos_contas", "id", "descricao"});
  m_model->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
  m_model->select();
  
  ui->tableView->setModel(m_model);
  ui->tableView->setItemDelegateForColumn(5, new QSqlRelationalDelegate(m_model));
  ui->tableView->setItemDelegateForColumn(4, new QSqlRelationalDelegate(m_model));
  ui->tableView->setItemDelegateForColumn(3, new QSqlRelationalDelegate(m_model));

  QObject::connect(ui->pushButtonAdicionar, &QPushButton::clicked, this, &FormCadastrarTiposMateriais::novo);
  QObject::connect(ui->pushButtonSalvar, &QPushButton::clicked, this, &FormCadastrarTiposMateriais::salvar);
  QObject::connect(ui->pushButtonRemover, &QPushButton::clicked, this, &FormCadastrarTiposMateriais::remover);
}

FormCadastrarTiposMateriais::~FormCadastrarTiposMateriais()
{
  delete ui;
}
void FormCadastrarTiposMateriais::novo()
{
  int linha = m_model->rowCount();
  if(m_model->insertRow(linha)) {
    ui->tableView->setCurrentIndex(m_model->index(linha, 0));
  }
}
void FormCadastrarTiposMateriais::salvar()
{
  m_model->submitAll();
}
void FormCadastrarTiposMateriais::remover()
{
  auto selectionModel = ui->tableView->selectionModel();
  int linha = selectionModel->currentIndex().row();
  if(selectionModel->currentIndex().isValid()) {
    m_model->removeRow(linha);
  }
}
