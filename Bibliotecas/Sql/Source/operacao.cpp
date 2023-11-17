
#include <mitor/sql/sqlnucleo.hpp>
#include <mitor/sql/operacao.hpp>
#include <QRegularExpression>
#include <QSqlQuery>
#include <QSqlError>
#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>

namespace MitoR::Sql {
    //
    struct InserirRegistrosComIndex::Impl
    {
        QString nomeEsquema;
        QString nomeTabela;
        QString idTabela;
        QString idIndex;
        const QString nomeTabelaIndex{"index"};
        std::string fmtCmd;
        QSqlDatabase bancoDados;
        QSqlRecord registro;
        QSqlIndex chavePrimaria;
        QSqlRecord ultimoRegistroInserido;
        bool invalido{false};
    };
    
    InserirRegistrosComIndex::InserirRegistrosComIndex(QSqlDatabase &bd, const QString &tabela, const QString &esquema,
                                                       QObject *pai)
        :
        QObject{pai}, impl(std::make_shared<Impl>())
    {
      impl->nomeEsquema = esquema;
      impl->nomeTabela = tabela;
      impl->bancoDados = bd;
      if (impl->nomeEsquema.isEmpty()) {
        impl->idTabela = impl->nomeTabela;
        impl->idIndex = "index";
      } else {
        impl->idTabela = QString(R"("%1"."%2")").formatArg(impl->nomeEsquema).formatArg(impl->nomeTabela);
        impl->idIndex = QString(R"("%1"."index")").formatArg(impl->nomeEsquema);
      }
      impl->fmtCmd = R"(WITH ret AS (INSERT INTO {tabela} ( "{idPrimaryKey}", {colunas} ) VALUES ( (SELECT "{indexPrimaryKey}" FROM {tabelaIndex})+1, {valores} ) RETURNING "{idPrimaryKey}") UPDATE {tabelaIndex} SET "{indexPrimaryKey}"=(ret."{idPrimaryKey}") FROM ret RETURNING "{indexPrimaryKey}";)";
      impl->registro = bd.record(impl->idTabela);
      if (impl->registro.isEmpty()) {
        spdlog::error("Não foi possível obter os nomes das colunas e seus tipos.");
        impl->invalido = true;
        return;
      }
      impl->chavePrimaria = bd.primaryIndex(impl->idTabela);
      if (impl->chavePrimaria.isEmpty()) {
        spdlog::error("É necessário que a tabela tenha pelo menos uma chave primária.");
        impl->invalido = true;
        return;
      }
    }
    
    bool InserirRegistrosComIndex::enviar(const QSqlRecord &r)
    {
      QString colunas;
      QString valores;
      QString ignorar = impl->chavePrimaria.fieldName(0);
      for (int i = 0, primeiro = 0; i < r.count(); ++i) {
        if (ignorar != r.fieldName(i)) {
          if (primeiro++ > 0) {
            colunas += ", ";
            valores += ", ";
          }
          colunas += QString(R"("%1")").formatArg(r.fieldName(i));
          valores += "?";
        }
      }
      std::string cmd = fmt::format(
          impl->fmtCmd,
          fmt::arg("tabela", impl->idTabela.toStdString()),
          fmt::arg("idPrimaryKey", impl->chavePrimaria.fieldName(0).toStdString()),
          fmt::arg("indexPrimaryKey", (QString("%1_%2").formatArg(impl->chavePrimaria.fieldName(0)).formatArg(
              impl->nomeTabela)).toStdString()),
          fmt::arg("tabelaIndex", impl->idIndex.toStdString()),
          fmt::arg("colunas", colunas.toStdString()),
          fmt::arg("valores", valores.toStdString())
      );
      
      QSqlQuery p(impl->bancoDados);
      p.prepare(QString::fromStdString(cmd));
      for (int i = 0, v = 0; i < r.count(); ++i) {
        if (r.fieldName(i) != impl->chavePrimaria.fieldName(0)) {
          p.bindValue(v++, r.value(i));
        }
      }
      if (!p.exec()) {
        spdlog::warn("Falha ao executar o comando. Comando: {}\n{}", cmd, p.lastError().text().toStdString());
        return false;
      } else {
        if (p.next()) {
          impl->ultimoRegistroInserido = p.record();
        }
      }
      return true;
    }
    
    QSqlRecord InserirRegistrosComIndex::registroSemValores() const
    {
      return impl->registro;
    }
    
    bool InserirRegistrosComIndex::valido() const
    {
      return impl->invalido == false;
    }
    
    QSqlRecord InserirRegistrosComIndex::ultimoRegistroInserido() const
    {
      return impl->ultimoRegistroInserido;
    }
    
    
    //
    struct AtualizarRegistros::Impl
    {
        QString nomeEsquema;
        QString nomeTabela;
        QString idTabela;
        QString idIndex;
        const QString nomeTabelaIndex{"index"};
        std::string fmtCmd;
        QSqlDatabase bancoDados;
        QSqlRecord registro;
        QSqlIndex chavePrimaria;
        QSqlRecord ultimoRegistroInserido;
        bool invalido{false};
    };
    
    AtualizarRegistros::AtualizarRegistros(QSqlDatabase &bd, const QString &tabela, const QString &esquema,
                                           QObject *pai)
        :
        QObject{pai}, impl(std::make_shared<Impl>())
    {
      impl->nomeEsquema = esquema;
      impl->nomeTabela = tabela;
      impl->bancoDados = bd;
      if (impl->nomeEsquema.isEmpty()) {
        impl->idTabela = impl->nomeTabela;
        impl->idIndex = "index";
      } else {
        impl->idTabela = QString(R"("%1"."%2")").formatArg(impl->nomeEsquema).formatArg(impl->nomeTabela);
        impl->idIndex = QString(R"("%1"."index")").formatArg(impl->nomeEsquema);
      }
      impl->fmtCmd = R"(UPDATE {tabela} SET {Coluna_Valor} WHERE {idPrimaryKey} = :{idPrimaryKey};)"; // "{indexPrimaryKey}"=(ret."{idPrimaryKey}"       FROM ret RETURNING "{indexPrimaryKey}"
      impl->registro = bd.record(impl->idTabela);
      if (impl->registro.isEmpty()) {
        spdlog::error("Não foi possível obter os nomes das colunas e seus tipos.");
        impl->invalido = true;
        return;
      }
      impl->chavePrimaria = bd.primaryIndex(impl->idTabela);
      if (impl->chavePrimaria.isEmpty()) {
        spdlog::error("É necessário que a tabela tenha pelo menos uma chave primária.");
        impl->invalido = true;
        return;
      }
    }
    
    bool AtualizarRegistros::enviar(const QSqlRecord &r)
    {
      const std::string fmtPdrColunaValor = R"("{coluna}" = :{coluna})";
      std::string listaColunaValor;
      QString ignorar = impl->chavePrimaria.fieldName(0);
      for (int i = 0, primeiro = 0; i < r.count(); ++i) {
        if (ignorar != r.fieldName(i)) {
          if (primeiro++ > 0) {
            listaColunaValor += ", ";
          }
          listaColunaValor += fmt::format(fmtPdrColunaValor, fmt::arg("coluna", r.fieldName(i).toStdString()));
        }
      }
      std::string cmd = fmt::format(
          impl->fmtCmd,
          fmt::arg("tabela", impl->idTabela.toStdString()),
          fmt::arg("Coluna_Valor", listaColunaValor),
          fmt::arg("idPrimaryKey", impl->chavePrimaria.fieldName(0).toStdString())
      );
      
      QSqlQuery p(impl->bancoDados);
      p.prepare(QString::fromStdString(cmd));
      for (int i = 0; i < r.count(); ++i) {
        p.bindValue(QString(":%1").formatArg(r.fieldName(i)), r.value(i));
      }
      if (!p.exec()) {
        spdlog::warn("Falha ao executar o comando. Comando: {}\n{}", cmd, p.lastError().text().toStdString());
        return false;
      } else {
        if (p.next()) {
          impl->ultimoRegistroInserido = p.record();
        }
      }
      return true;
    }
    
    QSqlRecord AtualizarRegistros::registroSemValores() const
    {
      return impl->registro;
    }
    
    bool AtualizarRegistros::valido() const
    {
      return impl->invalido == false;
    }
}
