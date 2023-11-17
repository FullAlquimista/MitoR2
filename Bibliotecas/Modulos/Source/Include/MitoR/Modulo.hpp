//
// Created by Robson on 15/04/2023.
//
#pragma once

#include <MitoR/MitoR.hpp>
#include <QString>
#include <QFileInfo>
#include <QSharedPointer>

namespace MitoR
{
  class EXP_IMP_DECL Modulo
  {
  public:
    enum {
      Invalido = -1,
      Aberto,
      Carregado,
      Construido
    };
    struct Erro {
      enum {
        Falhou = -1,
        Sucesso = 0,
        NaoExiste
      };
      operator int() {
        return erro;
      }
      int erro = Sucesso;
      QString msg;
    };

    explicit Modulo(const QFileInfo arquivoModuloJson);
    explicit Modulo(const QString idModulo);
    static void descarregarTodosModulos();

  private:
    struct Impl;
    QSharedPointer<Impl> pThis;
  };
}