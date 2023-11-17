//
// Created by Robson on 14/05/2023.
//
#pragma once

#include <MitoR/MitoR.hpp>
#include <QSharedPointer>
#include <QString>

namespace MitoR
{
  /**
 * @brief IServico declara Sessao interface de um serviço que um módulo pode
 * disponibilizar através do plugin.
 */
  class IServico
  {
  public:
    [[nodiscard]] virtual QSharedPointer<QObject> servico(const QString &IDS) = 0;

    [[nodiscard]] virtual bool temServico(const QString &IDS) const = 0;
  };
} // namespace MitoR