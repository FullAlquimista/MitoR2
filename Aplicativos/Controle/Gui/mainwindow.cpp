//
// Created by Robson on 15/04/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <MitoR/Configuracao.hpp>
#include <MitoR/Modulo.hpp>
#include <Controle/IControle.hpp>
#include <QCloseEvent>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this->setObjectName(Controle::MainWindow_ID);
  ui->tabWidget->setObjectName(Controle::CentralTabWidget_ID);
  ui->menubar->setObjectName(Controle::MenuBar_ID);
  ui->menu_Sistema->setObjectName(Controle::MenuSistema_ID);
  ui->action_Sair->setObjectName(Controle::ActionSair_ID);
  ui->statusbar->setObjectName(Controle::StatusBar_ID);
  ui->tabWidget->setTabsClosable(true);

  setWindowIcon(QIcon(QString(":/Imagens/icone.png")));
  setWindowTitle("Controle A.M.E.");

  MitoR::Configuracao cfg(QString("Controle"), QFileInfo("Controle.json"));

  // Sinais.
  QObject::connect(ui->action_Sair, &QAction::triggered, this, [this]() {
    this->close();
  });
  QObject::connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, [this](int idx) {
    QWidget *w = ui->tabWidget->widget(idx);
    ui->tabWidget->removeTab(idx);
    w->deleteLater();
  });
}

MainWindow::~MainWindow()
{
  delete ui;
}
void MainWindow::showEvent(QShowEvent *event)
{
  static bool carregado = false;
  if (!carregado) {
    carregarConfiguracoes();
    carregarModulos();
  }
  QWidget::showEvent(event);
}
void MainWindow::closeEvent(QCloseEvent *e)
{
  auto op = QMessageBox::question(this, "Sair...", "Deseja realmente sair ?", "Sim", "Não");
  if (op == 0) {
    MitoR::Modulo::descarregarTodosModulos();
    salvarConfiguracoes();
    e->accept();
    return;
  }
  e->ignore();
}
void MainWindow::carregarConfiguracoes()
{
  MitoR::Configuracao cfg(QString("Controle"));

  const QString caminhoGeo = "/Aplicativos/Controle/MainWindow/geometry";
  const QString caminhoState = "/Aplicativos/Controle/MainWindow/state";
  {
    QByteArray arr;
    if (!cfg.array(caminhoGeo, &arr)) {
      spdlog::warn("Não foi possível encontrar as informações da geometria da janela principal.");
      return;
    }
    if (!restoreGeometry(QByteArray::fromHex(arr))) {
      spdlog::warn("Falha ao restaurar Sessao geometria da janela principal.");
    }
  }
  {
    QByteArray arr;
    if (!cfg.array(caminhoState, &arr)) {
      spdlog::warn("Não foi possível encontrar as informações de estado da janela principal.");
      return;
    }
    if (!restoreState(QByteArray::fromHex(arr))) {
      spdlog::warn("Falha ao restaurar o estado da janela principal.");
    }
  }
}
void MainWindow::salvarConfiguracoes()
{
  MitoR::Configuracao cfg(QString("Controle"));

  const QString caminhoGeo = "/Aplicativos/Controle/MainWindow/geometry";
  const QString caminhoState = "/Aplicativos/Controle/MainWindow/state";
  if (!cfg.array(caminhoGeo, saveGeometry().toHex())) {
    spdlog::warn("Falha ao tentar salvar a geometria da janela.");
  }
  if (!cfg.array(caminhoState, saveState().toHex())) {
    spdlog::warn("Falha ao tentar salvar o estado da janela.");
  }
}
void MainWindow::carregarModulos()
{
  QDir dirModulos("Modulos");
  auto listaArquivos = dirModulos.entryInfoList({"*.json"});
  for (auto arquivo: listaArquivos) {
    if (arquivo.exists()) {
      MitoR::Modulo modulo(arquivo);
    }
  }
  _acesso = QApplication::instance()->findChild<Sessao::IAcesso*>();
  if(_acesso) {
    _acesso->cadastrarDispositivoAcesso(Controle::Controle_ID, "Aplicativo: Controle", "Este é o aplicativo principal que disponibiliza os módulos.", false);
    _acesso->cadastrarDispositivoAcesso(Controle::MenuSistema_ID, "Menu: Sistema", "Este menu contém as principais opções para acessar o sistema.", false);
  }
}
