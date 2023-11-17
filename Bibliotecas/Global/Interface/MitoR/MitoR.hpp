//
// Created by Robson on 15/04/2023.
//
#pragma once

#include <QObject>
#include <QString>

#ifdef MITOR_BUILD_LIB
# define EXP_IMP_DECL Q_DECL_EXPORT
#else
# define EXP_IMP_DECL Q_DECL_IMPORT
#endif

namespace MitoR
{
  struct Erro {
    enum {
      Falha = -1,
      Sucesso = 0
    };
    operator int()
    {
      return erro;
    }
    int erro = Falha;
    QString msg{};
  };
}