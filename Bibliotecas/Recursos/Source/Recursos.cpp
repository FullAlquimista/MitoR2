//
// Created by Robson on 15/04/2023.
//
#include <MitoR/Recursos.hpp>
#include <nlohmann/json.hpp>
#include <QMap>
#include <QString>
#include <QTextStream>
#include <QVector>

namespace MitoR
{
  using Json = nlohmann::json;
  struct Recursos::Impl {
    ~Impl();
    std::shared_ptr<Json> pJson;
    QFile arquivo;

    static void inicializar();
    void destruirRecursos();
    static QMap<QString, std::shared_ptr<Impl>> configuracoes;
  };
  Recursos::Impl::~Impl()
  {
    if(arquivo.isOpen()) {
      arquivo.resize(0);
      arquivo.flush();
      QTextStream txt(&arquivo);
      txt.setCodec("UTF-8");
      txt << QString::fromUtf8(pJson->dump(2).c_str());
      spdlog::debug("Arquivo de configuração '{}', salvo com sucesso.", arquivo.fileName().toStdString());
      arquivo.close();
    }
  }
  void Recursos::Impl::inicializar()
  {
    static bool iniciado = false;
    if (!iniciado) {
      iniciado = true;
      auto logger = MitoR::Log::criarLogger("MitoR::Configuracao");
      spdlog::set_default_logger(logger);
    }
  }
  void Recursos::Impl::destruirRecursos()
  {
    spdlog::info("Destruindo recursos...'{}'", arquivo.fileName().toStdString());
  }
  QMap<QString, std::shared_ptr<Recursos::Impl>> Recursos::Impl::configuracoes;

  Recursos::Recursos(const QString idConfigurador)
  {
    Impl::inicializar();
    if(auto it = pThis->configuracoes.find(idConfigurador); it == pThis->configuracoes.end()) {
      pThis = std::make_shared<Impl>();
      pThis->pJson = std::make_shared<Json>("{}"_json);
      pThis->configuracoes.insert(idConfigurador, pThis);
    }else {
      pThis = *it;
    }
  }
  Recursos::Recursos(const QString idConfigurador, const QFileInfo nomeArquivo) : Recursos(idConfigurador)
  {
    if(pThis->arquivo.fileName() == nomeArquivo.absoluteFilePath())
      return;

    bool primeiraVez = false;
    if(!nomeArquivo.exists()) {
      spdlog::warn("Nome do arquivo de configuração '{}' não existe e poderá ser criado pela primeira vez.", nomeArquivo.fileName().toStdString());
      primeiraVez = true;
    }
    pThis->arquivo.setFileName(nomeArquivo.absoluteFilePath());
    if(!pThis->arquivo.open(QIODevice::OpenModeFlag::ReadWrite)) {
      spdlog::warn("Falha ao abrir o arquivo '{}'. {}.\nOs dados serão perdidos após o termino do aplicativo.", nomeArquivo.fileName().toStdString(), pThis->arquivo.errorString().toStdString());
      return;
    }
    if(primeiraVez)
      return;
    try {
      QTextStream txt(&pThis->arquivo);
      txt.setCodec("UTF-8");
      *pThis->pJson = Json::parse(txt.readAll().toStdString());
    }
    catch(std::exception &e) {
      spdlog::warn("Ocorreu um erro ao interpretar o arquivo '{}'.\n{}.\nOs dados serão perdidos após o termino do aplicativo.", nomeArquivo.fileName().toStdString(), e.what());
      pThis->pJson->clear();
    }
  }
  bool Recursos::array(const QString &strPointerPath, QByteArray *arr) const
  {
    const auto path = Json::json_pointer(strPointerPath.toStdString().c_str());
    if(pThis->pJson->contains(path)) {
      std::vector<char> vec;
      pThis->pJson->operator[](path).get_to(vec);
      arr->append(&vec[0], vec.size());
      return true;
    }
    return false;
  }
  bool Recursos::array(const QString &strPointerPath, const QByteArray &arr)
  {
    const auto path = Json::json_pointer(strPointerPath.toStdString().c_str());
    std::vector<char> vec(arr.begin(), arr.end());
    pThis->pJson->operator[](path) = vec;
    return true;
  }
  bool Recursos::integer(const QString &strPointerPath, int *valor) const
  {
    const auto path = Json::json_pointer(strPointerPath.toStdString().c_str());
    if(pThis->pJson->contains(path)) {
      pThis->pJson->operator[](path).get_to(*valor);
      return true;
    }
    return false;
  }
  bool Recursos::integer(const QString &strPointerPath, const int valor)
  {
    const auto path = Json::json_pointer(strPointerPath.toStdString().c_str());
    pThis->pJson->operator[](path) = valor;
    return true;
  }
  bool Recursos::string(const QString &strPointerPath, QString *string) const
  {
    const auto path = Json::json_pointer(strPointerPath.toStdString().c_str());
    if(pThis->pJson->contains(path)) {
      std::string str;
      pThis->pJson->operator[](path).get_to(str);
      *string = QString::fromStdString(str);
      return true;
    }
    return false;
  }
  bool Recursos::string(const QString &strPointerPath, const QString &str)
  {
    const auto path = Json::json_pointer(strPointerPath.toStdString().c_str());
    pThis->pJson->operator[](path) = str.toStdString();
    return true;
  }

} // namespace MitoR