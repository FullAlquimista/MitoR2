//
// Created by Robson on 01/01/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_FormCadastrarClassificacoesMateriais.h" resolved

#include "formcadastrarclassificacoesmateriais.hpp"
#include "ui_formcadastrarclassificacoesmateriais.h"
#include <mitor/gui/callbackpaintdelegate.hpp>
#include <mitor/gui/keyeventfilter.hpp>

FormCadastrarClassificacoesMateriais::FormCadastrarClassificacoesMateriais(QWidget *parent) : QWidget(parent), ui(new Ui::FormCadastrarClassificacoesMateriais)
{
  ui->setupUi(this);
  // Carregar módulos.
  auto app = QApplication::instance();
  _acesso = app->findChild<Sessao::IAcesso*>();
  if(!_acesso) {
    QMessageBox::warning(this, this->objectName(), "Falha ao carregar os serviços.");
    return;
  }
  
  // Carregando o modelo.
  m_model = new QStandardItemModel(this);
  m_model->setColumnCount(3);
  m_model->setHeaderData(0, Qt::Horizontal, QString("ID"));
  m_model->setHeaderData(1, Qt::Horizontal, QString("Descrição"));
  m_model->setHeaderData(2, Qt::Horizontal, QString("Nomear"));
  ui->treeView->setModel(m_model);
  ui->treeView->setSelectionMode(QTreeView::SelectionMode::SingleSelection);
  
  carregarModelo();
  
  // Trata a tecla ESCAPE no dispositivo treeView para limpar seleções.
  MitoR::Gui::CallbackEventFilter *filtroTeclaEscape = new MitoR::Gui::CallbackEventFilter([this](QObject *obj, QEvent* evento) {
    auto keyEvent = static_cast<QKeyEvent*>(evento);
    if(keyEvent->key() == Qt::Key_Escape) {
      auto treeView = qobject_cast<QTreeView *>(obj);
      if (treeView) {
        auto selectionModel = treeView->selectionModel();
        selectionModel->setCurrentIndex(QModelIndex(), QItemSelectionModel::ClearAndSelect);
      }
    }
    return false; // Continua a enviar este evento a outros objetos filtros.
  }, this);
  ui->treeView->installEventFilter(filtroTeclaEscape);
  
  // Delegate para pintar de cores diferentes o conteúdo da coluna descrição quando adiconar, alterar ou remover um item.
  auto descricaoDelegate = new MitoR::Gui::CallbackPaintDelegate([this](QPainter *, QStyleOptionViewItem &option, const QModelIndex &index) {
    auto idxColuna0 = m_model->index(index.row(), 0, index.parent());
    bool adicionar = idxColuna0.data(Roles::Adicionar).toBool();
//    bool atualizar = idxColuna0.data(Roles::Atualizar).toBool();
//    bool remover = idxColuna0.data(Roles::Remover).toBool();
    if(adicionar) {
      auto fonte = option.font;
      fonte.setBold(true);
      option.font = fonte;
    }else {
      auto fonte = option.font;
      fonte.setBold(false);
      option.font = fonte;
    }
    return false;
  }, ui->treeView);
  ui->treeView->setItemDelegateForColumn(1, descricaoDelegate);
  
  // Delegate para adicionar icones na coluna 0 quando um item está para ser removido ou alterado.
  auto idDelegate = new MitoR::Gui::CallbackPaintDelegate([this](QPainter*, QStyleOptionViewItem &, const QModelIndex &index) {
    auto idxColuna0 = m_model->index(index.row(), 0, index.parent());
    auto itemColuna0 = m_model->itemFromIndex(idxColuna0);
    bool adicionar = idxColuna0.data(Roles::Adicionar).toBool();
    bool atualizar = idxColuna0.data(Roles::Atualizar).toBool();
    bool remover = idxColuna0.data(Roles::Remover).toBool();
    if(remover == false) {
      if(adicionar) {
        itemColuna0->setIcon(QApplication::style()->standardIcon(QStyle::SP_FileIcon));
      }else if (atualizar) {
        itemColuna0->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogSaveButton));
      } else {
        itemColuna0->setIcon(QIcon());
      }
    }else {
      itemColuna0->setIcon(QApplication::style()->standardIcon(QStyle::SP_TrashIcon));
    }
    return false;
  }, ui->treeView);
  ui->treeView->setItemDelegateForColumn(0, idDelegate);
  
  // Sinal ativado quando uma edição acontece na coluna descrição.
  QObject::connect(descricaoDelegate, SIGNAL(itemEditado(const QModelIndex&)), this, SLOT(itemAtualizado(const QModelIndex&)));
  
  QObject::connect(ui->pushButtonAdicionar, &QPushButton::clicked, this, &FormCadastrarClassificacoesMateriais::novo);
  QObject::connect(ui->pushButtonSalvar, &QPushButton::clicked, this, &FormCadastrarClassificacoesMateriais::salvar);
  QObject::connect(ui->pushButtonRemover, &QPushButton::clicked, this, &FormCadastrarClassificacoesMateriais::remover);
}
FormCadastrarClassificacoesMateriais::~FormCadastrarClassificacoesMateriais()
{
  delete ui;
}
void FormCadastrarClassificacoesMateriais::itemAtualizado(const QModelIndex &index)
{
  auto idxColuna0 = m_model->index(index.row(), 0, index.parent());
  m_model->setData(idxColuna0, true, Roles::Atualizar);
}
void FormCadastrarClassificacoesMateriais::novo()
{
  auto selectionModel = ui->treeView->selectionModel();
  auto idxSelecionado = m_model->index(selectionModel->currentIndex().row(), 0, selectionModel->currentIndex().parent());
  auto itemNo = m_model->itemFromIndex(idxSelecionado);
  auto novoItem = new QStandardItem;
  if(!itemNo) {
    itemNo = m_model->invisibleRootItem();
  }
  int cRow = itemNo->rowCount();
  novoItem->setData(true, Roles::Adicionar); // Marca este item como um item a ser adicionado na tabela.
  itemNo->setChild(cRow, 0, novoItem);
  itemNo->setChild(cRow, 1, new QStandardItem);
  itemNo->child(cRow, 1)->setData(QString("Novo"), Qt::DisplayRole);
  itemNo->setChild(cRow, 2, new QStandardItem);
  itemNo->child(cRow, 2)->setData(0, Qt::DisplayRole);
  ui->treeView->expand(m_model->indexFromItem(itemNo));
}
void FormCadastrarClassificacoesMateriais::salvar()
{
  // Efetua a leitura de todos os itens da arvore
  QList<QStandardItem*> listaItens;
  listaItens.push_front(m_model->invisibleRootItem());
  while(!listaItens.isEmpty()) {
    auto itemNo = listaItens.back();
    for(auto r=0; r <  itemNo->rowCount(); ++r) {
      bool adicionar = itemNo->child(r, 0)->data(Roles::Adicionar).toBool();
      bool remover = itemNo->child(r, 0)->data(Roles::Remover).toBool();
      if(adicionar && remover == false) {
        auto bd = _acesso->conexao();
        bd.transaction();
        QSqlQuery c(bd);
        auto novoItem = itemNo->child(r, 0);
        // Adiciona a inforação do id do nó neste novoItem.
        // Está informação vem do nó.
        novoItem->setData(itemNo->data(Roles::CT_Item_ID), Roles::CT_No_ID);
        auto res = adicionarItemTabela(novoItem, c);
        if(res == Erro::Falha) {
          QMessageBox::warning(this, "Adicionando novo item a tabela...", QString("Falha ao adicionar o item.\n%1").formatArg(c.lastError().text()));
          bd.rollback();
        }else {
          if(c.next()) {
            adicionarPapeisNovoItem(c.record(), novoItem);
          }
          itemNo->child(r, 0)->setData(false, Roles::Adicionar);
          itemNo->child(r, 0)->setData(false, Roles::Atualizar);
          bd.commit();
        }
      }
      if(remover) {
        if(adicionar) {
          // Este item é novo e pode ser retirado do modelo sem alterar o banco de dados.
          itemNo->removeRow(r);
        }else {
          auto bd = _acesso->conexao();
          bd.transaction();
          QSqlQuery c(bd);
          auto item = itemNo->child(r, 0);
          auto res = removerItemTabela(item, c);
          if(res == Erro::Falha) {
            QMessageBox::warning(this, "Adicionando novo item a tabela...", QString("Falha ao adicionar o item.\n%1").formatArg(c.lastError().text()));
            bd.rollback();
          }else {
            itemNo->removeRow(r);
            bd.commit();
          }
        }
      }else {
        listaItens.push_front(itemNo->child(r, 0)); // Adiciona o item r e c=0 na lista.
      }
    }
    listaItens.pop_back();
  }
}
void FormCadastrarClassificacoesMateriais::remover()
{
  auto selectionModel = ui->treeView->selectionModel();
  auto idxSelecionado = m_model->index(selectionModel->currentIndex().row(), 0, selectionModel->currentIndex().parent());
  auto itemSelecionado = m_model->itemFromIndex(idxSelecionado);
  if(!itemSelecionado)
    return;
  bool remover = itemSelecionado->data(Roles::Remover).toBool();
  if(remover) {
    itemSelecionado->setData(false, Roles::Remover);
  }else {
    itemSelecionado->setData(true, Roles::Remover);
  }
//
//  // Com isso gera um sinal para atualizar a coluna 1 via delegate.
//  // Porque mudamos os dados acima da coluna 0 e deve refletir visualmente na coluna 1.
//  auto itemNo = itemSelecionado->parent();
//  if(!itemNo) itemNo = m_model->invisibleRootItem();
//  auto itemSelecionadoColuna1 = itemNo->child(itemSelecionado->row(), 1);
//  itemSelecionadoColuna1->setData(true, Roles::Remover);
}
void FormCadastrarClassificacoesMateriais::carregarModelo()
{
  QSqlQuery consulta(_acesso->conexao());
  if(!consultarClassificacoes(consulta))
    return;
  // Este algoritmo depende que na descrição da estrutura hierarquica
  // venha primeiro do item em questão o id do nó com o nível -1
  // e sempre na sequencia o id do item em sí com o nivel 0.
  using IntId = int;
  using Item = QStandardItem;
  QMap<IntId, Item*> map;
  auto itNo = map.insert(0, m_model->invisibleRootItem());
  while(consulta.next()) {
    auto reg = consulta.record();
    auto id_item = reg.value("id_item").toInt();
    auto id_no = reg.value("id_no").toInt();
    auto nivel = reg.value("nivel").toInt();
    if(nivel == -1) {
      // 'Item' nó.
      itNo = map.find(id_no);
      if(itNo == map.end()) { // 'Item' nó não existe.
        itNo = map.insert(id_no, new Item);
        itNo.value()->setEnabled(false); // Primeiro item linha: 0 e coluna: 0.
        itNo.value()->setData(id_item, Roles::CT_No_ID);
      }
    }else if(nivel == 0) {
      // Item atual.
      auto itItem = map.find(id_item);
      if(itItem == map.end()) {
        itItem = map.insert(id_item, new Item);
        itItem.value()->setEnabled(false); // Primeiro item linha: 0, e coluna: 0.
      }
      preencherPapeisItem(reg, itItem.value());
      itItem.value()->setData(reg.value("c_id"), Qt::DisplayRole);
      // Verifica se este nó já tem a quantidade de colunas inseridas.
      if(itNo.value()->columnCount() < 1)
        itNo.value()->setColumnCount(3);
      int cRow = itNo.value()->rowCount();
      itNo.value()->setChild(cRow, 0, itItem.value());
      itNo.value()->setChild(cRow, 1, new Item);
      itNo.value()->child(cRow, 1)->setData(reg.value("descricao"), Qt::DisplayRole);
      itNo.value()->setChild(cRow, 2, new Item);
      itNo.value()->child(cRow, 2)->setData(reg.value("nomear"), Qt::DisplayRole);
      itNo = map.find(0); // Coloca o item raiz do modelo para um próximo item.
    }
  }
}
bool FormCadastrarClassificacoesMateriais::consultarClassificacoes(QSqlQuery &consulta)
{
  if(!consulta.exec(QString(R"(SELECT ct.id as ct_id, ct.id_item, ct.id_no, ct.nivel, c.id as c_id, c.descricao, c.nomear FROM cadastro.classificacoes_materiais_ct ct INNER JOIN cadastro.classificacoes_materiais c ON ct.id_item = c.id WHERE ct.nivel > -2 ORDER BY ct.id_item, ct.nivel;)"))) {
    QMessageBox::warning(this, "Consulta de classificações", QString("Falha ao efetuar a consulta da tabela fechada.\n%1").formatArg(consulta.lastError().text()));
    return false;
  }
  return true;
}
void FormCadastrarClassificacoesMateriais::preencherPapeisItem(const QSqlRecord &reg, QStandardItem *item)
{
  auto ct_id = reg.value("ct_id").toInt();
  auto id_item = reg.value("id_item").toInt();
  auto id_no = reg.value("id_no").toInt();
  auto nivel = reg.value("nivel").toInt();
  auto c_id = reg.value("c_id").toInt();
  auto c_descricao = reg.value("descricao").toString();
  auto c_nomear = reg.value("nomear").toInt();
  item->setData(ct_id, Roles::CT_ID);
  item->setData(id_item, Roles::CT_Item_ID);
  item->setData(id_no, Roles::CT_No_ID);
  item->setData(nivel, Roles::CT_Nivel);
  item->setData(c_id, Roles::C_ID);
  item->setData(c_descricao, Roles::C_Descricao);
  item->setData(c_nomear, Roles::C_Nomear);
}
FormCadastrarClassificacoesMateriais::Erro FormCadastrarClassificacoesMateriais::adicionarItemTabela(QStandardItem *novoItem, QSqlQuery &consulta)
{
  const QString cmd = R"(
                        WITH item_inserido AS (
                          INSERT INTO cadastro.classificacoes_materiais (descricao, nomear) VALUES (:descricao, :nomear) RETURNING *
                        ), inseridos_ct AS (
                          INSERT INTO cadastro.classificacoes_materiais_ct (id_item, id_no, nivel)
                            ( SELECT ii.id, ii.id, 0 FROM item_inserido ii UNION ALL
                              SELECT ii.id, lk.id_no, lk.nivel - 1 FROM item_inserido ii, cadastro.classificacoes_materiais_ct lk WHERE id_item = :id_no
                            )
                          RETURNING *
                        )
                        SELECT ct.id as ct_id, ct.id_item, ct.id_no, ct.nivel, c.id as c_id, c.descricao, c.nomear FROM inseridos_ct ct, item_inserido c WHERE ct.nivel = 0 AND ct.id_item = c.id ORDER BY ct.id_item, ct.nivel;
                        )";
  auto id_no = novoItem->data(Roles::CT_No_ID).toInt();
  auto itemNo = novoItem->parent();
  if(!itemNo) itemNo = m_model->invisibleRootItem();
  auto descricao = itemNo->child(novoItem->row(), 1)->data(Qt::DisplayRole).toString();
  auto nomear = itemNo->child(novoItem->row(), 2)->data(Qt::DisplayRole).toInt();
  consulta.prepare(cmd);
  consulta.bindValue(":descricao", descricao);
  consulta.bindValue(":nomear", nomear);
  consulta.bindValue(":id_no", id_no);
  if(!consulta.exec()) {
    return Erro{Erro::Falha, consulta.lastError().text()};
  }
  return Erro{Erro::Sucesso, ""};
}
void FormCadastrarClassificacoesMateriais::adicionarPapeisNovoItem(const QSqlRecord &reg, QStandardItem *novoItem)
{
  auto ct_id = reg.value("ct_id").toInt();
  auto id_item = reg.value("id_item").toInt();
  auto nivel = reg.value("nivel").toInt();
  auto c_id = reg.value("c_id").toInt();
  auto c_descricao = reg.value("descricao").toString();
  auto c_nomear = reg.value("nomear").toInt();
  novoItem->setData(ct_id, Roles::CT_ID);
  novoItem->setData(id_item, Roles::CT_Item_ID);
  novoItem->setData(nivel, Roles::CT_Nivel);
  novoItem->setData(c_id, Roles::C_ID);
  novoItem->setData(c_descricao, Roles::C_Descricao);
  novoItem->setData(c_nomear, Roles::C_Nomear);
  novoItem->setData(novoItem->data(Roles::C_ID), Qt::DisplayRole);
}
FormCadastrarClassificacoesMateriais::Erro FormCadastrarClassificacoesMateriais::removerItemTabela(QStandardItem *item, QSqlQuery &consulta)
{
  const QString cmd = R"(
                        WITH remover AS (
                          SELECT * FROM cadastro.classificacoes_materiais_ct WHERE id_no = :id_item ORDER BY id_item, nivel
                        ), ct_deletados AS (
                          DELETE FROM cadastro.classificacoes_materiais_ct ct USING remover r WHERE ct.id_item = r.id_item RETURNING ct.id_item
                        ), deletados AS (
                          DELETE FROM cadastro.classificacoes_materiais c USING ct_deletados d WHERE c.id = d.id_item RETURNING *
                        ) SELECT * FROM deletados;
                        )";
  auto id_item = item->data(Roles::CT_No_ID).toInt();
  consulta.prepare(cmd);
  consulta.bindValue(":id_item", id_item);
  if(!consulta.exec()) {
    return Erro{Erro::Falha, consulta.lastError().text()};
  }
  return Erro{Erro::Sucesso, ""};
}
