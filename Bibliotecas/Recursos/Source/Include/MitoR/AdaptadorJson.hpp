//
// Created by Robson on 30/07/2023.
//
#pragma once

#include <MitoR/MitoR.hpp>
#include <QString>
#include <QSharedPointer>

namespace MitoR
{
  class EXP_IMP_DECL AdaptadorJson
  {
  public:
    AdaptadorJson();
    AdaptadorJson(const QString &fromStr);

    bool inserirDado(const QString &path, const QString &dado);
    bool inserirDado(const QString &path, const int &dado);
    bool inserirDado(const QString &path, const QByteArray &dado);
    bool inserirObjetoVazio(const QString &path);

    bool obterDado(const QString &path, QString &dado) const;
    bool obterDado(const QString &path, int &dado) const;
    bool obterDado(const QString &path, QByteArray &dado) const;

    QString dump(int nIndent = -1) const;

  private:
    struct Impl;
    QSharedPointer<Impl> pThis;
  };
}