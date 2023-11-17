#pragma once

#include "MitoR/MitoR.hpp"
#include <spdlog/spdlog.h>
#include <memory>

namespace MitoR
{
  class EXP_IMP_DECL Log
  {
  public:
    static void inicializar(const std::string nomeArquivo, spdlog::level::level_enum nivelLog);
    static void finalizar();

    static std::shared_ptr<spdlog::logger> criarLogger(const std::string nomeLogger);
    static std::shared_ptr<spdlog::logger> obterLogger(const std::string nomeLogger);
  private:
    struct Impl;
    static std::unique_ptr<Impl> pThis;
  };
}