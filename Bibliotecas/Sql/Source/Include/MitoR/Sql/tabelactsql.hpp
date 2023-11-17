//
// Created by Robson on 05/02/2023.
//
#pragma once

#include <MitoR/MitoR.hpp>
#include <QObject>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace MitoR::Sql
{
  class EXP_IMP_DECL TabelaCtSql : QObject
  {
    CS_OBJECT(TabelaCtSql)
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
    
    explicit TabelaCtSql(const QString &nomeTabela, QObject *parent = nullptr);
    ~TabelaCtSql() override;
    
    Erro inserirRegistro(QSqlRecord &registro, QSqlQuery &consulta, const QVariant id_no = QVariant());
    Erro inserirRegistroComIndex(QSqlRecord &registro, QSqlQuery &consulta, const QVariant id_no = QVariant());
    Erro removerRegistro(QSqlRecord &registro, QSqlQuery &consulta);
    
  private:
    struct Impl;
    std::shared_ptr<Impl> pThis;
  };
}