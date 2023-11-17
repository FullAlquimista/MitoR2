//
// Created by Robson on 28/05/2023.
//
#pragma once

#include <MitoR/MitoR.hpp>
#include <QDialog>
#include <QAbstractItemModel>
class QTreeView;

QT_BEGIN_NAMESPACE
namespace Ui
{
  class DialogPesquisar;
}
QT_END_NAMESPACE

class EXP_IMP_DECL DialogPesquisar : public QDialog
{
  CS_OBJECT(DialogPesquisar)

public:
  explicit DialogPesquisar(QAbstractItemModel *model, QWidget *parent = nullptr);
  ~DialogPesquisar() override;

  int linhaSelecionada() const;
  QTreeView* visualizacao();

private:
  Ui::DialogPesquisar *ui;
  QAbstractItemModel *_model{nullptr};
  QModelIndex _itemSelecionado;
};
