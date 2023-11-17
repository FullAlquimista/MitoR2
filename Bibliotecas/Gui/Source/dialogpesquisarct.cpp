//
// Created by Robson on 22/01/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DialogPesquisarArvore.h" resolved

#include <mitor/gui/dialogpesquisarct.hpp>
#include "ui_dialogpesquisarct.h"
#include <QtCore>
#include <QtGui>
#include <QtSql>

namespace MitoR::Gui
{
  DialogPesquisarCT::DialogPesquisarCT(QSqlTableModel *tblModel, QWidget *parent)
      : QDialog(parent), ui(new Ui::DialogPesquisarCT), m_tModel(tblModel)
  {
    ui->setupUi(this);

    m_idChvPrimaria = m_tModel->primaryKey();

    m_tModelCt = new QSqlTableModel(this, m_tModel->database());
    const QString nomeTabelaCt = m_tModel->tableName() + "_ct";
    m_tModelCt->setTable(nomeTabelaCt);
    if (m_tModelCt->lastError().isValid()) {
      QMessageBox::warning(this, "Pesquisar arvore...", QString("Falha ao carregar a tabela auxiliar %1.\n%2").formatArg(nomeTabelaCt).formatArg(m_tModelCt->lastError().text()));
      return;
    }
    m_tModelCt->setFilter("nivel > -2 ORDER BY id_item, nivel");
    m_tModelCt->select();
    if (m_tModelCt->lastError().isValid()) {
      QMessageBox::warning(this, "Pesquisar arvore...", QString("Falha ao aplicar o filtro na tabela %1.\n%2").formatArg(nomeTabelaCt).formatArg(m_tModelCt->lastError().text()));
      return;
    }

    m_tTreeModel = new QStandardItemModel;
    m_tTreeModel->setColumnCount(m_tModel->columnCount());
    for (auto c = 0, max = m_tModel->columnCount(); c < max; ++c) {
      m_tTreeModel->setHeaderData(c, Qt::Horizontal, m_tModel->headerData(c, Qt::Horizontal));
    }
    carregarModelo();

    ui->treeView->setModel(m_tTreeModel);
    ui->treeView->expandAll();
    QObject::connect(ui->pushButtonOk, &QPushButton::clicked, this, [this](bool) {
      accept();
    });
  }
  DialogPesquisarCT::~DialogPesquisarCT()
  {
    delete ui;
  }

  void DialogPesquisarCT::carregarModelo()
  {
    QMap<int, QStandardItem *> map;
    auto itNo = map.insert(0, m_tTreeModel->invisibleRootItem());
    for (int l = 0, max = m_tModelCt->rowCount(); l < max; ++l) {
      auto reg = m_tModelCt->record(l);
      int nivel = reg.value("nivel").toInt();
      int idItem = reg.value("id_item").toInt();
      int idNo = reg.value("id_no").toInt();
      int idCt = reg.value("id").toInt();
      if (nivel == -1) {
        // Item com informação de quem é o nó.
        itNo = map.find(idNo);
        if (itNo == map.end()) {
          itNo = map.insert(idNo, new QStandardItem);
        }
        if (itNo.value()->columnCount() < 1) {
          itNo.value()->setColumnCount(m_tModel->columnCount());
        }
        auto itItem = map.find(idItem);
        if (itItem == map.end()) {
          itItem = map.insert(idItem, new QStandardItem);
          itItem.value()->setData(idCt, Roles::IdCt); // Grava o id que contém a informação do item e seu nó.
          itItem.value()->setData(idNo, Roles::IdNoCt);
          itItem.value()->setData(nivel, Roles::NivelCt);
        }
      } else if (nivel == 0) {
        // Item pertencente à um nó anterior ou um nó raiz.
        auto itItem = map.find(idItem);
        if (itItem == map.end()) {
          itItem = map.insert(idItem, new QStandardItem);
          itItem.value()->setData(idCt, Roles::IdCt); // Grava o id que contém a informação do item e seu nó.
          itItem.value()->setData(idNo, Roles::IdNoCt);
          itItem.value()->setData(nivel, Roles::NivelCt);
        }
        itItem.value()->setData(idItem, Roles::IdItemCt);
        auto linhaDisponivel = itNo.value()->rowCount();
        itNo.value()->setChild(linhaDisponivel, itItem.value()); // Adiciona este item ao nó.
        preencherDadosItem(itNo.value(), itItem.value());
        itNo = map.find(0); // Obtém o nó raiz, após preencher o item, caso o próximo item não tenha um item nó.
      }
    }
  }
  void DialogPesquisarCT::preencherDadosItem(QStandardItem *no, QStandardItem *item)
  {
    auto idMaterial = item->data(Roles::IdItemCt).toInt();
    for (int linha = 0, maxL = m_tModel->rowCount(); linha < maxL; ++linha) {
      auto reg = m_tModel->record(linha);
      // Procura pelo registro deste item para preencher suas informações.
      if (reg.value(m_idChvPrimaria.fieldName(0)).toInt() == idMaterial) {
        for (int coluna = 0, maxC = reg.count(); coluna < maxC; ++coluna) {
          auto itemN = no->child(item->row(), coluna);
          if (!itemN) {
            itemN = new QStandardItem;
            no->setChild(item->row(), coluna, itemN);
          }
          if(coluna == 0) {
            // Armazena no primeiro item da linha, a informação da linha do modelo m_tModel selecionado.
            itemN->setData(linha, IndexModelRow);
          }
          itemN->setEditable(false);
          itemN->setData(reg.value(coluna), Qt::DisplayRole);
        }
        break;
      }
    }
  }
  QModelIndex DialogPesquisarCT::indexSelecionado()
  {
    auto listaIdx = ui->treeView->selectionModel()->selectedIndexes();
    for(auto idx : listaIdx) {
      return m_tModel->index(idx.data(IndexModelRow).toInt(), 0);
    }
    return QModelIndex();
  }

}