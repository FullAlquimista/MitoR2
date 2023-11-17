//
// Created by Robson on 30/07/2023.
//
#include <MitoR/AdaptadorJson.hpp>
#include <nlohmann/json.hpp>
#include <QMap>

namespace MitoR
{
  using Json = nlohmann::json;

  struct AdaptadorJson::Impl
  {
    Impl();

    QString identificador;
    Json json;
    static QMap<QString, QSharedPointer<Impl>> globalImpls;
  };
  QMap<QString, QSharedPointer<AdaptadorJson::Impl>> AdaptadorJson::Impl::globalImpls;

  AdaptadorJson::Impl::Impl()
  {
    json = Json::parse(R"({})");
  }

  //
  //
  AdaptadorJson::AdaptadorJson()
  {
    pThis = QSharedPointer<Impl>(new Impl);
  }
  AdaptadorJson::AdaptadorJson(const QString &fromStr) : AdaptadorJson()
  {
    try {
      pThis->json = Json::parse(fromStr.toStdString());
    }catch(std::exception &e) {
    }
  }
  bool AdaptadorJson::inserirDado(const QString &path, const QString &dado)
  {
    const Json::json_pointer ptrPath(path.toStdString());
    pThis->json[ptrPath] = dado.toStdString();
    return true;
  }
  bool AdaptadorJson::inserirDado(const QString &path, const int &dado)
  {
    const Json::json_pointer ptrPath(path.toStdString());
    pThis->json[ptrPath] = dado;
    return true;
  }
  bool AdaptadorJson::inserirDado(const QString &path, const QByteArray &dado)
  {
    const Json::json_pointer ptrPath(path.toStdString());
    std::vector<char> vec(dado.begin(), dado.end());
    pThis->json[ptrPath] = vec;
    return true;
  }
  bool AdaptadorJson::inserirObjetoVazio(const QString &path)
  {
    const Json::json_pointer ptrPath(path.toStdString());
    pThis->json[ptrPath] = Json("{}"_json);
    return true;
  }
  bool AdaptadorJson::obterDado(const QString &path, QString &dado) const
  {
    const Json::json_pointer ptrPath(path.toStdString());
    if(pThis->json.contains(ptrPath)) {
      std::string d = pThis->json[ptrPath].get<std::string>();
      dado = QString::fromStdString(d);
      return true;
    }
    return false;
  }
  bool AdaptadorJson::obterDado(const QString &path, int &dado) const
  {
    const Json::json_pointer ptrPath(path.toStdString());
    if(pThis->json.contains(ptrPath)) {
      dado = pThis->json[ptrPath].get<int>();
      return true;
    }
    return false;
  }
  bool AdaptadorJson::obterDado(const QString &path, QByteArray &dado) const
  {
    const Json::json_pointer ptrPath(path.toStdString());
    if(pThis->json.contains(ptrPath)) {
      std::vector<char> d = pThis->json[ptrPath].get<std::vector<char>>();
      dado = QByteArray(d.data(), d.size());
      return true;
    }
    return false;
  }
  QString AdaptadorJson::dump(int nIndent) const
  {
    return QString::fromUtf8(pThis->json.dump(nIndent).c_str());
  }
}