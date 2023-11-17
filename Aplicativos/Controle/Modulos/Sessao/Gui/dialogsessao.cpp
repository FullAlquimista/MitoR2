//
// Created by Robson on 27/05/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DialogAcessar.h" resolved

#include "dialogsessao.hpp"
#include "ui_dialogsessao.h"
#include <Sessao/ISessao.hpp>
#include <spdlog/spdlog.h>
#include <QMessageBox>
#include <QSqlError>
#include <QApplication>

DialogSessao::DialogSessao(QWidget *parent) : QDialog(parent), ui(new Ui::DialogSessao)
{
  ui->setupUi(this);
  this->setObjectName(Sessao::DialogSessao_ID);

  _acesso = QApplication::instance()->findChild<Sessao::IAcesso *>();
  if(!_acesso) {
    QMessageBox::warning(this, "Caixa de diálogo de uma sessão...", "Falha ao obter o componente 'Sessao'.");
    return;
  }
  ui->lineEditUsuario->setText(_acesso->usuario());

  QObject::connect(ui->pushButton_Acessar, &QPushButton::clicked, this, [this]() {
    if(_acesso->acessarSistema(ui->lineEditUsuario->text(), ui->lineEditSenha->text())) {
      this->ui->lineEditUsuario->setEnabled(false);
      this->ui->lineEditSenha->setEnabled(false);
      this->ui->pushButton_Acessar->setEnabled(false);
      spdlog::info("Usuário '{}' acessou o sistema.", ui->lineEditUsuario->text().toStdString());
      this->close();
    }else {
      QMessageBox::warning(this, "Conexão...", QString("Não foi possível conectar...\n%1").formatArg(_acesso->conexao().lastError().text()));
    }
  });
  QObject::connect(ui->pushButton_Cancelar, &QPushButton::clicked, this, [this]() {
    this->close();
  });

}

DialogSessao::~DialogSessao()
{
  delete ui;
}

#include <QCloseEvent>
void DialogSessao::closeEvent(QCloseEvent *event)
{
  QDialog::closeEvent(event);
}
