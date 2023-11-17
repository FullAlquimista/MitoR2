//
// Created by Robson on 01/01/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_FormCadastrarTiposMateriais.h" resolved

#include "formcadastrartipospropostas.hpp"
#include "ui_formcadastrartipospropostas.h"
#include <QtCore>
#include <QtGui>
#include <spdlog/spdlog.h>

FormCadastrarTiposPropostas::FormCadastrarTiposPropostas(QWidget *parent) : QWidget(parent), ui(new Ui::FormCadastrarTiposPropostas)
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
  m_model->setTable("producao.tipos_propostas");
  if(m_model->lastError().isValid()) {
    QMessageBox::warning(this, this->objectName(), QString("Falha ao carregar a tabela.\n%1").formatArg(m_model->lastError().text()));
    return;
  }
  m_model->setHeaderData(0, Qt::Horizontal, QString("ID"));
  m_model->setHeaderData(1, Qt::Horizontal, QString("Descrição"));
  m_model->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
  m_model->select();
  
  ui->tableView->setModel(m_model);

  QObject::connect(ui->pushButtonAdicionar, &QPushButton::clicked, this, &FormCadastrarTiposPropostas::novo);
  QObject::connect(ui->pushButtonSalvar, &QPushButton::clicked, this, &FormCadastrarTiposPropostas::salvar);
  QObject::connect(ui->pushButtonRemover, &QPushButton::clicked, this, &FormCadastrarTiposPropostas::remover);
}

FormCadastrarTiposPropostas::~FormCadastrarTiposPropostas()
{
  delete ui;
}
void FormCadastrarTiposPropostas::novo()
{
  int linha = m_model->rowCount();
  if(m_model->insertRow(linha)) {
    ui->tableView->setCurrentIndex(m_model->index(linha, 0));
  }
}
void FormCadastrarTiposPropostas::salvar()
{
  m_model->submitAll();
}
void FormCadastrarTiposPropostas::remover()
{
  auto selectionModel = ui->tableView->selectionModel();
  int linha = selectionModel->currentIndex().row();
  if(selectionModel->currentIndex().isValid()) {
    m_model->removeRow(linha);
  }
}
