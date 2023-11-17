//
// Created by Robson on 06/07/2022.
//
#pragma once
#include <MitoR/MitoR.hpp>
#include <QString>
#include <QLineEdit>

namespace MitoR::Gui
{
  /**
   * @class FormatLineEdit - Está classe utiliza o sinal QLineEdit::textChanged do objeto passado por argumento
   * para formatar a entrada de texto de acordo com a string formatadora.
   */
  class EXP_IMP_DECL FormatLineEdit : public QObject
  {
    CS_OBJECT(FormatLineEdit)
  public:
    FormatLineEdit(QLineEdit *lineEdit, const QString &strFmt);
    
    CS_SLOT_1(Public, void textChanged(const QString& text))
    CS_SLOT_2(textChanged)

  protected:
    const QString m_strFmt;
    const QString m_caracteresExclusao;
    QLineEdit *m_plineEdit{nullptr};
  };
} // MitoR::Gui