#include <Gui/mainwindow.h>
#include <MitoR/Log.hpp>
#include <MitoR/LinkedRelation.hpp>
#include <QApplication>
#include <QResource>
#include <windows.h>

int main(int nArgs, char *args[])
{
  // Para que as mensagens sejam mostradas corretamente na saída padrão.
  SetConsoleOutputCP(CP_UTF8);

  QApplication app(nArgs, args);

  if (!QResource::registerResource("recursos.rcc")) {
    spdlog::error("Falha ao carregar o arquivo de recursos 'recursos.rcc'.");
    return -1;
  }
  MitoR::Log::inicializar("Log/Controle", spdlog::level::debug);

  MainWindow mainWindow;
  mainWindow.show();

  int r = app.exec();

  MitoR::Log::finalizar();
  return r;
}
