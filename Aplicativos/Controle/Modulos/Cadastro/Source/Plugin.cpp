//
// Created by Robson on 14/05/2023.
//

#include "Plugin.hpp"
CS_PLUGIN_REGISTER(Cadastro::Plugin)
#include <MitoR/Log.hpp>
#include <Controle/IControle.hpp>
#include <Cadastro/ICadastro.hpp>
#include <Gui/formcadastrarempresa.hpp>
#include <Gui/formcadastrarplanoconta.hpp>
#include <Gui/formcadastrarunidadesmedidas.hpp>
#include <Gui/formcadastrarclassificacoesmateriais.hpp>
#include <Gui/formcadastrarformatomateriais.hpp>
#include <Gui/formcadastrartiposmateriais.hpp>
#include <Gui/formcadastrarmateriais.hpp>
#include <spdlog/spdlog.h>
#include <QApplication>
#include <QWindow>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QTabWidget>
#include <QAction>

namespace Cadastro
{
  Plugin::Plugin(QObject *parent) : QObject(parent)
  {
    auto logger = MitoR::Log::criarLogger("Modulo::Cadastro");
    if(logger) {
      spdlog::set_default_logger(logger);
    }
  }
  bool Plugin::construir()
  {
    _acesso = QApplication::instance()->findChild<Sessao::IAcesso*>();
    if(!_acesso) {
      spdlog::error("Falha ao obter o 'acesso' a sessão atual.");
      return false;
    }
    _acesso->cadastrarDispositivoAcesso(Cadastro_ID, "Módulo: Cadastro", "Este módulo fornece todas as funcionalidades necessárias para cadastrar.", false);

    // Obtendo os dispositivos principais.
    auto listaJanelas = QApplication::allWidgets();
    QMainWindow *mainWindow{nullptr};
    for(auto janela : listaJanelas) {
      if(janela->objectName() == Controle::MainWindow_ID) {
        mainWindow = dynamic_cast<QMainWindow *>(janela);
        break;
      }
    }
    if(!mainWindow) {
      spdlog::error("Falha ao obter a 'janela principal' do aplicativo.");
      return false;
    }
    QTabWidget *tabWidget = mainWindow->findChild<QTabWidget*>(Controle::CentralTabWidget_ID);
    if(!tabWidget) {
      spdlog::error("Falha ao obter o dispositivo 'tab widget' do aplicativo.");
      return false;
    }
    // Criando os menus.
    auto menuBar = mainWindow->findChild<QMenuBar*>(Controle::MenuBar_ID);
    if(!menuBar) {
      spdlog::error("Falha ao obter a 'barra de menu' do aplicativo.");
      return false;
    }
    auto menuSistema = mainWindow->findChild<QMenu*>(Controle::MenuSistema_ID);
    if(!menuSistema) {
      spdlog::error("Falha ao obter a menu 'Sistema' do aplicativo.");
      return false;
    }
    auto menuCadastrar = new QMenu("&Cadastrar", menuBar);
    menuCadastrar->setObjectName(Cadastro::MenuCadastro_ID);
    _acesso->cadastrarDispositivoAcesso(MenuCadastro_ID, "Menu: Cadastrar", "Este menu mostra todas as opções de cadastro.", false);
    menuBar->insertMenu(menuSistema->menuAction(), menuCadastrar);
    auto subMenuInfoCadastro = menuCadastrar->findChild<QMenu*>(Cadastro::SubMenuInfoCadastro_ID);
    if(!subMenuInfoCadastro) {
      subMenuInfoCadastro = new QMenu("Informações &Cadastro");
      subMenuInfoCadastro->setObjectName(Cadastro::SubMenuInfoCadastro_ID);
      _acesso->cadastrarDispositivoAcesso(Cadastro::SubMenuInfoCadastro_ID, "Sub-menu: Informações de Cadastro.", "Este sub-menu contém todos os forumlários de cadastro de informações de objetos no sistema.", false);
    }
    menuCadastrar->addMenu(subMenuInfoCadastro);

    // Criando ações.
    // Formulário de cadastro de uma empresa.
    actionCadastrarEmpresa = new QAction("&Empresa", this);
    actionCadastrarEmpresa->setObjectName(ActionCadastrarEmpresa_ID);
    _acesso->cadastrarDispositivoAcesso(ActionCadastrarEmpresa_ID, "Action: Cadastrar Empresa", "Esta ação abre o formulário para cadastrar uma empresa.");
    actionCadastrarEmpresa->setEnabled(false);
    QObject::connect(actionCadastrarEmpresa, &QAction::triggered, this, [this, tabWidget](bool) {
      FormCadastrarEmpresa *formCadastrarEmpresa = tabWidget->findChild<FormCadastrarEmpresa*>(Cadastro::FormCadastrarEmpresa_ID);
      if(!formCadastrarEmpresa) {
        formCadastrarEmpresa = new FormCadastrarEmpresa(tabWidget);
        formCadastrarEmpresa->setObjectName(Cadastro::FormCadastrarEmpresa_ID);
        _acesso->cadastrarDispositivoAcesso(Cadastro::FormCadastrarEmpresa_ID, QString("Formulário: Cadastrar Empresa"), QString("Este formulário é utilizado para cadastrar uma empresa como: cliente, fornecedor ou fabricante."), false);
      }
      int index = tabWidget->indexOf(formCadastrarEmpresa);
      if(index < 0)
        tabWidget->addTab(formCadastrarEmpresa, _acesso->nomeDispositivoAcesso(Cadastro::FormCadastrarEmpresa_ID, "Formulário: Cadastrar Empresa"));
      else
        tabWidget->setCurrentIndex(index);
    });
    subMenuInfoCadastro->addAction(actionCadastrarEmpresa);

    // Formulário de cadastro de um novo plano de conta.
    actionCadastrarPlanoConta = new QAction("&Plano de conta", this);
    actionCadastrarPlanoConta->setObjectName(ActionCadastrarPlanoConta_ID);
    _acesso->cadastrarDispositivoAcesso(ActionCadastrarPlanoConta_ID, "Action: Cadastrar Plano de Conta", "Esta ação abre o formulário para cadastrar um novo plano de conta.");
    actionCadastrarPlanoConta->setEnabled(false);
    QObject::connect(actionCadastrarPlanoConta, &QAction::triggered, this, [this, tabWidget](bool) {
      FormCadastrarPlanoConta *formCadastrarPlanoConta = tabWidget->findChild<FormCadastrarPlanoConta *>(Cadastro::FormCadastrarPlanoConta_ID);
      if(!formCadastrarPlanoConta) {
        formCadastrarPlanoConta = new FormCadastrarPlanoConta(tabWidget);
        formCadastrarPlanoConta->setObjectName(Cadastro::FormCadastrarPlanoConta_ID);
        _acesso->cadastrarDispositivoAcesso(Cadastro::FormCadastrarPlanoConta_ID, QString("Formulário: Cadastrar Plano de Conta"), QString("Este formulário é utilizado para cadastrar, alterar ou remover um plano de conta."), false);
      }
      int index = tabWidget->indexOf(formCadastrarPlanoConta);
      if(index < 0)
        tabWidget->addTab(formCadastrarPlanoConta, _acesso->nomeDispositivoAcesso(Cadastro::FormCadastrarPlanoConta_ID, "Formulário: Cadastrar Plano de Conta"));
      else
        tabWidget->setCurrentIndex(index);
    });
    subMenuInfoCadastro->addAction(actionCadastrarPlanoConta);

    // Formulário de cadastro de uma nova unidade de medida.
    actionCadastrarUnidadesMedidas = new QAction("&Unidade Medida", this);
    actionCadastrarUnidadesMedidas->setObjectName(ActionCadastrarUnidadesMedidas_ID);
    _acesso->cadastrarDispositivoAcesso(ActionCadastrarUnidadesMedidas_ID, "Action: Cadastrar Unidade Medida", "Esta ação abre o formulário para cadastrar uma nova unidade de medida no sistema.");
    actionCadastrarUnidadesMedidas->setEnabled(false);
    QObject::connect(actionCadastrarUnidadesMedidas, &QAction::triggered, this, [this, tabWidget](bool) {
      FormCadastrarUnidadesMedidas *formCadastrarUnidadesMedidas = tabWidget->findChild<FormCadastrarUnidadesMedidas*>(Cadastro::FormCadastrarUnidadesMedidas_ID);
      if(!formCadastrarUnidadesMedidas) {
        formCadastrarUnidadesMedidas = new FormCadastrarUnidadesMedidas(tabWidget);
        formCadastrarUnidadesMedidas->setObjectName(Cadastro::FormCadastrarUnidadesMedidas_ID);
        _acesso->cadastrarDispositivoAcesso(Cadastro::FormCadastrarUnidadesMedidas_ID, QString("Formulário: Cadastrar Unidade de Medida"), QString("Este formulário é utilizado para cadastrar uma nova unidade de medida no sistema. Ex: mm, s, kg..."), false);
      }
      int index = tabWidget->indexOf(formCadastrarUnidadesMedidas);
      if(index < 0)
        tabWidget->addTab(formCadastrarUnidadesMedidas, _acesso->nomeDispositivoAcesso(Cadastro::FormCadastrarUnidadesMedidas_ID, "Formulário: Cadastrar Unidade de Medida"));
      else
        tabWidget->setCurrentIndex(index);
    });
    subMenuInfoCadastro->addAction(actionCadastrarUnidadesMedidas);

    // Formulário de cadastro das classificações de materiais.
    actionCadastrarClassificacoesMateriais = new QAction("C&lassificações de Materiais", this);
    actionCadastrarClassificacoesMateriais->setObjectName(ActionCadastrarClassificacoesMateriais_ID);
    _acesso->cadastrarDispositivoAcesso(ActionCadastrarClassificacoesMateriais_ID, "Action: Cadastrar uma classificaçao de material.", "Esta ação abre o formulário para cadastrar uma nova classificação de material no sistema.");
    actionCadastrarClassificacoesMateriais->setEnabled(false);
    QObject::connect(actionCadastrarClassificacoesMateriais, &QAction::triggered, this, [this, tabWidget](bool) {
      FormCadastrarClassificacoesMateriais *formCadastrarClassificacoesMateriais = tabWidget->findChild<FormCadastrarClassificacoesMateriais*>(Cadastro::FormCadastrarClassificacoesMateriais_ID);
      if(!formCadastrarClassificacoesMateriais) {
        formCadastrarClassificacoesMateriais = new FormCadastrarClassificacoesMateriais(tabWidget);
        formCadastrarClassificacoesMateriais->setObjectName(Cadastro::FormCadastrarClassificacoesMateriais_ID);
        _acesso->cadastrarDispositivoAcesso(Cadastro::FormCadastrarClassificacoesMateriais_ID, QString("Formulário: Cadastrar Classificações de Materiais"), QString("Este formulário é utilizado para cadastrar uma nova classificação de material no sistema. Ex: Parafuso, Cabeça abaulada..."), false);
      }
      int index = tabWidget->indexOf(formCadastrarClassificacoesMateriais);
      if(index < 0)
        tabWidget->addTab(formCadastrarClassificacoesMateriais, _acesso->nomeDispositivoAcesso(Cadastro::FormCadastrarClassificacoesMateriais_ID, "Formulário: Cadastrar Classificações de Materiais"));
      else
        tabWidget->setCurrentIndex(index);
    });
    subMenuInfoCadastro->addAction(actionCadastrarClassificacoesMateriais);

    // Formulário de cadastro formato de materiais.
    actionCadastrarFormatoMateriais = new QAction("&Formato de material", this);
    actionCadastrarFormatoMateriais->setObjectName(ActionCadastrarFormatoMateriais_ID);
    _acesso->cadastrarDispositivoAcesso(ActionCadastrarFormatoMateriais_ID, "Action: Cadastrar Formato de Material", "Esta ação abre o formulário para cadastrar novos formatos de materiais.");
    actionCadastrarFormatoMateriais->setEnabled(false);
    QObject::connect(actionCadastrarFormatoMateriais, &QAction::triggered, this, [this, tabWidget](bool) {
      FormCadastrarFormatoMateriais *formCadastrarFormatoMateriais = tabWidget->findChild<FormCadastrarFormatoMateriais*>(Cadastro::FormCadastrarFormatoMateriais_ID);
      if(!formCadastrarFormatoMateriais) {
        formCadastrarFormatoMateriais = new FormCadastrarFormatoMateriais(tabWidget);
        formCadastrarFormatoMateriais->setObjectName(Cadastro::FormCadastrarFormatoMateriais_ID);
        _acesso->cadastrarDispositivoAcesso(Cadastro::FormCadastrarFormatoMateriais_ID, QString("Formulário: Cadastrar Formatos de materiais"), QString("Este formulário é utilizado para cadastrar um novo formato de material: barra redonda, barra chata..."), false);
      }
      int index = tabWidget->indexOf(formCadastrarFormatoMateriais);
      if(index < 0)
        tabWidget->addTab(formCadastrarFormatoMateriais, _acesso->nomeDispositivoAcesso(Cadastro::FormCadastrarFormatoMateriais_ID, "Formulário: Cadastrar Formatos de Materiais"));
      else
        tabWidget->setCurrentIndex(index);
    });
    subMenuInfoCadastro->addAction(actionCadastrarFormatoMateriais);

    // Formulário de cadastro dos tipos de materiais.
    actionCadastrarTiposMateriais = new QAction("&Tipo de material", this);
    actionCadastrarTiposMateriais->setObjectName(ActionCadastrarTiposMateriais_ID);
    _acesso->cadastrarDispositivoAcesso(ActionCadastrarTiposMateriais_ID, "Action: Cadastrar Tipos Materiais", "Esta ação abre o formulário para cadastrar um novo tipo de material.");
    actionCadastrarTiposMateriais->setEnabled(false);
    QObject::connect(actionCadastrarTiposMateriais, &QAction::triggered, this, [this, tabWidget](bool) {
      FormCadastrarTiposMateriais *formCadastrarTiposMateriais = tabWidget->findChild<FormCadastrarTiposMateriais*>(Cadastro::FormCadastrarTiposMateriais_ID);
      if(!formCadastrarTiposMateriais) {
        formCadastrarTiposMateriais = new FormCadastrarTiposMateriais(tabWidget);
        formCadastrarTiposMateriais->setObjectName(Cadastro::FormCadastrarTiposMateriais_ID);
        _acesso->cadastrarDispositivoAcesso(Cadastro::FormCadastrarTiposMateriais_ID, QString("Formulário: Cadastrar Tipos Materiais"), QString("Este formulário é utilizado para cadastrar um novo tipo de material. Ex: Aço Prata, Aço 1020."), false);
      }
      int index = tabWidget->indexOf(formCadastrarTiposMateriais);
      if(index < 0)
        tabWidget->addTab(formCadastrarTiposMateriais, _acesso->nomeDispositivoAcesso(Cadastro::FormCadastrarTiposMateriais_ID, "Formulário: Cadastrar Tipos Materiais"));
      else
        tabWidget->setCurrentIndex(index);
    });
    subMenuInfoCadastro->addAction(actionCadastrarTiposMateriais);

    // Formulário de cadastro dos materiais.
    actionCadastrarMateriais = new QAction("&Material", this);
    actionCadastrarMateriais->setObjectName(ActionCadastrarMateriais_ID);
    _acesso->cadastrarDispositivoAcesso(ActionCadastrarMateriais_ID, "Action: Cadastrar Materiais", "Esta ação abre o formulário para cadastrar um novo material.");
    actionCadastrarMateriais->setEnabled(false);
    QObject::connect(actionCadastrarMateriais, &QAction::triggered, this, [this, tabWidget](bool) {
      FormCadastrarMateriais *formCadastrarMateriais = tabWidget->findChild<FormCadastrarMateriais*>(Cadastro::FormCadastrarMateriais_ID);
      if(!formCadastrarMateriais) {
        formCadastrarMateriais = new FormCadastrarMateriais(tabWidget);
        formCadastrarMateriais->setObjectName(Cadastro::FormCadastrarMateriais_ID);
        _acesso->cadastrarDispositivoAcesso(Cadastro::FormCadastrarMateriais_ID, QString("Formulário: Cadastrar Materiais"), QString("Este formulário é utilizado para cadastrar um novo material. Ex: CLP FPX, etc..."), false);
      }
      int index = tabWidget->indexOf(formCadastrarMateriais);
      if(index < 0)
        tabWidget->addTab(formCadastrarMateriais, _acesso->nomeDispositivoAcesso(Cadastro::FormCadastrarMateriais_ID, "Formulário: Materiais"));
      else
        tabWidget->setCurrentIndex(index);
    });
    subMenuInfoCadastro->addAction(actionCadastrarMateriais);

    QObject::connect(_acesso, SIGNAL(sistemaAcessado(QSqlDatabase &, const QString &)), this, SLOT(verificarSeguranca()));
    return true;
  }
  bool Plugin::destruir()
  {
    return true;
  }
  void Plugin::verificarSeguranca()
  {
    if(_acesso->verificarAcesso(actionCadastrarEmpresa->objectName()))
      actionCadastrarEmpresa->setEnabled(true);
    if(_acesso->verificarAcesso(actionCadastrarPlanoConta->objectName()))
      actionCadastrarPlanoConta->setEnabled(true);
    if(_acesso->verificarAcesso(actionCadastrarUnidadesMedidas->objectName()))
      actionCadastrarUnidadesMedidas->setEnabled(true);
    if(_acesso->verificarAcesso(actionCadastrarClassificacoesMateriais->objectName()))
      actionCadastrarClassificacoesMateriais->setEnabled(true);
    if(_acesso->verificarAcesso(actionCadastrarFormatoMateriais->objectName()))
      actionCadastrarFormatoMateriais->setEnabled(true);
    if(_acesso->verificarAcesso(actionCadastrarTiposMateriais->objectName()))
      actionCadastrarTiposMateriais->setEnabled(true);
    if(_acesso->verificarAcesso(actionCadastrarMateriais->objectName()))
      actionCadastrarMateriais->setEnabled(true);
  }
} // namespace Sessao