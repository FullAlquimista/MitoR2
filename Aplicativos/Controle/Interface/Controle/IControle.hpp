//
// Created by Robson on 08/06/2023.
//
#pragma once
#include <MitoR/MitoR.hpp>
#include <QStringView>

namespace Controle
{
  const QString Controle_ID("/Controle");
  const QString MainWindow_ID = Controle_ID + "/MainWindow";
  const QString CentralTabWidget_ID = MainWindow_ID + "/TabWidget";
  const QString StatusBar_ID = MainWindow_ID + "/StatusBar";

  const QString MenuBar_ID = MainWindow_ID + "/MenuBar";
  const QString MenuSistema_ID = MenuBar_ID + "/MenuSistema";

  const QString ActionSair_ID = MenuSistema_ID + "/ActionSair";
}