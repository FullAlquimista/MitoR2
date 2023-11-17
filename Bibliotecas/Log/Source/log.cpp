#include "Include/MitoR/Log.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <iostream>

namespace MitoR
{
  struct Log::Impl
  {
    std::vector<spdlog::sink_ptr> sinks;
    std::shared_ptr<spdlog::logger> logger;
  };
  std::unique_ptr<Log::Impl> Log::pThis;

  void Log::inicializar(const std::string nomeArquivo, spdlog::level::level_enum nivelLog)
  {
    static bool bibliotecaIniciada = false;
    if(!bibliotecaIniciada) {
      try {
        pThis = std::make_unique<Log::Impl>();
        pThis->sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        pThis->sinks.push_back(std::make_shared<spdlog::sinks::daily_file_sink_mt>(nomeArquivo, 23, 59));
        pThis->logger = std::make_shared<spdlog::logger>("MitoR::Log", pThis->sinks.begin(), pThis->sinks.end());
        spdlog::register_logger(pThis->logger);
        spdlog::set_default_logger(pThis->logger);
        spdlog::set_level(nivelLog);
        spdlog::info("Logging iniciado.");
        spdlog::debug("Informações para depuração ativa.");
      }
      catch (std::exception &e) {
        std::cerr << e.what();
      }
    }
  }
  void Log::finalizar()
  {
  }
  std::shared_ptr<spdlog::logger> Log::criarLogger(const std::string nomeLogger)
  {
    try {
      auto logger = std::make_shared<spdlog::logger>(nomeLogger, pThis->sinks.begin(), pThis->sinks.end());
      logger->set_level(spdlog::get_level());
      spdlog::register_logger(logger);
      return logger;
    }
    catch (std::exception &e) {
      spdlog::error("{}", e.what());
    }
    return std::shared_ptr<spdlog::logger>();
  }
  std::shared_ptr<spdlog::logger> Log::obterLogger(const std::string nomeLogger)
  {
    return spdlog::get(nomeLogger);
  }
}