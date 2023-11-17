//
// Created by Robson on 01/10/2022.
//
#pragma once

#include <MitoR/MitoR.hpp>
#include <QDialog>
#include <QAbstractItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class DialogPesquisarTabela; }
QT_END_NAMESPACE

namespace MitoR::Gui {
    class EXP_IMP_DECL DialogPesquisarTabela
        : public QDialog
    {
    CS_OBJECT(DialogPesquisarTabela)
    
    public:
        explicit DialogPesquisarTabela(QAbstractItemModel *ptrModelo, QWidget *parent = nullptr);
        ~DialogPesquisarTabela() override;
        
        QModelIndex indexSelecionado();
    
    private:
        Ui::DialogPesquisarTabela *ui;
        QAbstractItemModel *pModelo{nullptr};
    };
} // MitoR::Gui
