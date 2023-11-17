//
// Created by Robson on 31/12/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_FormCadastrarUnidadesMedidas.h" resolved

#include "formcadastrarunidadesmedidas.hpp"
#include "ui_FormCadastrarUnidadesMedidas.h"
#include <spdlog/spdlog.h>

class DoubleSpinBoxDelegate : public QStyledItemDelegate
{
  CS_OBJECT(DoubleSpinBoxDelegate)
public:
  DoubleSpinBoxDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}
  
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const override
  {
    (void)option, (void)index;
    QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
    editor->setFrame(false);
    editor->setDecimals(4);
    editor->setMinimum(-1000000000);
    editor->setMaximum(1000000000);
    
    return editor;
  }
  
  void setEditorData(QWidget *editor, const QModelIndex &index) const override
  {
    double value = index.model()->data(index, Qt::EditRole).toDouble();
    
    auto *spinBox = static_cast<QDoubleSpinBox*>(editor);
    spinBox->setValue(value);
  }
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const override
  {
    auto *spinBox = static_cast<QDoubleSpinBox*>(editor);
    spinBox->interpretText();
    double value = spinBox->value();
    
    model->setData(index, value, Qt::EditRole);
  }

  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const override
  {
    (void)option, (void)index;
    editor->setGeometry(option.rect);
  }
};

// ************************************************************************************************

FormCadastrarUnidadesMedidas::FormCadastrarUnidadesMedidas(QWidget *parent) : QWidget(parent), ui(new Ui::FormCadastrarUnidadesMedidas)
{
  ui->setupUi(this);
  
  // Carregando serviço acesso.
  auto app = QApplication::instance();
  _acesso = app->findChild<Sessao::IAcesso*>();
  if(!_acesso) {
    spdlog::warn("Falha ao carregar os servições: acesso, etc.");
    return;
  }
  
  m_tUnidadesMedidas = new QSqlTableModel(this, _acesso->conexao());
  m_tUnidadesMedidas->setTable("cadastro.unidades_medidas");
  if(m_tUnidadesMedidas->lastError().isValid()) {
    QMessageBox::warning(this, QString("%1").formatArg(this->objectName()),
                         QString("Falha ao carregar a tabela.\n%1").formatArg(m_tUnidadesMedidas->lastError().text()));
    return;
  }
  m_tUnidadesMedidas->setHeaderData(0, Qt::Horizontal, QString("ID"));
  m_tUnidadesMedidas->setHeaderData(1, Qt::Horizontal, QString("Descrição"));
  m_tUnidadesMedidas->setHeaderData(2, Qt::Horizontal, QString("Abreviação"));
  m_tUnidadesMedidas->setEditStrategy(QSqlTableModel::OnManualSubmit);
  m_tUnidadesMedidas->select();
  
  ui->tableView->setModel(m_tUnidadesMedidas);
  ui->tableView->setItemDelegateForColumn(4, new DoubleSpinBoxDelegate(this));
  ui->tableView->setColumnHidden(0, true);
  
  QObject::connect(ui->pushButtonAdicionar, &QPushButton::clicked, this, &FormCadastrarUnidadesMedidas::novo);
  QObject::connect(ui->pushButtonGravar, &QPushButton::clicked, this, &FormCadastrarUnidadesMedidas::salvar);
  QObject::connect(ui->pushButtonExcluir, &QPushButton::clicked, this, &FormCadastrarUnidadesMedidas::remover);
  
  m_tConversao = new QSqlRelationalTableModel(this, _acesso->conexao());
  m_tConversao->setTable("cadastro.conversao_medidas");
  if(m_tConversao->lastError().isValid()) {
    QMessageBox::warning(this, QString("%1").formatArg(this->objectName()),
                         QString("Falha ao carregar a tabela.\n%1").formatArg(m_tUnidadesMedidas->lastError().text()));
    return;
  }
  m_tConversao->setRelation(2, QSqlRelation("cadastro.unidades_medidas", "id", "abreviacao"));
  auto tR1 = m_tConversao->relationModel(2);
  if(tR1->lastError().isValid()) {
    QMessageBox::warning(this, QString("%1").formatArg(this->objectName()),
                         QString("Falha ao carregar a tabela.\n%1").formatArg(m_tUnidadesMedidas->lastError().text()));
    return;
  }
  m_tConversao->setRelation(3, QSqlRelation("cadastro.unidades_medidas", "id", "abreviacao"));
  auto tR2 = m_tConversao->relationModel(3);
  if(tR2->lastError().isValid()) {
    QMessageBox::warning(this, QString("%1").formatArg(this->objectName()),
                         QString("Falha ao carregar a tabela.\n%1").formatArg(m_tUnidadesMedidas->lastError().text()));
    return;
  }
  m_tConversao->setHeaderData(0, Qt::Horizontal, QString("ID"));
  m_tConversao->setHeaderData(1, Qt::Horizontal, QString("Descrição"));
  m_tConversao->setHeaderData(2, Qt::Horizontal, QString("Unidade dividendo"));
  m_tConversao->setHeaderData(3, Qt::Horizontal, QString("Unidade divisor"));
  m_tConversao->setHeaderData(4, Qt::Horizontal, QString("Fator"));
  m_tConversao->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
  m_tConversao->select();
  
  ui->tableViewConversao->setModel(m_tConversao);
  ui->tableViewConversao->setItemDelegateForColumn(2, new QSqlRelationalDelegate(ui->tableViewConversao));
  ui->tableViewConversao->setItemDelegateForColumn(3, new QSqlRelationalDelegate(ui->tableViewConversao));
  ui->tableViewConversao->setColumnHidden(0, true);
  
  QObject::connect(ui->pushButtonAdicionarConversao, &QPushButton::clicked, this, &FormCadastrarUnidadesMedidas::novoConversao);
  QObject::connect(ui->pushButtonGravarConversao, &QPushButton::clicked, this, &FormCadastrarUnidadesMedidas::salvarConversao);
  QObject::connect(ui->pushButtonExcluirConversao, &QPushButton::clicked, this, &FormCadastrarUnidadesMedidas::removerConversao);
}

FormCadastrarUnidadesMedidas::~FormCadastrarUnidadesMedidas()
{
  delete ui;
}
void FormCadastrarUnidadesMedidas::novo()
{
  int linha = m_tUnidadesMedidas->rowCount();
  m_tUnidadesMedidas->insertRow(linha);
}
void FormCadastrarUnidadesMedidas::salvar()
{
  m_tUnidadesMedidas->submitAll();
  if(m_tUnidadesMedidas->lastError().isValid()) {
    QMessageBox::warning(this, QString("%1").formatArg(this->objectName()),
                         QString("Falha ao salvar a tabela.\n%1").formatArg(m_tUnidadesMedidas->lastError().text()));
  }
}
void FormCadastrarUnidadesMedidas::remover()
{
  auto selectionModel = ui->tableView->selectionModel();
  auto idxSelecionado = selectionModel->currentIndex();
  if(idxSelecionado != QModelIndex()) {
    m_tUnidadesMedidas->removeRow(idxSelecionado.row(), idxSelecionado.parent());
  }
}
void FormCadastrarUnidadesMedidas::novoConversao()
{
  int linha = m_tConversao->rowCount();
  m_tConversao->insertRow(linha);
}
void FormCadastrarUnidadesMedidas::salvarConversao()
{
  m_tConversao->submitAll();
  if(m_tConversao->lastError().isValid()) {
    QMessageBox::warning(this, QString("%1").formatArg(this->objectName()),
                         QString("Falha ao salvar a tabela.\n%1").formatArg(m_tUnidadesMedidas->lastError().text()));
  }
}
void FormCadastrarUnidadesMedidas::removerConversao()
{
  auto selectionModel = ui->tableViewConversao->selectionModel();
  auto idxSelecionado = selectionModel->currentIndex();
  if(idxSelecionado != QModelIndex()) {
    m_tConversao->removeRow(idxSelecionado.row(), idxSelecionado.parent());
  }
}
