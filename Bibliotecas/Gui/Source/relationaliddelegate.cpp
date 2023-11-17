//
// Created by Robson on 04/03/2023.
//
#include <MitoR/Gui/relationaliddelegate.hpp>
#include <QSqlRelationalTableModel>
#include <QSpinBox>
#include <QComboBox>
#include <QHBoxLayout>

namespace MitoR::Gui
{
  RelationalIdDelegate::RelationalIdDelegate(QObject *parent) : QStyledItemDelegate(parent)
  {
  }
  RelationalIdDelegate::~RelationalIdDelegate()
  {
  }
  
  QWidget *RelationalIdDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
  {
    Q_UNUSED(option)
    
    const auto relationalTableModel = qobject_cast<const QSqlRelationalTableModel*>(index.model());
    auto relation = relationalTableModel->relation(index.column());
    if(!relationalTableModel || !relation.isValid())
      goto def;

    {
      // Cria o QSpinBox
      QSpinBox *spinBox = new QSpinBox(parent);

      // Cria o QComboBox
      QComboBox *comboBox = new QComboBox(parent);
      comboBox->setModel(relationalTableModel->relationModel(index.column()));
      comboBox->setModelColumn(relationalTableModel->relationModel(index.column())->fieldIndex(relation.displayColumn()));

      // Cria o widget que será utilizado como editor para a célula
      QWidget *editor = new QWidget(parent);
      QHBoxLayout *layout = new QHBoxLayout;
      layout->addWidget(spinBox);
      layout->addWidget(comboBox);
      layout->setContentsMargins(0, 0, 0, 0);
      editor->setLayout(layout);

      return editor;
    }
    
    // Caso contrário, retorna o editor padrão
    def:
    return QStyledItemDelegate::createEditor(parent, option, index);
  }
  void RelationalIdDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
  {
    Q_UNUSED(editor) Q_UNUSED(index)
  }
  void RelationalIdDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
  {
    Q_UNUSED(editor) Q_UNUSED(model) Q_UNUSED(index)
  }
  void RelationalIdDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
  {
    Q_UNUSED(index)
    
    editor->setGeometry(option.rect);
  }
}