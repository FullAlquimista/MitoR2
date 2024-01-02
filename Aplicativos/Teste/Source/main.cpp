//
// Created by Robson on 28/06/2023.
//

#include <MitoR/AdaptadorJson.hpp>
#include <MitoR/LinkedRelation.hpp>
#include <QFlatMap>
#include <QJsonDocument>
#include <QtSql>
#include <QtCore>
#include <QtGui>
#include <Sessao/IAcesso.hpp>
#include <spdlog/spdlog.h>
#include <string>

int main(int nArgs, char *args[])
{
  QLocale l;
  QApplication app(nArgs, args);
  QMainWindow mainWindow;
  mainWindow.resize(800, 600);
  QWidget* central = new QWidget(&mainWindow);
  mainWindow.setCentralWidget(central);
  central->setLayout(new QVBoxLayout(central));
  QTreeView* treeView = new QTreeView(central);
  central->layout()->addWidget(treeView);
  QLineEdit *lineEdit = new QLineEdit(central);
  central->layout()->addWidget(lineEdit);
  QDoubleSpinBox *doubleSpinBox = new QDoubleSpinBox(central);
  central->layout()->addWidget(doubleSpinBox);


  QTimer timer;
  QObject::connect(&timer, &QTimer::timeout, &mainWindow, [&mainWindow](){ mainWindow.close(); });

  QSqlDatabase bd = QSqlDatabase::addDatabase("QPSQL");
  if(!bd.isValid()) {
    spdlog::error("Falha ao abrir o driver psql.");
    return -1;
  }
  bd.setHostName("localhost");
  bd.setPort(5432);
  bd.setDatabaseName("controle");
  bd.setUserName("postgres");
  if(!bd.open()) {
    spdlog::error("Falha ao abrir a conexão. {}", bd.lastError().text().toStdString());
    return -2;
  }

  QSqlQuery p(bd);
  if(!p.exec(QString{"select ct.id, ct.id_item, ct.id_no, ct.nivel, c.id as c_id, c.descricao as c_descricao from cadastro.planos_contas_ct ct join cadastro.planos_contas c on ct.id_item = c.id where ct.nivel >= -1 order by ct.id_item ASC;"})) {
      spdlog::error("Falha na consulta do banco de dados. {}", p.lastError().text().toStdString());
  }
  spdlog::info("Linhas consultadas: {}", p.size());
  QMap<int, QStandardItem*> listaItens;
  while(p.next()) {
      QSqlRecord r{p.record()};
//    int64_t ct_id = r.value("id").toInt();
      int64_t ct_id_item = r.value("id_item").toInt();
      int64_t ct_id_no = r.value("id_no").toInt();
      int32_t ct_nivel = r.value("nivel").toInt();
//    int64_t c_id = r.value("c_id").toInt();
      QString c_descricao = r.value("c_descricao").toString();
      if(ct_nivel == -1) {
          auto it_no = listaItens.begin();
          if((it_no = listaItens.find(ct_id_no)) == listaItens.end()) {
              it_no = listaItens.insert(ct_id_no, new QStandardItem);
          }
          auto it_item = listaItens.begin();
          if((it_item = listaItens.find(ct_id_item)) == listaItens.end()) {
              it_item = listaItens.insert(ct_id_item, new QStandardItem);
          }
          QStandardItem* item_no = it_no.value();
          QStandardItem* item = it_item.value();
          item->setText("Sem preenchimento...");
          item_no->appendRow(item);
      }else if(ct_nivel == 0) {
          auto it_item = listaItens.begin();
          if((it_item = listaItens.find(ct_id_item)) == listaItens.end()) {
              it_item = listaItens.insert(ct_id_item, new QStandardItem);
          }
          QStandardItem* item = it_item.value();
          item->setText("Sem preenchimento...");
      }
  }

  QStandardItemModel *model = new QStandardItemModel;
  model->clear();
  model->setHeaderData(0, Qt::Horizontal, QString("Descrição"));
  auto raiz = model->invisibleRootItem();
  for(auto item : listaItens) {
      if(!item->parent()) {
          raiz->appendRow(item);
      }
  }
  treeView->setModel(model);
  QPushButton *botao = new QPushButton("Fechar");
  central->layout()->addWidget(botao);
  QObject::connect(botao, &QPushButton::clicked, treeView, [=]()
  {
      model->clear();
  });

  mainWindow.show();

  //timer.start(2000);
  return app.exec();
}
