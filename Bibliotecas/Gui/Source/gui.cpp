//
// Created by Robson on 06/07/2022.
//

#include <mitor/gui/gui.hpp>
#include <QRegularExpression>

namespace MitoR::Gui
{
  
  FormatLineEdit::FormatLineEdit(QLineEdit *lineEdit, const QString &strFmt)
    : m_strFmt(strFmt), m_caracteresExclusao(QString(strFmt).remove(QRegularExpression("[wW0]"))), m_plineEdit(lineEdit)
  {
    // Faz a conexão do objeto lineEdit com este formatador.
    QObject::connect(lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(textChanged(const QString&)));
  }
  
  void FormatLineEdit::textChanged(const QString &text)
  {
    QString str = QString(text).remove(QRegularExpression(QString("[%1]").formatArg(m_caracteresExclusao)));
    const int cursorPos = text.size() - m_plineEdit->cursorPosition();
    int iFmt = m_strFmt.count() - 1;
    int iStr = str.count() - 1;
    while (iStr >= 0 && iFmt >= 0)
    {
      const auto chFmt = m_strFmt[iFmt];
      const auto chStr = str[iStr];
      bool inserido{false};
      if (chFmt == QChar32('0'))
      {
        // é um digito...
        if (!chStr.isDigit())
        {
          str.clear();
          break;
        }
      } else if (chFmt == QChar32('W'))
      {
        // é uma letra maiuscula...
        if (!chStr.isLetter() && !chStr.isUpper())
        {
          str.clear();
          break;
        }
      } else if (chFmt == QChar32('w'))
      {
        // é uma letra maiuscula...
        if (!chStr.isLetter() && !chStr.isLower())
        {
          str.clear();
          break;
        }
      } else
      {
        if (chFmt != chStr)
        {
          str.insert(iStr + 1, chFmt);
          iFmt = m_strFmt.count() - 1;
          iStr = str.count() - 1;
        }
      }
      if (!inserido)
      {
        --iFmt;
        --iStr;
      }
    }
    if (!str.isEmpty())
    {
      m_plineEdit->setText(str);
      m_plineEdit->setCursorPosition(str.size() - cursorPos);
    }
  }
} // MitoR