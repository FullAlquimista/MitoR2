//
// Created by Robson on 24/12/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_FormCadastrarPlanoContas.h" resolved

#include "formcadastrarplanoconta.hpp"
#include "ui_formcadastrarplanoconta.h"
#include <QFont>
#include <functional>
#include <spdlog/spdlog.h>

class FiltroTeclaEsc : public QObject
{
  CS_OBJECT(FiltroTeclaEsc)

  std::function<bool()> m_funcOp;

public:
  FiltroTeclaEsc(std::function<bool()> func, QObject *parent = nullptr) : QObject(parent), m_funcOp(func)
  {
  }

protected:
  bool eventFilter(QObject *obj, QEvent *evento) override
  {
    (void) obj;
    if (evento->type() == QEvent::KeyPress) {
      QKeyEvent *keyEvent = static_cast<QKeyEvent *>(evento);
      if (keyEvent->key() == Qt::Key_Escape) {
        return m_funcOp();
      }
    }
    return false;
  }
};

class ItemDelegate : public QStyledItemDelegate
{
  CS_OBJECT(ItemDelegate)
public:
  ItemDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

public:
  CS_SIGNAL_1(Public, void itemEditado(const QModelIndex index))
  CS_SIGNAL_2(itemEditado, index)

protected:
  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
  {
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);
    int data = index.data(FormCadastrarPlanoConta::ColumnRoles::Estado).toInt();
    if (data >= 1) {
      opt.font.setBold(true);
      opt.palette.setBrush(QPalette::ColorRole::Text, QBrush(QColor(0, 255, 0)));
    } else if (data == -1) {
      opt.font.setBold(true);
      opt.palette.setBrush(QPalette::ColorRole::Text, QBrush(QColor(255, 0, 0)));
    }
    QStyledItemDelegate::paint(painter, opt, index);
  }

  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override
  {
    auto data = index.data();
    QStyledItemDelegate::setModelData(editor, model, index);
    auto modifiedData = index.data();
    if (data.toString() != modifiedData.toString()) {
      const_cast<ItemDelegate *>(this)->itemEditado(index);
    }
  }
};

FormCadastrarPlanoConta::FormCadastrarPlanoConta(QWidget *parent) : QWidget(parent), ui(new Ui::FormCadastrarPlanoConta)
{
  ui->setupUi(this);

  auto app = QApplication::instance();
  _acesso = app->findChild<Sessao::IAcesso *>();
  if (!_acesso) {
    spdlog::error("Serviços necessários não foram encontrados.");
    return;
  }

  _model = new QStandardItemModel(ui->treeView);
  _model->insertColumns(0, 1, QModelIndex());
  _model->setHeaderData(0, Qt::Horizontal, QString("Nome"));
  ui->treeView->setModel(_model);
  ui->treeView->setSelectionMode(QTreeView::SelectionMode::SingleSelection);

  ui->treeView->installEventFilter(new FiltroTeclaEsc([this]() {
    ui->treeView->selectionModel()->setCurrentIndex(QModelIndex(), QItemSelectionModel::ClearAndSelect);
    return true;
  }, ui->treeView));

  auto delegate = new ItemDelegate(ui->treeView);
  ui->treeView->setItemDelegateForColumn(0, delegate);
  QObject::connect(delegate, &ItemDelegate::itemEditado, this, [this](const QModelIndex index) {
    auto estadoIndex = index.data(ColumnRoles::Estado).toInt();
    if (estadoIndex < 1)
      _model->setData(index, 1, ColumnRoles::Estado);
  });

  QObject::connect(ui->pushButtonAdicionar, &QPushButton::clicked, this, &FormCadastrarPlanoConta::novo);
  QObject::connect(ui->pushButtonSalvar, &QPushButton::clicked, this, &FormCadastrarPlanoConta::salvar);
  QObject::connect(ui->pushButtonRemover, &QPushButton::clicked, this, &FormCadastrarPlanoConta::remover);

  _tPlanosContaCt = new QSqlQueryModel(this);
  atualizarTabelaPlanosConta();

  carregarPlanosConta();
}

FormCadastrarPlanoConta::~FormCadastrarPlanoConta()
{
  delete ui;
}

void FormCadastrarPlanoConta::novo(bool)
{
  auto selectionModel = ui->treeView->selectionModel();
  auto idxSelecionado = _model->index(selectionModel->currentIndex().row(), 0, selectionModel->currentIndex().parent());
  if (_model->columnCount(idxSelecionado) < 1) {
    _model->insertColumns(0, 1, idxSelecionado);
  }
  int inserirNaLinha = _model->rowCount(idxSelecionado);
  if (_model->insertRow(inserirNaLinha, idxSelecionado)) {
    ui->treeView->expand(idxSelecionado);
    auto idxInserido = _model->index(inserirNaLinha, 0, idxSelecionado);
    _model->setData(idxInserido, QString("Novo"));
    _model->setData(idxInserido, idxSelecionado.data(ColumnRoles::ClousureTableIdItem), ColumnRoles::ClousureTableIdNo);
    _model->setData(idxInserido, 2, ColumnRoles::Estado);
    selectionModel->setCurrentIndex(idxSelecionado, QItemSelectionModel::ClearAndSelect);
    ui->treeView->resizeColumnToContents(0);
  }
}

void FormCadastrarPlanoConta::salvar(bool)
{
  QList<QModelIndex> listaIndexes;
  listaIndexes.push_front(QModelIndex()); // Nó raiz.
  while (!listaIndexes.isEmpty()) {
    for (int l = 0; l < _model->rowCount(listaIndexes.back()); ++l) {
      auto index = _model->index(l, 0, listaIndexes.back());
      auto estadoItem = index.data(ColumnRoles::Estado).toInt();
      if (estadoItem == 1) {
        auto bd = _acesso->conexao();
        bd.transaction();
        auto res = atualizarIndex(index);
        if (res == MitoR::Erro::Falha) {
          QMessageBox::warning(this, "Salvando...", QString("Falha ao savar as alterações.\n%1").formatArg(res.msg));
          bd.rollback();
        } else {
          bd.commit();
          _model->setData(index, 0, ColumnRoles::Estado);
        }
      } else if (estadoItem == 2) {
        auto bd = _acesso->conexao();
        bd.transaction();
        auto res = inserirIndex(index);
        if (res == MitoR::Erro::Falha) {
          QMessageBox::warning(this, "Salvando...", QString("Falha ao savar as alterações.\n%1").formatArg(res.msg));
          bd.rollback();
        } else {
          bd.commit();
          _model->setData(index, 0, ColumnRoles::Estado);
        }
      } else if (estadoItem == -1) {
        auto bd = _acesso->conexao();
        bd.transaction();
        auto res = apagarIndex(index);
        if (res == MitoR::Erro::Falha) {
          QMessageBox::warning(this, "Salvando...", QString("Falha ao savar as alterações.\n%1").formatArg(res.msg));
          bd.rollback();
        } else {
          bd.commit();
          _model->setData(index, 0, ColumnRoles::Estado);
        }
        // Removendo index.
        auto indexNo = index.parent();
        _model->removeRow(index.row(), index.parent());
        if (_model->rowCount(indexNo) < 1) {
          _model->removeColumns(0, 1, indexNo);
        }
      }
      listaIndexes.push_front(index);
    }
    listaIndexes.pop_back();
  }
}

void FormCadastrarPlanoConta::remover(bool)
{
  auto selectionModel = ui->treeView->selectionModel();
  auto idxSelecionado = _model->index(selectionModel->currentIndex().row(), 0, selectionModel->currentIndex().parent());
  if (idxSelecionado.isValid() && idxSelecionado != QModelIndex()) {
    int estadoItem = idxSelecionado.data(ColumnRoles::Estado).toInt();
    int id = idxSelecionado.data(ColumnRoles::ClousureTableId).toInt();
    if (estadoItem == 2 && id < 1) {
      _model->removeRow(idxSelecionado.row(), idxSelecionado.parent());
    } else if (estadoItem == -1) {
      _model->setData(idxSelecionado, 0, ColumnRoles::Estado);
    } else {
      _model->setData(idxSelecionado, -1, ColumnRoles::Estado);
    }
  }
}

void FormCadastrarPlanoConta::carregarPlanosConta()
{
  // Limpa o modelo sem apagar as informações de cabeçalho.
  _model->removeRows(0, _model->rowCount(QModelIndex()));


  for (int linha = 0; linha < _tPlanosContaCt->rowCount(); ++linha) {
    auto r = _tPlanosContaCt->record(linha);
    int idItem = r.value(1).toInt();
    int idNo = r.value(2).toInt();
    int nivel = r.value(3).toInt();
    if (nivel == -1) {
      QStandardItem *itemNo = nullptr;
      if (!itens.contains(idNo)) {
        // Cria o item nó caso ainda não exista.
        itemNo = new QStandardItem;
        itens[idNo] = itemNo;
      } else {
        itemNo = itens[idNo];
      }
      if (itemNo->columnCount() < 1)
        itemNo->setColumnCount(1);
      QStandardItem *itemRamo = nullptr;
      if (!itens.contains(idItem)) {
        itemRamo = new QStandardItem;
        itens[idItem] = itemRamo;
      } else {
        itemRamo = itens[idItem];
      }
      itemNo->insertRow(itemNo->rowCount(), itemRamo);
    } else if (nivel == 0) {
      QStandardItem *item = nullptr;
      if (!itens.contains(idItem)) {
        item = new QStandardItem;
      } else {
        item = itens[idItem];
      }
      item->setData(r.value(0), ColumnRoles::ClousureTableId);     // _ct.id
      item->setData(r.value(1), ColumnRoles::ClousureTableIdItem); // _ct.id_item
      auto noItem = item->parent();
      if (noItem) {
        item->setData(noItem->data(ColumnRoles::ClousureTableIdItem), ColumnRoles::ClousureTableIdNo); // _ct.id_no
      } else {
        item->setData(r.value(2), ColumnRoles::ClousureTableIdNo); // _ct.id_no
      }
      item->setData(r.value(3), ColumnRoles::ClousureTableNivel); // _ct.nivel
      item->setData(r.value(4), ColumnRoles::TableId);            // pc.id
      item->setData(r.value(5), Qt::EditRole);                    // pc.descricao
      itens[idItem] = item;
    }
  }
  // Interliga todos os itens sem nó, ao "item" raiz do modelo.
  auto itemRaiz = _model->invisibleRootItem();
  for (auto itItem: itens) {
    if (itItem->parent() == nullptr) {
      int n = itemRaiz->rowCount();
      itemRaiz->insertRow(n, itItem);
    }
  }
}

void FormCadastrarPlanoConta::atualizarTabelaPlanosConta()
{
  _tPlanosContaCt->setQuery(QString("SELECT * FROM cadastro.planos_contas_ct ct INNER JOIN cadastro.planos_contas pc ON ct.id_item = pc.id WHERE ct.nivel > -2 ORDER BY id_item, nivel;"), _acesso->conexao());
  if (_tPlanosContaCt->lastError().isValid()) {
    QMessageBox::warning(this, "Formulário: Cadastrar planos conta...", QString("Falha ao obter as informações de hierarquia. \n%1").formatArg(_tPlanosContaCt->lastError().text()));
  }
}

MitoR::Erro FormCadastrarPlanoConta::atualizarIndex(const QModelIndex &index)
{
  using Erro = MitoR::Erro;
  bool res{false};
  const auto idRegistro = index.data(ColumnRoles::TableId).toInt(&res);
  if (!res)
    return {Erro::Falha, "O 'id' necessário para atualizar o registro não foi definido."};
  const auto novoTexto = index.data().toString();
  QSqlQuery c(_acesso->conexao());
  c.prepare("UPDATE cadastro.planos_contas pc SET descricao = :descricao WHERE id = :id;");
  c.bindValue(":descricao", novoTexto);
  c.bindValue(":id", idRegistro);
  if (!c.exec())
    return {Erro::Falha, QString("Falha no comando de atualização de registro.\n%1").formatArg(c.lastError().text())};

  return {Erro::Sucesso, ""};
}

MitoR::Erro FormCadastrarPlanoConta::inserirIndex(const QModelIndex &index)
{
  using Erro = MitoR::Erro;
  auto item = _model->itemFromIndex(index);
  auto itemNo = item->parent();
  int idNo = 0;
  if (itemNo) {
    bool res{false};
    idNo = itemNo->data(ColumnRoles::ClousureTableIdItem).toInt(&res);
    if (!res)
      return {Erro::Falha, QString("Falha ao obter o 'id' do item nó, para inserção de um novo item.")};
  }
  const auto texto = item->data(Qt::EditRole).toString();
  const QString cmd = R"(WITH item_inserido AS (
                          INSERT INTO cadastro.planos_contas (descricao) VALUES (:descricao) RETURNING *
                        )
                        INSERT INTO cadastro.planos_contas_ct (id_item, id_no, nivel)
                          ( SELECT ii.id, ii.id, 0 FROM item_inserido ii UNION ALL
                              SELECT ii.id, lk.id_no, lk.nivel - 1 FROM item_inserido ii, cadastro.planos_contas_ct lk WHERE id_item = :idNo
                          ) RETURNING *;)";
  QSqlQuery c(_acesso->conexao());
  c.prepare(cmd);
  c.bindValue(":descricao", texto);
  c.bindValue(":idNo", idNo);
  if (!c.exec()) {
    return {Erro::Falha, QString("Falha ao executar o comando de inserção.\n%1").formatArg(c.lastError().text())};
  }
  if (c.next()) {
    auto r = c.record();
    auto id = r.value(0);
    auto idItem = r.value(1);
    item->setData(id, ColumnRoles::ClousureTableId);
    item->setData(idItem, ColumnRoles::ClousureTableIdItem);
    item->setData(idNo, ColumnRoles::ClousureTableIdNo);
  }
  return {Erro::Sucesso, ""};
}
MitoR::Erro FormCadastrarPlanoConta::apagarIndex(const QModelIndex &index)
{
  using Erro = MitoR::Erro;
  bool res{false};
  auto idItem = index.data(ColumnRoles::ClousureTableIdItem).toInt(&res);
  if (!res)
    return {Erro::Falha, "O 'id' necessário para remover o registro não foi definido."};
  const auto cmd_ct = QString(R"(WITH remover AS (
                                      SELECT * FROM cadastro.planos_contas_ct WHERE id_no = :idItem ORDER BY id_item, nivel
                                      ),
                                      ct_deletados AS (DELETE FROM cadastro.planos_contas_ct ct USING remover r WHERE ct.id_item = r.id_item RETURNING ct.id_item
                                      ),
                                      deletados AS (DELETE FROM cadastro.planos_contas p USING ct_deletados d WHERE p.id = d.id_item RETURNING *)
                                      SELECT * FROM deletados;)");
  QSqlQuery c(_acesso->conexao());
  c.prepare(cmd_ct);
  c.bindValue(":idItem", idItem);
  if (!c.exec()) {
    return {Erro::Falha, QString("Falha ao executar o comando de remoção.\n%1").formatArg(c.lastError().text())};
  }

  return {Erro::Sucesso, ""};
}
