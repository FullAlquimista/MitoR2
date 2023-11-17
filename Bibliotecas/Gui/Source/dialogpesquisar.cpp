//
// Created by Robson on 28/05/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DialogPesquisar.h" resolved

#include <MitoR/Gui/dialogpesquisar.hpp>
#include "ui_DialogPesquisar.h"
#include <QMessageBox>
#include <spdlog/spdlog.h>

DialogPesquisar::DialogPesquisar(QAbstractItemModel *model, QWidget *parent) : QDialog(parent), ui(new Ui::DialogPesquisar)
{
  ui->setupUi(this);
  this->_model = model;

  ui->treeView->setModel(model);

  QObject::connect(ui->pushButtonOK, &QPushButton::clicked, this, [this]() {
    auto selectionModel = ui->treeView->selectionModel();
    if(selectionModel->hasSelection()) {
      _itemSelecionado = selectionModel->currentIndex();
      this->accept();
    }else {
      QMessageBox::warning(this, "Pesquisa...", "Selecione um registro.");
    }
  });
}

DialogPesquisar::~DialogPesquisar()
{
  delete ui;
}
int DialogPesquisar::linhaSelecionada() const
{
  if(_itemSelecionado.isValid())
    return _itemSelecionado.row();
  else
    return -1;
}
QTreeView *DialogPesquisar::visualizacao()
{
  return ui->treeView;
}
