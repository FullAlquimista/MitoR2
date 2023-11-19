//
// Created by Robson on 28/01/2023.
//

#include <mitor/sql/tabelasql.hpp>

#include <QObject>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlIndex>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QStringList>
#include <spdlog/spdlog.h>

namespace MitoR::Sql
{
  // ************************************************************************************
  // Dados internos da classe.
  struct TabelaSql::Impl {
    Impl(TabelaSql *pThisClass) : pClass(pThisClass) {}
    TabelaSql *pClass{nullptr};
    
    static QString removerCaractere(const QString &str, QChar32 c);
    static void extrairEsquemaTabela(const QString str, QString &esquema, QString &tabela);
  };
  QString TabelaSql::Impl::removerCaractere(const QString &str, QChar32 c)
  {
    QString tmp = str;
    for(auto pos=tmp.find(c, 0); pos != -1; pos = tmp.find(c, pos)) {
      tmp.remove(pos, 1);
    }
    return tmp;
  }
  void TabelaSql::Impl::extrairEsquemaTabela(const QString str, QString &esquema, QString &tabela)
  {
    const QString semAspas = removerCaractere(str, '"');
    auto posSeparador = semAspas.find('.');
    if(posSeparador == -1)
      tabela = semAspas;
    else {
      esquema = semAspas.substr(0, posSeparador);
      tabela = semAspas.substr(posSeparador + 1);
    }
  }

  // ************************************************************************************
  // Implementação da classe.
  TabelaSql::TabelaSql(QObject *parent) : QObject(parent)
  {
    pThis = std::make_shared<Impl>(this);
  }
  TabelaSql::~TabelaSql()
  {
  }
  TabelaSql::Erro TabelaSql::inserirRegistro(const QString &nomeTabela, QSqlQuery &consulta, QSqlRecord &registro)
  {
    // Comando para inserir um registro:
    // INSERT INTO tabela (colunas) VALUES (valores);
    QString esquema;
    QString tabela;
    Impl::extrairEsquemaTabela(nomeTabela, esquema, tabela);
    QString identificadorTabela;
    if(esquema.isEmpty())
      identificadorTabela = tabela;
    else
      identificadorTabela = QString(R"("%1"."%2")").formatArgs(esquema, tabela);

    QString colunas;
    QString valores;
    bool bInicio = false;
    auto idx = consulta.driver()->primaryIndex(identificadorTabela);
    for(auto coluna = 0, max=registro.count(); coluna < max; ++coluna) {
      if(registro.fieldName(coluna) == idx.fieldName(0))
        continue;
      if(bInicio) {
        colunas.append(", ");
        valores.append(", ");
      }
      colunas.append(QString(R"("%1")").formatArg(registro.fieldName(coluna)));
      valores.append(QString(":%1").formatArg(registro.fieldName(coluna)));
      bInicio = true;
    }
    
    consulta.prepare(QString(R"(INSERT INTO %1 (%2) VALUES (%3) RETURNING *;)").formatArgs(
        identificadorTabela,
        colunas,
        valores
        ));
    for(auto coluna=0, max=registro.count(); coluna < max; ++coluna) {
      consulta.bindValue(QString(":%1").formatArg(registro.fieldName(coluna)), registro.value(registro.fieldName(coluna)));
    }
    if(!consulta.exec()) {
      return Erro{Erro::Falhou, QString("Falha ao executar o comando INSERT na tabela '%1'").formatArg(tabela)};
    }
    if(consulta.next()) {
      auto res = consulta.record();
      registro.setValue(idx.fieldName(0), res.value(idx.fieldName(0)));
    }
    
    return Erro{Erro::Sucesso, ""};
  }
  TabelaSql::Erro TabelaSql::inserirRegistroComIndex(const QString &nomeTabela, QSqlQuery &consulta, QSqlRecord &registro)
  {
    // Comando para inserir um registro usando a tabela auxiliar .index:
    // WITH registro_inserido AS (INSERT INTO tabela (id, colunas) VALUES ((SELECT id_{tabela} FROM .index LIMIT 1) + 1, valores)) UPDATE .index SET id_{tabela} = :id;
    // INSERT INTO %1 (%2, %3) VALUES ((SELECT %4 FROM %5 LIMIT 1) + 1, %6);
    QString esquema;
    QString tabela;
    Impl::extrairEsquemaTabela(nomeTabela, esquema, tabela);
    QString identificadorTabela;
    QString identificadorTabelaIndex;
    if(esquema.isEmpty()) {
      identificadorTabela = QString(R"("%1")").formatArg(tabela);
      identificadorTabelaIndex = QString(R"("%1")").formatArg(QString("index"));
    }else {
      identificadorTabela = QString(R"("%1"."%2")").formatArgs(esquema, tabela);
      identificadorTabelaIndex = QString(R"("%1"."%2")").formatArgs(esquema, QString("index"));
    }
    
    auto index = consulta.driver()->primaryIndex(QString(identificadorTabela));
    QString colunas;
    QString valores;
    for(auto coluna=0, max=registro.count(); coluna < max; ++coluna) {
      if(coluna != 0) {
        colunas.append(", ");
        valores.append(", ");
      }
      if(registro.fieldName(coluna) == index.fieldName(0)) {
        colunas.append(QString(R"("%1")").formatArg(registro.fieldName(coluna)));
        valores.append(QString(R"((SELECT "%1_%2" FROM %3 LIMIT 1))").formatArgs(index.fieldName(0), tabela, identificadorTabelaIndex));
      }else {
        colunas.append(QString(R"("%1")").formatArg(registro.fieldName(coluna)));
        valores.append(QString(":%1").formatArg(registro.fieldName(coluna)));
      }
    }
    
    QString comando = QString(R"(WITH "registro_inserido" AS (INSERT INTO %1 (%2) VALUES (%3) RETURNING *), "registro_atualizdo" AS (UPDATE %4 SET "%5_%6" = "registro_inserido"."%7" + 1 FROM "registro_inserido" RETURNING *) SELECT id FROM "registro_inserido";)")
                          .formatArgs(identificadorTabela, colunas, valores, identificadorTabelaIndex, index.fieldName(0), tabela, index.fieldName(0));
    consulta.prepare(comando);
    for(auto coluna=0, max=registro.count(); coluna < max; ++coluna) {
      if(registro.fieldName(coluna) != index.fieldName(0))
        consulta.bindValue(QString(":%1").formatArg(registro.fieldName(coluna)), registro.value(coluna));
    }
    if(!consulta.exec()) {
      spdlog::info("{}", comando.toStdString());
      return {Erro::Falhou, QString("Falha ao executar o comando de inserção na tabela '%1' com tabela auxiliar 'index'.").formatArg(tabela)};
    }
    if(consulta.next()) {
      auto res = consulta.record();
      registro.setValue(index.fieldName(0), res.value(index.fieldName(0)));
    }
    return Erro{Erro::Sucesso, ""};
  }

} // namespace MitoR::Sql