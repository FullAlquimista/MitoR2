//
// Created by Robson on 28/06/2023.
//

#include <spdlog/spdlog.h>
#include <string>
#include <MitoR/LinkedRelation.hpp>
#include <QtCore>
#include <QtGui>
#include <QJsonDocument>
#include <QFlatMap>
#include <Sessao/IAcesso.hpp>
#include <MitoR/AdaptadorJson.hpp>

std::string_view jsonString = R"(
{
  "Aplicativo": {
    "MainWindow" : {
      "iNome" : "Janela principal",
      "iDescricao" : "Está é a janela principal do aplicativo",
      "VecPos" : [ 10, 55, 33, 22, 10],
      "MainMenu" : {
        "MenuCadastro" : {
          "iNome" : "Menu cadastro",
          "iDescricao" : "Este contém todas as ações de cadastro.",
          "iAcesso" : 1
        }
      }
    }
  }
}
)";

int main(int nArgs, char *args[])
{
  QLocale l;
  QApplication app(nArgs, args);
  QMainWindow mainWindow;
  mainWindow.resize(800, 600);
  QWidget* central = new QWidget(&mainWindow);
  mainWindow.setCentralWidget(central);
  central->setLayout(new QVBoxLayout(central));
  QLineEdit *lineEdit = new QLineEdit(central);
  central->layout()->addWidget(lineEdit);
  QDoubleSpinBox *doubleSpinBox = new QDoubleSpinBox(central);
  central->layout()->addWidget(doubleSpinBox);


  QTimer timer;
  QObject::connect(&timer, &QTimer::timeout, &mainWindow, [&mainWindow](){ mainWindow.close(); });


  mainWindow.show();

  //timer.start(2000);
  return app.exec();
}