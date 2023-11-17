//
// Created by Robson on 22/01/2023.
//
#pragma once

#include <QDialog>
#include <QSqlIndex>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include <MitoR/MitoR.hpp>

QT_BEGIN_NAMESPACE
namespace Ui
{
  class DialogPesquisarCT;
}
QT_END_NAMESPACE

namespace MitoR::Gui
{

  class EXP_IMP_DECL DialogPesquisarCT : public QDialog
  {
    CS_OBJECT(DialogPesquisarCT)

  public:
    enum Roles {
      IdCt = Qt::UserRole + 10,
      IdItemCt,
      IdNoCt,
      NivelCt,
      IndexModelRow
    };
    explicit DialogPesquisarCT(QSqlTableModel *tblModel, QWidget *parent = nullptr);
    ~DialogPesquisarCT() override;
    
    QModelIndex indexSelecionado();

  private:
    Ui::DialogPesquisarCT *ui;
    QSqlTableModel *m_tModel{nullptr};
    QSqlIndex m_idChvPrimaria;
    QSqlTableModel *m_tModelCt{nullptr};
    QStandardItemModel *m_tTreeModel{nullptr};

    void carregarModelo();
    void preencherDadosItem(QStandardItem *no, QStandardItem *item);
  };
} // namespace MitoR::Gui