//
// Created by Robson on 14/01/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_FormCadastrarFormatoMateriais.h" resolved

#include "formcadastrarformatomateriais.hpp"
#include "ui_FormCadastrarFormatoMateriais.h"

FormCadastrarFormatoMateriais::FormCadastrarFormatoMateriais(QWidget *parent) : QWidget(parent), ui(new Ui::FormCadastrarFormatoMateriais)
{
  ui->setupUi(this);
  // Carregar módulos.
  auto app = QApplication::instance();
  _acesso = app->findChild<Sessao::IAcesso*>();
  if(!_acesso) {
    QMessageBox::warning(this, this->objectName(), "Falha ao carregar os serviços");
    return;
  }
  
  // Carrega a tabela de formato de materiais.
  m_model = new QSqlTableModel(this, _acesso->conexao());
  m_model->setTable("cadastro.formatos_materiais");
  if(m_model->lastError().isValid()) {
    QMessageBox::warning(this, "Cadastro de formato de materiais...", QString("Falha ao carregar a tabela.\n%1").formatArg(m_model->lastError().text()));
    return;
  }
  m_model->setHeaderData(0, Qt::Horizontal, QString("Id"));
  m_model->setHeaderData(1, Qt::Horizontal, QString("Descrição"));
  m_model->setHeaderData(2, Qt::Horizontal, QString("Formula de cálculo do peso"));
  m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
  m_model->select();
  
  ui->tableView->setModel(m_model);
  ui->tableView->resizeColumnsToContents();
  
  QObject::connect(ui->pushButtonAdicionar, &QPushButton::clicked, this, &FormCadastrarFormatoMateriais::novo);
  QObject::connect(ui->pushButtonSalvar, &QPushButton::clicked, this, &FormCadastrarFormatoMateriais::salvar);
  QObject::connect(ui->pushButtonRemover, &QPushButton::clicked, this, &FormCadastrarFormatoMateriais::remover);
}

FormCadastrarFormatoMateriais::~FormCadastrarFormatoMateriais()
{
  delete ui;
}
void FormCadastrarFormatoMateriais::novo()
{
  int linha = m_model->rowCount();
  m_model->insertRow(linha);
  auto indexColuna1 = m_model->index(linha, 1);
  m_model->setData(indexColuna1, QString("Novo"));
}
void FormCadastrarFormatoMateriais::salvar()
{
  m_model->submitAll();
}
void FormCadastrarFormatoMateriais::remover()
{
  auto selectionModel = ui->tableView->selectionModel();
  auto indexSelecionado = selectionModel->currentIndex();
  if(indexSelecionado.isValid()) {
    m_model->removeRow(indexSelecionado.row());
  }
}
