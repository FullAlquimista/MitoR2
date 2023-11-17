//
// Created by Robson on 01/10/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DialogPesquisarTabela.h" resolved

#include "../include/mitor/gui/dialogpesquisartabela.hpp"
#include "ui_DialogPesquisarTabela.h"

namespace MitoR::Gui {
    
    DialogPesquisarTabela::DialogPesquisarTabela(QAbstractItemModel *ptrModelo, QWidget *parent)
        :
        QDialog(parent), ui(new Ui::DialogPesquisarTabela), pModelo(ptrModelo)
    {
      ui->setupUi(this);
      ui->tableView->setModel(pModelo);
      
      QObject::connect(ui->pushButtonOk, &QPushButton::clicked, this, [=]()
      {
        if(ui->tableView->selectionModel()->selectedIndexes().isEmpty())
          return;
        accept();
      });
    }
    
    DialogPesquisarTabela::~DialogPesquisarTabela()
    {
      delete ui;
    }
    
    QModelIndex DialogPesquisarTabela::indexSelecionado()
    {
      auto listaIdx = ui->tableView->selectionModel()->selectedIndexes();
      for(auto idx : listaIdx) {
        return idx;
      }
      return QModelIndex();
    }
} // MitoR::Gui
