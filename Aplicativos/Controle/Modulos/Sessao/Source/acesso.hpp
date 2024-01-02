//
// Created by Robson on 30/05/2023.
//
#pragma once

#include "MitoR/MitoR.hpp"
#include <Sessao/IAcesso.hpp>
#include <nlohmann/json.hpp>


namespace Sessao
{
  using Json = nlohmann::json;

  class Acesso : public Sessao::IAcesso
  {
    CS_OBJECT_MULTIPLE(Acesso, Sessao::IAcesso)
  public:

    explicit Acesso(QObject *parent = nullptr);
    ~Acesso() override;

    bool acessarSistema(const QString &usuario, const QString &senha) override;
    QString usuario() const override;
    int64_t oidUsuario() const override;
    int verificarPrevilegio() const override;
    QSqlDatabase conexao(const QString &nomeConexao = QSqlDatabase::defaultConnection) const override;
    bool verificarAcesso(const QString idDispositivo) override;

    void cadastrarDispositivoAcesso(const QString &idDispositivo, const QString &nome, const QString &descricao, bool acessivel) override;
    QString nomeDispositivoAcesso(const QString &idDispositivo, const QString &defaultNotExist) override;
    Json diretivaAtualizada() const;

    QSharedPointer<Json> obterDiretivas() const;

  private:
    QSqlDatabase _conexao;
    int _oid{};
    int _previlegio{Nenhum};
    QSharedPointer<Json> _diretivas;

    CS_SLOT_1(Public, void carregarDiretivas(QSqlDatabase &conexao, const QString &usuario))
    CS_SLOT_2(carregarDiretivas);
  };
}