//
// Created by Robson on 15/04/2023.
//
#pragma once

#include <QMainWindow>
#include <Sessao/IAcesso.hpp>

QT_BEGIN_NAMESPACE
namespace Ui
{
  class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  CS_OBJECT(MainWindow)

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

protected:
  void showEvent(QShowEvent *event) override;
  void closeEvent(QCloseEvent *e) override;
  void carregarConfiguracoes();
  void salvarConfiguracoes();
  void carregarModulos();
  void descarregarModulos();

private:
  Ui::MainWindow *ui;
  Sessao::IAcesso *_acesso;
};