//
// Created by Robson on 05/02/2023.
//

#include "mitor/sql/tabelactsql.hpp"
#include <QSqlRecord>
#include <QSqlDriver>
#include <QSqlIndex>
#include <spdlog/spdlog.h>

namespace MitoR::Sql
{
  struct TabelaCtSql::Impl
  {
    Impl(TabelaCtSql *classe) : pClass(classe) {}
    void inicializar(const QString &nomeTabela)
    {
      extrairEsquemaTabela(nomeTabela, esquema, tabela);
      if(esquema.isEmpty())
        tabelaSql = QString(R"("%1")").formatArg(tabela);
      else
        tabelaSql = QString(R"("%1"."%2")").formatArgs(esquema, tabela);
      extrairTabelaAuxiliarCt();
      if(esquema.isEmpty())
        tabelaCtSql = QString(R"("%1")").formatArg(tabelaCt);
      else
        tabelaCtSql = QString(R"("%1"."%2")").formatArgs(esquema, tabelaCt);
    }
    
    static QString removerCaractere(const QString &str, QChar32 c)
    {
      QString tmp = str;
      for(auto pos=tmp.find(c, 0); pos != -1; pos = tmp.find(c, pos)) {
        tmp.remove(pos, 1);
      }
      return tmp;
    }
    static void extrairEsquemaTabela(const QString str, QString &esquema, QString &tabela)
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
    void extrairTabelaAuxiliarCt()
    {
      tabelaCt = QString("%1_ct").formatArg(tabela);
    }
    
    TabelaCtSql *pClass;
    QString esquema;
    QString tabela;
    QString tabelaSql;
    QString tabelaCt;
    QString tabelaCtSql;
  };
  
  TabelaCtSql::TabelaCtSql(const QString &nomeTabela, QObject *parent) : QObject(parent)
  {
    pThis = std::make_shared<Impl>(this);
    pThis->inicializar(nomeTabela);
  }
  TabelaCtSql::~TabelaCtSql()
  {
  }

  TabelaCtSql::Erro TabelaCtSql::inserirRegistro(QSqlRecord &registro, QSqlQuery &consulta, const QVariant id_no)
  {
    QString colunas;
    QString valores;
    for(int coluna=0, max=registro.count(); coluna < max; ++coluna) {
      if(coluna != 0) {
        colunas.append(", ");
        valores.append(", ");
      }
      colunas.append(QString(R"("%1")").formatArg(registro.fieldName(coluna)));
      valores.append(QString(":%1").formatArg(registro.fieldName(coluna)));
    }
    const QString cmdInserirTabela = R"(INSERT INTO %1 (%2) VALUES (%3) RETURNING *)";
    const QString cmdInserirTabelaCt = R"(INSERT INTO %1 (id_item, id_no, nivel) ( SELECT ii.id, ii.id, 0 FROM item_inserido AS ii UNION ALL SELECT ii.id, lk.id_no, lk.nivel - 1 FROM item_inserido AS ii, %2 AS lk WHERE id_item = %3 ) RETURNING *)";
    const QString comando = QString("WITH item_inserido AS ( %1 ), itens_inseridos_ct AS ( %2 ) SELECT * FROM item_inserido;")
                                .formatArg( cmdInserirTabela.formatArgs(pThis->tabelaSql, colunas, valores) )
                                .formatArg( cmdInserirTabelaCt.formatArgs(pThis->tabelaCtSql, pThis->tabelaCtSql, id_no.toInt()) );
    consulta.prepare(comando);
    for(auto coluna=0, max=registro.count(); coluna < max; ++coluna) {
      consulta.bindValue(QString(":%1").formatArg(registro.fieldName(coluna)), registro.value(coluna));
    }
    if(!consulta.exec()) {
      spdlog::warn("{}", consulta.executedQuery().toStdString());
      return Erro{Erro::Falhou, "Ocorreu uma falha no comando de inserção de um novo item."};
    }
    
    return Erro{Erro::Sucesso, ""};
  }
  
  TabelaCtSql::Erro TabelaCtSql::removerRegistro(QSqlRecord &registro, QSqlQuery &consulta)
  {
    (void)registro;
    auto indexPK = consulta.driver()->primaryIndex(pThis->tabelaSql);
    const QString cmdRemoverCt = R"(SELECT * FROM %1 WHERE id_no = %2 ORDER BY id_item, nivel)";
    const QString cmdCtDeletados = R"(DELETE FROM %1 ct USING remover r WHERE ct.id_item = r.id_item RETURNING ct.id_item)";
    const QString cmdDeletados = R"(DELETE FROM %1 p USING ct_deletados d WHERE p.id = d.id_item RETURNING *)";
    const QString comando = QString(R"(WITH remover AS ( %1 ), ct_deletados AS ( %2 ), deletados AS ( %3 ) SELECT * FROM deletados;)")
                                .formatArg( cmdRemoverCt.formatArgs(pThis->tabelaCtSql, QString(":id")) )
                                .formatArg( cmdCtDeletados.formatArgs(pThis->tabelaCtSql) )
                                .formatArg( cmdDeletados.formatArgs(pThis->tabelaSql) );
    consulta.prepare(comando);
    consulta.bindValue(QString(":id"), registro.value(indexPK.fieldName(0)));
    if(!consulta.exec()) {
      spdlog::warn("{}", consulta.executedQuery().toStdString());
      return Erro{Erro::Falhou, "Ocorreu uma falha no comando de remoção de um item."};
    }
    
    return Erro{Erro::Sucesso, ""};
  }
  TabelaCtSql::Erro TabelaCtSql::inserirRegistroComIndex(QSqlRecord &registro, QSqlQuery &consulta, const QVariant id_no)
  {
    auto indexPK = consulta.driver()->primaryIndex(pThis->tabelaSql);
    const QString tabelaIndex = "index";
    QString tabelaIndexSql = QString(R"("%1")").formatArg(tabelaIndex);
    if(!pThis->esquema.isEmpty())
      tabelaIndexSql = QString(R"("%1"."%2")").formatArgs(pThis->esquema, tabelaIndex);
    const QString colunaIndex = QString(R"(%1_%2)").formatArgs(indexPK.fieldName(0), pThis->tabela);
    const QString colunaIndexSql = QString(R"("%1")").formatArg(colunaIndex);
    QString colunas;
    QString valores;
    for(int coluna=0, max=registro.count(); coluna < max; ++coluna) {
      if(coluna != 0) {
        colunas.append(", ");
        valores.append(", ");
      }
      if(registro.fieldName(coluna) == indexPK.fieldName(0)) {
        colunas.append( QString(R"("%1")").formatArg(registro.fieldName(coluna)));
        valores.append(QString(R"((SELECT %1 FROM %2 LIMIT 1))").formatArgs(colunaIndexSql, tabelaIndexSql));
      }else {
        colunas.append(QString(R"("%1")").formatArg(registro.fieldName(coluna)));
        valores.append(QString(":%1").formatArg(registro.fieldName(coluna)));
      }
    }
    const QString cmdInserirTabela = R"(INSERT INTO %1 (%2) VALUES (%3) RETURNING *)";
    const QString cmdInserirTabelaCt = R"(INSERT INTO %1 (id_item, id_no, nivel) ( SELECT ii.id, ii.id, 0 FROM item_inserido AS ii UNION ALL SELECT ii.id, lk.id_no, lk.nivel - 1 FROM item_inserido AS ii, %2 AS lk WHERE id_item = %3 ) RETURNING *)";
    const QString comando = QString(R"(WITH item_inserido AS ( %1 ), "registro_atualizado" AS (UPDATE %2 SET %3 = %4 + 1 FROM "item_inserido" RETURNING *), itens_inseridos_ct AS ( %5 ) SELECT * FROM item_inserido;)")
                                .formatArg( cmdInserirTabela.formatArgs(pThis->tabelaSql, colunas, valores) )
                                .formatArg( tabelaIndexSql )
                                .formatArg( colunaIndexSql )
                                .formatArg( QString(R"("item_inserido"."%1")").formatArg(indexPK.fieldName(0)) )
                                .formatArg( cmdInserirTabelaCt.formatArgs(pThis->tabelaCtSql, pThis->tabelaCtSql, id_no.toInt()) );
    consulta.prepare(comando);
    for(auto coluna=0, max=registro.count(); coluna < max; ++coluna) {
      consulta.bindValue(QString(":%1").formatArg(registro.fieldName(coluna)), registro.value(coluna));
    }
    if(!consulta.exec()) {
      spdlog::warn("{}", consulta.executedQuery().toStdString());
      return Erro{Erro::Falhou, "Ocorreu uma falha no comando de inserção de um novo item."};
    }
    return Erro{Erro::Sucesso, ""};
  }
}