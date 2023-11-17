//
// Created by Robson on 15/04/2023.
//
#include <MitoR/LinkedRelation.hpp>
#include <MitoR/Modulo.hpp>
#include <MitoR/IPlugin.hpp>
#include <MitoR/Log.hpp>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QMap>
#include <QPluginLoader>
#include <nlohmann/json.hpp>

namespace MitoR
{
  using Json = nlohmann::json;
  const char *ChaveNomeModulo = "/modulo/nome"; // Uma string que identifica o módulo.
  const char *ChaveIdModulo = "/modulo/id"; // Uma string com um identificador UUID V4 que identifica unicamente o módulo no sistema.
  const char *ChaveCaminhoModulo = "/modulo/caminho"; // Uma string com o caminho relativo da pasta pasta raiz do módulo. Relativo ao caminho absoluto do arquivo descritor.
  const char *ChaveRecursosModulo = "/modulo/recursos"; // Um array de strings com os caminhos relativos e nomes dos arquivos que armazenam recursos.
  const char *ChaveDependenciasModulo = "/modulo/dependencias"; // Um array de strings com os identificadores das dependencias.
  const char *ChaveCaminhoAbsolutoModulo = "/modulo/caminhoAbsoluto"; // Uma string com o caminho absoluto do arquivo descritor. Criado pelo carregador do descritor.

  struct Modulo::Impl
  {
    enum {
      Invalido = 0,
      DependenciasOk = 1,
      Descarregado = 2,
      Carregado = 4,
      Destruido = 8,
      Construido = 16
    };
    Impl();

    QFileInfo arquivoJson;
    QSharedPointer<Json> jModulo;
    QDir dirAbsoluto;
    QMap<QString, QFileInfo> recursos;
    QPluginLoader *dllLoader{nullptr};
    IPlugin *plugin{nullptr};
    QString id;
    QString nome;
    int estado = Invalido;

    using Container = MitoR::LinkedRelation<QSharedPointer<Impl>>;
    static Container modulos;
    static QString idModulo(Container::ConstIterator itModulo)
    {
      return (*itModulo)->id;
    }
    static QStringList listarIdDependencias(Container::ConstIterator itModulo)
    {
      QStringList lista;
      if(itModulo->data()->jModulo->contains(Json::json_pointer(ChaveDependenciasModulo))) {
        std::vector<std::string> vec;
        itModulo->data()->jModulo->operator[](Json::json_pointer(ChaveDependenciasModulo)).get_to(vec);
        for(auto str : vec) lista.push_back(QString::fromStdString(str));
      }
      return lista;
    }
  };
  Modulo::Impl::Container Modulo::Impl::modulos;

  Modulo::Impl::Impl()
  {
    static bool logIniciado = false;
    if(!logIniciado) {
      auto logger = MitoR::Log::criarLogger("MitoR::Modulo");
      spdlog::set_default_logger(logger);
      logIniciado = true;
    }
  }

  Modulo::Modulo(const QFileInfo arquivoModuloJson)
  {
    switch(auto erro = [&]() {
      // Abre o arquivo Json descritor do módulo.
      if(!arquivoModuloJson.exists())
        return Erro{Erro::NaoExiste, QString("O arquivo não existe: '%1'.").formatArg(arquivoModuloJson.fileName())};
      QFile arquivo(arquivoModuloJson.absoluteFilePath());
      if(!arquivo.open(QFile::ReadOnly))
        return Erro{Erro::Falhou, QString("Falha ao abrir o arquivo '%1'.\n%2").formatArg(arquivoModuloJson.fileName()).formatArg(arquivo.errorString())};
      pThis = QSharedPointer<Impl>(new Impl);
      QTextStream txt(&arquivo);
      txt.setCodec("UTF-8");
      try
      {
        pThis->jModulo = QSharedPointer<Json>(new Json(Json::parse(txt.readAll().toStdString())));
      }catch(std::exception &e)
      {
        return Erro{Erro::Falhou, QString("Uma excessão foi lançada: %1").formatArg(QString::fromStdString(e.what()))};
      }
      if(!pThis->jModulo->contains(Json::json_pointer(ChaveIdModulo)))
        return Erro{Erro::Falhou, QString("Falha ao carregar o modulo '%1'. A chave 'id' não existe.").formatArg(arquivoModuloJson.fileName())};
      if(!pThis->jModulo->contains(Json::json_pointer(ChaveCaminhoModulo)))
        return Erro{Erro::Falhou, QString("Falha ao carregar o modulo '%1'. A chave 'caminho' do módulo não existe.").formatArg(arquivoModuloJson.fileName())};
      pThis->id = QString::fromStdString(pThis->jModulo->operator[](Json::json_pointer(ChaveIdModulo)));
      if(pThis->jModulo->contains(Json::json_pointer(ChaveNomeModulo)))
        pThis->nome = QString::fromStdString(pThis->jModulo->operator[](Json::json_pointer(ChaveNomeModulo)));

      // Preenche as informações de diretórios e dos arquivos de recursos.
      QDir dirAbs = arquivoModuloJson.absoluteDir();
      if(pThis->jModulo->contains(Json::json_pointer(ChaveCaminhoModulo))) {
        auto chvDir = pThis->jModulo->operator[](Json::json_pointer(ChaveCaminhoModulo)).get<std::string>();
        auto dir = dirAbs;
        if(dir.cd(QString::fromStdString(chvDir))) {
          dirAbs = QDir(QDir::cleanPath(dir.absolutePath()));
        }
      }
      pThis->jModulo->operator[](Json::json_pointer(ChaveCaminhoAbsolutoModulo)) = dirAbs.absolutePath().toStdString();
      pThis->dirAbsoluto = dirAbs;
      if(pThis->jModulo->contains(Json::json_pointer(ChaveRecursosModulo))) {
        auto &jRecursos = pThis->jModulo->operator[](Json::json_pointer(ChaveRecursosModulo));
        for(auto it=jRecursos.begin(); it != jRecursos.end(); ++it) {
          pThis->recursos[QString::fromStdString(it.key())] = pThis->dirAbsoluto.absoluteFilePath(QString::fromStdString(it.value().get<std::string>()));
        }
      }

      // Inserir este módulo na lista de módulos.
      bool encontrado = false;
      for(auto itModulo = Impl::modulos.begin(); itModulo != Impl::modulos.end(); ++itModulo) {
        if((*itModulo)->id == pThis->id) {
          encontrado = true;
          break;
        }
      }
      if(!encontrado)
        Impl::modulos.insert(pThis);

      for(auto itModulo = Impl::modulos.begin(); itModulo != Impl::modulos.end(); ++itModulo) {
        auto listaIdDep = Impl::listarIdDependencias(itModulo);
        bool depOk = true;
        for(auto id : listaIdDep) {
          auto it = std::find_if(Impl::modulos.begin(), Impl::modulos.end(), [id](auto it) { return id == it->id; });
          if(it != Impl::modulos.end()) {
            Impl::modulos.associate(itModulo, it);
          }else {
            depOk = false;
          }
        }
        if(depOk) itModulo->data()->estado |= Impl::DependenciasOk;
      }

      // Carrega os módulos que estejam com as dependencias OK.
      auto itBeg = Impl::modulos.begin();
      auto itEnd = Impl::modulos.end();
      while(itBeg != itEnd) {
        bool moduloConstruido = false;
        bool construirModulo = true;
        if(((itBeg->data()->estado & Impl::Construido) > 0) || (itBeg->data()->estado == Impl::Invalido) || ((itBeg->data()->estado & Impl::DependenciasOk) == 0)) {
          itBeg++;
          continue;
        }

        auto listaPais = Impl::modulos.list_parents(itBeg);
        for(const auto it : listaPais) {
          if((it->data()->estado & Impl::Construido) == 0) {
            construirModulo = false;
            break;
          }
        }
        if(construirModulo) {
          bool carregar = (itBeg->data()->estado & Impl::Carregado) == 0;
          bool construir = (itBeg->data()->estado & Impl::Construido) == 0;
          for(auto arquivo : itBeg->data()->recursos) {
            if(arquivo.exists() == false) {
              spdlog::error("Falha ao verificar os arquivos dos recursos deste módulo. '{}' não existe.", arquivo.fileName().toStdString());
              carregar = false;
              construir = false;
              itBeg->data()->estado = Impl::Invalido;
            }
          }
          if (itBeg->data()->recursos.contains("plugin") && carregar) {
            itBeg->data()->dllLoader = new QPluginLoader(itBeg->data()->recursos["plugin"].absoluteFilePath());
            auto o = itBeg->data()->dllLoader->instance();
            if (!o) {
              spdlog::error("Falha ao carregar o plugin '{}'. \n{}", itBeg->data()->recursos["plugin"].fileName().toStdString(), itBeg->data()->dllLoader->errorString().toStdString());
              carregar = false;
              construir = false;
              itBeg->data()->estado = Impl::Invalido;
            }else {
              itBeg->data()->plugin = dynamic_cast<IPlugin*>(o);
              if(!itBeg->data()->plugin) {
                spdlog::error("Falha ao obter Sessao interface do plugin '{}'. \n{}", itBeg->data()->recursos["plugin"].fileName().toStdString(), itBeg->data()->dllLoader->errorString().toStdString());
                carregar = false;
                construir = false;
              }
            }
            if(carregar) itBeg->data()->estado |= Impl::Carregado;
          }
          if(carregar && construir) {
            if(itBeg->data()->plugin->construir()) {
              spdlog::info("Módulo: '{}' ({}) construído com sucesso.", itBeg->data()->nome.toStdString(), itBeg->data()->id.toStdString());
              itBeg->data()->estado |= Impl::Construido;
              moduloConstruido = true;
            }else {
              spdlog::error("Falha ao construir o módulo '{}' ({}).", itBeg->data()->nome.toStdString(), itBeg->data()->id.toStdString());
              itBeg->data()->estado = Impl::Invalido;
            }
          }
        }
        if(moduloConstruido)
          itBeg = Impl::modulos.begin();
        else
          itBeg++;
      }

      return Erro{Erro::Sucesso, QString()};
    }())
    {
      case Erro::Sucesso: {
        return;
      }break;
      case Erro::Falhou: {
        if(!erro.msg.isEmpty())
          spdlog::error("{}", erro.msg.toStdString());
        return;
      }break;
    }
  }
  Modulo::Modulo(const QString idModulo)
  {
    auto it = std::find_if(Impl::modulos.begin(), Impl::modulos.end(), [idModulo](auto item) { return item->id == idModulo; });
    if(it != Impl::modulos.end()) {
      pThis = *it;
    }
  }
  void Modulo::descarregarTodosModulos()
  {
    auto itBeg = Impl::modulos.begin();
    auto itEnd = Impl::modulos.end();
    while(itBeg != itEnd)
    {
      bool moduloDescarregado = false;
      bool descarregarModulo = true;
      if((itBeg->data()->estado == Impl::Invalido) || ((itBeg->data()->estado & Impl::Destruido) > 0) || ((itBeg->data()->estado & Impl::Construido) < 1)) {
        ++itBeg;
        continue;
      }

      auto listaFilhos = Impl::modulos.list_children(itBeg);
      for(auto it : listaFilhos) {
        if((it->data()->estado & Impl::Construido) > 0) {
          descarregarModulo = false;
        }
      }
      if(descarregarModulo) {
        if(!itBeg->data()->plugin) {
          spdlog::debug("Plugin não foi construído.");
        }
        else if(itBeg->data()->plugin->destruir()) {
          spdlog::info("Módulo: '{}' ({}) destruído com sucesso.", itBeg->data()->nome.toStdString(), itBeg->data()->id.toStdString());
          itBeg->data()->estado |= Impl::Destruido;
          itBeg->data()->estado &= ~Impl::Construido;
          moduloDescarregado = true;
        }else {
          spdlog::error("Falha ao destruir o módulo '{}' ({}).", itBeg->data()->nome.toStdString(), itBeg->data()->id.toStdString());
        }
      }
      if(moduloDescarregado)
        itBeg = Impl::modulos.begin();
      else
        ++itBeg;
    }
  }

}