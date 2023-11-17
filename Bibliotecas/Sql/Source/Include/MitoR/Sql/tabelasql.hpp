//
// Created by Robson on 28/01/2023.
//
#pragma once

#include <MitoR/MitoR.hpp>
#include <QObject>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlIndex>
#include <QSqlDatabase>
#include <QSqlError>

namespace MitoR::Sql
{
  /**
   * @class Cria uma classe que gerencia uma tabela armazenada
   * no banco de dados postgreSQL.
   */
  class EXP_IMP_DECL TabelaSql : public QObject
  {
    CS_OBJECT(TabelaSql)
    
  public:

    struct Erro {
      enum {
        Falhou = -1,
        Sucesso = 0
      };
      operator int()
      {
        return erro;
      }
      int erro = Falhou;
      QString msg{};
    };
    explicit TabelaSql(QObject *parent = nullptr);
    TabelaSql(const TabelaSql&) = delete;
    TabelaSql(TabelaSql&&) = delete;
    TabelaSql& operator=(const TabelaSql&) = delete;
    TabelaSql& operator=(const TabelaSql&&) = delete;
    ~TabelaSql() override;

    Erro inserirRegistro(const QString &nomeTabela, QSqlQuery &consulta, QSqlRecord &registro);
    Erro inserirRegistroComIndex(const QString &nomeTabela, QSqlQuery &consulta, QSqlRecord &registro);
    
  public:
  
  private:
    struct Impl;
    std::shared_ptr<Impl> pThis;
  };
}