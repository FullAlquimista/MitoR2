//
// Created by Robson on 15/04/2023.
//
#pragma once

#include <MitoR/MitoR.hpp>
#include <MitoR/Log.hpp>
#include <QFileInfo>
#include <memory>

namespace MitoR
{
  class EXP_IMP_DECL Recursos
  {
  public:
    explicit Recursos(const QString idConfigurador);
    Recursos(const QString idConfigurador, const QFileInfo nomeArquivo);

    bool array(const QString &strPointerPath, QByteArray *arr) const;
    bool array(const QString &strPointerPath, const QByteArray &arr);
    bool integer(const QString &strPointerPath, int *valor) const;
    bool integer(const QString &strPointerPath, const int valor);
    bool string(const QString &strPointerPath, QString *string_to_be_modified) const;
    bool string(const QString &strPointerPath, const QString& string_to_be_copied);

  private:
    struct Impl;
    std::shared_ptr<Impl> pThis;
  };
}