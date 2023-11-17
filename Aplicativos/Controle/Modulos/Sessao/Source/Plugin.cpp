//
// Created by Robson on 14/05/2023.
//

#include "Plugin.hpp"
CS_PLUGIN_REGISTER(Sessao::Plugin)
#include "../Gui/dialogsessao.hpp"
#include "../Gui/formgerenciarusuarios.hpp"
#include <Controle/IControle.hpp>
#include <MitoR/Log.hpp>
#include <QAction>
#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QTabWidget>
#include <Sessao/ISessao.hpp>
#include <spdlog/spdlog.h>

namespace Sessao
{
  Plugin::Plugin(QObject *parent) : QObject(parent)
  {
    auto logger = MitoR::Log::criarLogger("Modulo::Sessao");
    if (logger) {
      spdlog::set_default_logger(logger);
    }
  }
  bool Plugin::construir()
  {
    // Cria o serviço que pode ser obtido através da instancia do aplicativo.
    _acesso = new Sessao::Acesso(QApplication::instance());
    _acesso->cadastrarDispositivoAcesso(Sessao_ID, QString("Módulo: Sessão"), QString("Fornece ao sistema funcionalidades de acesso."), false);

    // Obtem os dispositivos do aplicativo.
    QMainWindow *mainWindow{nullptr};
    auto listaWidgets = QApplication::instance()->allWidgets();
    for (auto widget: listaWidgets) {
      if (widget->objectName() == Controle::MainWindow_ID) {
        mainWindow = dynamic_cast<QMainWindow *>(widget);
        break;
      }
    }
    if (!mainWindow) {
      spdlog::error("Falha ao obter a 'janela principal' do aplicativo.");
      return false;
    }
    QMenuBar *menuBar = mainWindow->findChild<QMenuBar *>(Controle::MenuBar_ID);
    if (!menuBar) {
      spdlog::error("Falha ao obter a 'barra de menu' do aplicativo.");
      return false;
    }
    QTabWidget *tabWidget = mainWindow->findChild<QTabWidget *>(Controle::CentralTabWidget_ID);

    // Diálogo para acessar o sistema.
    QMenu *menuSistema = menuBar->findChild<QMenu *>(Controle::MenuSistema_ID);
    if (!menuSistema) {
      spdlog::error("Falha ao obter o menu 'Sistema'.");
    }
    QMenu *subMenuSessao = menuSistema->findChild<QMenu *>(SubMenuSessao_ID);
    if(!subMenuSessao) subMenuSessao = new QMenu("&Sessão", menuSistema);
    subMenuSessao->setObjectName(SubMenuSessao_ID);
    _acesso->cadastrarDispositivoAcesso(SubMenuSessao_ID, "Sub-menu: Sessão", "Este sub-menu disponibiliza as opções para acessar a sessão do sistema.", false);
    menuSistema->insertAction(menuSistema->actions().front(), subMenuSessao->menuAction());
    QAction *actionAcessar = new QAction(QString("&Acessar"), this);
    actionAcessar->setObjectName(Sessao::ActionAcessar_ID);
    _acesso->cadastrarDispositivoAcesso(Sessao::ActionAcessar_ID, "Action: Acessar", "Abre uma caixa de diálogo para iniciar uma sessão com o sistema.");
    QObject::connect(actionAcessar, &QAction::triggered, this, [mainWindow]() {
      DialogSessao *dialogSessao = mainWindow->findChild<DialogSessao *>();
      if (!dialogSessao) {
        dialogSessao = new DialogSessao(mainWindow);
        QObject::connect(dialogSessao, &DialogSessao::destroyed, mainWindow, [dialogSessao]() mutable {
          dialogSessao = nullptr;
        });
      }
      dialogSessao->exec();
    });
    if(subMenuSessao->actions().isEmpty()) subMenuSessao->addAction(actionAcessar);
    else subMenuSessao->insertAction(subMenuSessao->actions().front(), actionAcessar);


    // Formulário para gerenciar um dispositivo
    QMenu *menuGerenciar{nullptr};
    menuGerenciar = menuBar->findChild<QMenu *>(MenuGerenciar_ID);
    if(!menuGerenciar) {
      menuGerenciar = new QMenu("&Gerenciar", menuBar);
      menuGerenciar->setObjectName(MenuGerenciar_ID);
      _acesso->cadastrarDispositivoAcesso(MenuGerenciar_ID, "Menu: Gerenciar", "Este menu disponibiliza todas as opções de gerenciamento do sistema.", false);
      menuBar->addMenu(menuGerenciar);
    }
    QAction *actionGerenciarUsuarios = new QAction("&Usuários", this);
    actionGerenciarUsuarios->setObjectName(ActionGerenciarUsuarios_ID);
    _acesso->cadastrarDispositivoAcesso(ActionGerenciarUsuarios_ID, QString("Action: Gerenciar usuários"), QString("Esta ação abre o formulário para gerenciar um usuário do sistema."));
    actionGerenciarUsuarios->setEnabled(false);
    QObject::connect(actionGerenciarUsuarios, &QAction::triggered, this, [this, tabWidget]() {
      FormGerenciarUsuarios *formGerenciarUsuarios = tabWidget->findChild<FormGerenciarUsuarios *>(FormGerenciarUsuarios_ID);
      if(!formGerenciarUsuarios) {
        formGerenciarUsuarios = new FormGerenciarUsuarios(tabWidget);
        formGerenciarUsuarios->setObjectName(FormGerenciarUsuarios_ID);
        _acesso->cadastrarDispositivoAcesso(FormGerenciarUsuarios_ID, QString("Formulário: Gerenciar usuários"), QString("Este formulário gerencia um usuário do sistema."), false);
      }
      int index = tabWidget->indexOf(formGerenciarUsuarios);
      if(index < 0) tabWidget->addTab(formGerenciarUsuarios, _acesso->nomeDispositivoAcesso(FormGerenciarUsuarios_ID, "Formulário: Gerenciar usuários"));
      else tabWidget->setCurrentIndex(index);
    });
    if(menuGerenciar->actions().isEmpty()) menuGerenciar->addAction(actionGerenciarUsuarios);
    else menuGerenciar->insertAction(menuGerenciar->actions().front(), actionGerenciarUsuarios);

    QObject::connect(_acesso, &Sessao::IAcesso::sistemaAcessado, this, [this, actionGerenciarUsuarios](QSqlDatabase &, const QString&) {
      if(_acesso->verificarAcesso(actionGerenciarUsuarios->objectName()))
        actionGerenciarUsuarios->setEnabled(true);
    });
    return true;
  }
  bool Plugin::destruir()
  {
    return true;
  }
} // namespace Sessao
