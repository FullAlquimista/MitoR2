//
// Created by Robson on 14/05/2023.
//

#include "Plugin.hpp"
CS_PLUGIN_REGISTER(Producao::Plugin)
#include <Controle/IControle.hpp>
#include <Producao/IProducao.hpp>
#include <Cadastro/ICadastro.hpp>
#include <Gui/formcadastrartipospropostas.hpp>
#include <Gui/formorcamento.hpp>
#include <MitoR/Log.hpp>
#include <spdlog/spdlog.h>
#include <QApplication>
#include <QMainWindow>
#include <QWindow>
#include <QMenuBar>
#include <QMenu>

namespace Producao
{
  Plugin::Plugin(QObject *parent) : QObject(parent)
  {
    auto logger = MitoR::Log::criarLogger("Modulo::Producao");
    if(logger) {
      spdlog::set_default_logger(logger);
    }
  }
  bool Plugin::construir()
  {
    switch(MitoR::Erro e = [this]()->MitoR::Erro {
      _acesso = QApplication::instance()->findChild<Sessao::IAcesso*>();
      if(!_acesso)
        return {MitoR::Erro::Falha, "Falha ao obter o serviço do módulo 'Sessão', IAcesso."};
      QMainWindow *mainWindow{nullptr};
      auto listaWidgets = QApplication::instance()->allWidgets();
      auto itRes = std::find_if(listaWidgets.begin(), listaWidgets.end(), [](auto janela) {
        return janela->objectName() == Controle::MainWindow_ID;
      });
      if(itRes == listaWidgets.end())
        return {MitoR::Erro::Falha, "Falha ao obter a janela principal do aplicativo."};
      mainWindow = dynamic_cast<QMainWindow*>(*itRes);
      QTabWidget *tabWidget = mainWindow->findChild<QTabWidget*>(Controle::CentralTabWidget_ID);
      if(!tabWidget)
        return {MitoR::Erro::Falha, "Falha ao obter o dispositivo central tab widget."};
      QMenuBar *menuBar = mainWindow->findChild<QMenuBar*>(Controle::MenuBar_ID);
      if(!menuBar)
        return {MitoR::Erro::Falha, "Falha ao obter a barra de menu principal do aplicativo."};
      QMenu *menuCadastro = menuBar->findChild<QMenu*>(Cadastro::MenuCadastro_ID);
      if(!menuCadastro)
        return {MitoR::Erro::Falha, "Falha ao obter o menu Cadastro."};
      QMenu *subMenuInfoProducao = menuCadastro->findChild<QMenu*>(Producao::SubMenuInfoProducao_ID);
      if(!subMenuInfoProducao) {
        subMenuInfoProducao = new QMenu("Informações &Produção");
        subMenuInfoProducao->setObjectName(Producao::SubMenuInfoProducao_ID);
        _acesso->cadastrarDispositivoAcesso(Producao::SubMenuInfoProducao_ID, "Sub-menu: Informações da Produção.", "Este sub-menu contém todos os forumlários de cadastro de informações da produção do sistema.", false);
      }
      menuCadastro->addMenu(subMenuInfoProducao);

      // Adicionando ações:
      // Formulário para cadastrar um novo tipo de proposta.
      actionFormCadastrarTiposPropostas = new QAction("Tipo de uma &Proposta", this);
      actionFormCadastrarTiposPropostas->setObjectName(Producao::ActionCadastrarTiposPropostas_ID);
      _acesso->cadastrarDispositivoAcesso(Producao::ActionCadastrarTiposPropostas_ID, "Action: Cadastrar tipo de uma Proposta", "Esta ação abre o formulário para cadastrar um novo tipo de proposta.");
      actionFormCadastrarTiposPropostas->setEnabled(false);
      QObject::connect(actionFormCadastrarTiposPropostas, &QAction::triggered, this, [this, tabWidget](bool) {
        FormCadastrarTiposPropostas *formCadastrarTiposPropostas = tabWidget->findChild<FormCadastrarTiposPropostas*>(Producao::FormCadastrarTiposPropostas_ID);
        if(!formCadastrarTiposPropostas) {
          formCadastrarTiposPropostas = new FormCadastrarTiposPropostas(tabWidget);
          formCadastrarTiposPropostas->setObjectName(Producao::FormCadastrarTiposPropostas_ID);
          _acesso->cadastrarDispositivoAcesso(Producao::FormCadastrarTiposPropostas_ID, QString("Formulário: Cadastrar Tipo de uma Proposta"), QString("Este formulário é utilizado para cadastrar um novo tipo de proposta como: fabricação, serviço, etc."), false);
        }
        int index = tabWidget->indexOf(formCadastrarTiposPropostas);
        if(index < 0)
          tabWidget->addTab(formCadastrarTiposPropostas, _acesso->nomeDispositivoAcesso(Producao::FormCadastrarTiposPropostas_ID, "Formulário: Cadastrar Tipo de uma Proposta"));
        else
          tabWidget->setCurrentIndex(index);
      });
      subMenuInfoProducao->addAction(actionFormCadastrarTiposPropostas);

      // Adicionando ações:
      // Formulário para criar um novo orçamento.
      actionFormOrcamento = new QAction("&Orçamento", this);
      actionFormOrcamento->setObjectName(Producao::ActionOrcamento_ID);
      _acesso->cadastrarDispositivoAcesso(Producao::ActionOrcamento_ID, "Action: Abrir Orçamento", "Esta ação abre o formulário para cadastrar um novo orçamento.");
      actionFormOrcamento->setEnabled(false);
      QObject::connect(actionFormOrcamento, &QAction::triggered, this, [this, tabWidget, mainWindow](bool) {
        FormOrcamento *formOrcamento = tabWidget->findChild<FormOrcamento*>(Producao::FormOrcamento_ID);
        if(!formOrcamento) {
          formOrcamento = new FormOrcamento(tabWidget, mainWindow, tabWidget);
          formOrcamento->setObjectName(Producao::FormOrcamento_ID);
          _acesso->cadastrarDispositivoAcesso(Producao::FormOrcamento_ID, QString("Formulário: Orçamento"), QString("Este formulário é utilizado para registrar um novo orçamento."), false);
        }
        int index = tabWidget->indexOf(formOrcamento);
        if(index < 0)
          tabWidget->addTab(formOrcamento, _acesso->nomeDispositivoAcesso(Producao::FormOrcamento_ID, "Formulário: Orçamento"));
        else
          tabWidget->setCurrentIndex(index);
      });
      subMenuInfoProducao->addAction(actionFormOrcamento);

      QObject::connect(_acesso, SIGNAL(sistemaAcessado(QSqlDatabase &, const QString&)), this, SLOT(verificarSeguranca()));

      return {MitoR::Erro::Sucesso};
    }()) {
      case MitoR::Erro::Sucesso: {
        return true;
      }break;
      case MitoR::Erro::Falha: {
        spdlog::error("Falha ao construir o módulo. \n{}", e.msg.toStdString());
      }break;
    }
    return false;
  }
  bool Plugin::destruir()
  {
    return true;
  }
  QSharedPointer<QObject> Plugin::servico(const QString &)
  {
    return QSharedPointer<QObject>();
  }
  bool Plugin::temServico(const QString &) const
  {
    return false;
  }
  void Plugin::verificarSeguranca()
  {
    if(_acesso->verificarAcesso(actionFormCadastrarTiposPropostas->objectName()))
      actionFormCadastrarTiposPropostas->setEnabled(true);
    if(_acesso->verificarAcesso(actionFormOrcamento->objectName()))
      actionFormOrcamento->setEnabled(true);
  }
} // namespace Sessao