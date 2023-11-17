//
// Created by Robson on 04/06/2023.
//
#pragma once

#include <MitoR/MitoR.hpp>
#include <QSqlDatabase>
#include <QSqlError>

namespace Sessao
{
  class IAcesso : public QObject
  {
    CS_OBJECT(IAcesso)
  public:
    enum {
      Nenhum = 0,
      Usuario = 1,
      Administrador = 2
    };
    static const std::string iNome;
    static const std::string iDescricao;
    static const std::string iAcesso;

    virtual bool acessarSistema(const QString &usuario, const QString &senha) = 0;
    virtual QString usuario() const = 0;
    virtual int verificarPrevilegio() const = 0;
    virtual QSqlDatabase conexao(const QString &nomeConexao = QSqlDatabase::defaultConnection) const = 0;
    virtual bool verificarAcesso(const QString idDispositivo) = 0;

    virtual void cadastrarDispositivoAcesso(const QString &idDispositivo, const QString &nome, const QString &descricao, bool acessivel = true) = 0;
    virtual QString nomeDispositivoAcesso(const QString &idDispositivo, const QString &defaultNotExist) = 0;

    IAcesso(QObject *parent = nullptr) : QObject(parent) {}
    ~IAcesso() override {}

    CS_SIGNAL_1(Public, void sistemaAcessado(QSqlDatabase &conexao, const QString &usuario))
    CS_SIGNAL_2(sistemaAcessado, conexao, usuario)

  };
}