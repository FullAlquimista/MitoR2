//
// Created by Robson on 30/05/2023.
//

#include "acesso.hpp"
#include "MitoR/Configuracao.hpp"
#include <QMessageBox>
#include <QSqlQuery>
#include <nlohmann/json.hpp>

namespace Sessao
{
  const std::string IAcesso::iNome = "iNome";
  const std::string IAcesso::iDescricao = "iDescricao";
  const std::string IAcesso::iAcesso = "iAcesso";

  const QString ChaveUltimoUsuarioLogado = "/Aplicativos/Controle/Servidor/ultimoUsuario";
  const QString ChaveHostServidor = "/Aplicativos/Controle/Servidor/endereco";
  const QString ChaveNomeBancoDados = "/Aplicativos/Controle/Servidor/bancoDados";
  const QString ChavePortaHost = "/Aplicativos/Controle/Servidor/porta";

  Acesso::Acesso(QObject *parent) : Sessao::IAcesso(parent)
  {
    // Carrega as configurações...
    MitoR::Configuracao cfg("Controle");

    // Informações do servidor.
    _conexao = QSqlDatabase::addDatabase("QPSQL");
    if (!_conexao.isValid()) {
      spdlog::error("Falha ao inicializar o banco de dados.\n\t{}", _conexao.lastError().text().toStdString());
      return;
    }
    QString hostServidor = "localhost";
    if(!cfg.string(ChaveHostServidor, &hostServidor))
      cfg.string(ChaveHostServidor, hostServidor);
    QString nomeBancoDados = "controle";
    if(!cfg.string(ChaveNomeBancoDados, &nomeBancoDados))
      cfg.string(ChaveNomeBancoDados, nomeBancoDados);
    int porta = 5432;
    if(!cfg.integer(ChavePortaHost, &porta))
      cfg.integer(ChavePortaHost, porta);
    _conexao.setHostName(hostServidor.toUtf8());
    _conexao.setDatabaseName(nomeBancoDados.toUtf8());
    _conexao.setPort(porta);

    // Ultimo usuário.
    QString ultimoUsuario;
    if(!cfg.string(ChaveUltimoUsuarioLogado, &ultimoUsuario))
      cfg.string(ChaveUltimoUsuarioLogado, ultimoUsuario);
    _conexao.setUserName(ultimoUsuario);

    _diretivas = QSharedPointer<Json>{new Json("{}"_json)};

    QObject::connect(this, &Acesso::sistemaAcessado, this, &Acesso::carregarDiretivas);
  }
  Acesso::~Acesso()
  {
  }
  bool Acesso::acessarSistema(const QString &usuario, const QString &senha)
  {
    MitoR::Configuracao cfg("Controle");

    if (!usuario.isEmpty()) {
      _conexao.setUserName(usuario);
    }
    _conexao.setPassword(senha);
    if (_conexao.open()) {
      cfg.string(ChaveUltimoUsuarioLogado, usuario);
      QSqlQuery p(_conexao);
      if (!p.exec(QString("select g.groname, u.oid FROM pg_roles u INNER JOIN pg_group g ON u.oid = ANY(g.grolist) WHERE u.rolcanlogin = true AND u.rolname LIKE '%1';").formatArg(usuario))) {
        spdlog::error("Falha ao executar o comando para obter as informações de previlégio do usuário logado.\n{}", p.lastError().text().toStdString());
      }
      if (p.next()) {
        const QString nomeGrupo = p.value(0).toString();
        if (nomeGrupo == "usuarios")
          _previlegio = Usuario;
        else if (nomeGrupo == "administradores")
          _previlegio = Administrador;
        else
          _previlegio = Nenhum;
        _oid = p.value(1).toInt();
      }
      emit sistemaAcessado(_conexao, usuario);
      return true;
    }
    return false;
  }
  QString Acesso::usuario() const
  {
    return _conexao.userName();
  }
  int64_t Acesso::oidUsuario() const {
    return _oid;
  }
  int Acesso::verificarPrevilegio() const
  {
    return _previlegio;
  }
  QSqlDatabase Acesso::conexao(const QString &nomeConexao) const
  {
    if (nomeConexao == QSqlDatabase::defaultConnection)
      return _conexao;

    QSqlDatabase novaConexao = QSqlDatabase::cloneDatabase(_conexao, nomeConexao);
    if (novaConexao.isOpen()) {
      return novaConexao;
    } else {
      if (novaConexao.open()) {
        return novaConexao;
      }
    }
    spdlog::warn("Falha ao criar uma nova conexão '{}' com o sistema.", nomeConexao.toStdString());
    return QSqlDatabase();
  }
  bool Acesso::verificarAcesso(const QString idDispositivo)
  {
    if (_previlegio == Administrador)
      return true;

    auto chave = Json::json_pointer(QString("%1/%2").formatArg(idDispositivo).formatArg(QString::fromStdString(iAcesso)).toStdString());
    if (_diretivas->contains(chave)) {
      int acesso{};
      _diretivas->operator[](chave).get_to(acesso);
      return acesso == 1;
    } else {
      spdlog::debug("O identificador do dispositivo '{}' não existe na diretiva de segurança.", chave.to_string());
    }
    return false;
  }

  void Acesso::carregarDiretivas(QSqlDatabase &conexao, const QString &usuario)
  {
    QSqlQuery p(conexao);
    if (!p.exec(QString("SELECT acesso FROM seguranca.diretivas WHERE nome LIKE '%1'").formatArg(usuario))) {
      spdlog::warn("Falha ao executar o pedido de carregamento das diretivas de segurança do usuário '{}'.\n{}", usuario.toStdString(), p.lastError().text().toStdString());
      return;
    }
    if (p.next()) {
      QString data = p.value(0).toString().toUtf8();
      try {
        *_diretivas = Json::parse(data.toStdString());
        //spdlog::debug("Carregando diretivas: \n{}", _diretivas->flatten().dump(2));
      } catch (std::exception &e) {
        spdlog::warn("Falha ao interpretar a diretiva de segurança do usuário '{}'.\n{}", usuario.toStdString(), e.what());
      }
    }
  }
  void Acesso::cadastrarDispositivoAcesso(const QString &idDispositivo, const QString &nome, const QString &descricao, bool acessivel)
  {
    const auto ChaveNome = Json::json_pointer(QString("%1/%2").formatArg(idDispositivo).formatArg(QString::fromStdString(iNome)).toStdString());
    const auto ChaveDescricao = Json::json_pointer(QString("%1/%2").formatArg(idDispositivo).formatArg(QString::fromStdString(iDescricao)).toStdString());
    const auto ChaveAcesso = Json::json_pointer(QString("%1/%2").formatArg(idDispositivo).formatArg(QString::fromStdString(iAcesso)).toStdString());

    _diretivas->operator[](ChaveNome) = nome.toStdString();
    _diretivas->operator[](ChaveDescricao) = descricao.toStdString();
    if(acessivel) {
      if(!_diretivas->contains(ChaveAcesso))
        _diretivas->operator[](ChaveAcesso) = 0;
    }
  }
  QString Acesso::nomeDispositivoAcesso(const QString &idDispositivo, const QString &defaultNotExist)
  {
    const auto ChaveNome = Json::json_pointer(QString("%1/%2").formatArg(idDispositivo).formatArg(QString::fromStdString(iNome)).toStdString());
    if(_diretivas->contains(ChaveNome))
      return QString::fromUtf8(_diretivas->operator[](ChaveNome).get<std::string>().c_str());
    return defaultNotExist;
  }
  Json Acesso::diretivaAtualizada() const
  {
    return *_diretivas; 
  }
  QSharedPointer<Json> Acesso::obterDiretivas() const
  {
    return QSharedPointer<Json>(new Json(*_diretivas));
  }

} // namespace Sessao