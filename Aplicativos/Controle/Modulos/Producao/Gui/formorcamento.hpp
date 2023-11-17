//
// Created by Robson on 28/07/2022.
//#
#pragma once

#include <QDialog>
#include <QMainWindow>
#include <QTabWidget>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QDataWidgetMapper>
#include <Sessao/IAcesso.hpp>
#include <Producao/IProducao.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class FormOrcamento; }
QT_END_NAMESPACE

class FormOrcamento : public QDialog {
CS_OBJECT(FormOrcamento)

public:
  enum {
    Limpo = 0, Edicao = 1
  };
  struct Erro : public MitoR::Erro {
    enum {
      Ignorar = MitoR::Erro::Falha - 1
    };
  };
  
  FormOrcamento(QTabWidget *tabWidget, QMainWindow *mainWindow,
                QWidget *parent = nullptr);

  ~FormOrcamento() override;
  
  CS_SLOT_1(Public, void novoOrcamento())
  CS_SLOT_2(novoOrcamento)
  CS_SLOT_1(Public, void pesquisaRapida())
  CS_SLOT_2(pesquisaRapida)
  CS_SLOT_1(Public, void salvarOrcamento())
  CS_SLOT_2(salvarOrcamento)
  CS_SLOT_1(Public, void limparFormulario())
  CS_SLOT_2(limparFormulario)
  CS_SLOT_1(Public, void removerFormulario())
  CS_SLOT_2(removerFormulario)
  CS_SLOT_1(Public, void adicionarAnexo())
  CS_SLOT_2(adicionarAnexo);
  CS_SLOT_1(Public, void baixarAnexo())
  CS_SLOT_2(baixarAnexo)
  CS_SLOT_1(Public, void deletarAnexo())
  CS_SLOT_2(deletarAnexo)
  
  CS_SLOT_1(Public, void adicionarProposta())
  CS_SLOT_2(adicionarProposta)
  CS_SLOT_1(Public, void salvarProposta())
  CS_SLOT_2(salvarProposta)
  CS_SLOT_1(Public, void removerProposta())
  CS_SLOT_2(removerProposta)
  CS_SLOT_1(Public, void adicionarItemProposta())
  CS_SLOT_2(adicionarItemProposta)
  CS_SLOT_1(Public, void removerItemProposta())
  CS_SLOT_2(removerItemProposta)
  
  CS_SLOT_1(Public, void aprovarProposta())
  CS_SLOT_2(aprovarProposta);
  CS_SLOT_1(Public, void cancelarAprovacao())
  CS_SLOT_2(cancelarAprovacao)
  
private:
  QMainWindow *m_janelaPrincipal{nullptr};
  QTabWidget *m_tabWidget{nullptr};
  Ui::FormOrcamento *ui;
  Sessao::IAcesso *m_acesso{nullptr};
  QWidget *m_filtroSelecionado{nullptr};
  int m_estado = Limpo;
  
  struct InfoOrcamento {
    struct InfoCliente {
      QSqlQueryModel *tbl_clientes{nullptr};
      QDataWidgetMapper *map{nullptr};
    } infoCliente;
    struct InfoFabricante {
      QSqlQueryModel *tbl_fabricantes{nullptr};
      QDataWidgetMapper *map{nullptr};
    } infoFabricante;
    struct Anexos {
      QSqlQueryModel *tbl_anexos{nullptr};
    }anexos;
    QString nomeArquivoImagem;
    enum { PNG, JPEG };
    int tipoArquivoImagem;
    QSqlTableModel *tbl_orcamentos{nullptr};
    QDataWidgetMapper *map{nullptr};
  } infoOrcamento;
  
  struct InfoProposta {
    struct TipoProposta {
      QSqlTableModel *tbl_tiposPropostas{nullptr};
    } tipoProposta;
    struct Aprovadas {
      QSqlTableModel *tbl_propostasAprovadas{nullptr};
      QDataWidgetMapper *map{nullptr};
    }aprovadas;
    QSqlTableModel *tbl_propostas{nullptr};
    QDataWidgetMapper *map{nullptr};
    QSqlTableModel *tbl_itens_propostas{nullptr};
  } infoProposta;

private:
  void nomearColunas(QAbstractTableModel *model, QStringList colunas);

protected:
  bool carregarServicos();
  
  bool configurarTabelasMappers();
  
  void conectarAcoesBotoes();
  
  bool validarOrcamento();
  
  void limparOrcamento();
  
  void limparProposta();
  
  bool validarProposta();
  
  bool validarAprovacaoProposta();
  
  bool procurarFabricante(const int idFabricante = -1, const QString &razaoSocial = QString());
  
  bool procurarCliente(const int idCliente = -1, const QString &razaoSocial = QString());
  
  void atualizarListaAnexos(const int idOrcamento);
  
  void atualizarTiposPropostas(const int idTipoProposta);
  
  bool procurarImagemProduto(QPixmap &img, QString &arquivo);

  static QStringList listarCaminhoRecurso(const QString &caminho);

  Erro procurarIdRecurso(const int &idOrcamento, const QString &caminhoRecurso, int &idRecurso);
  Erro salvarImagemOrcamentoNoRecurso(int &idRecurso, const QByteArray &data, const QString &nomeArquivoImagem);
  Erro salvarAnexo(const int &idRecurso, const int &idOrcamento, int &idAnexo);
  Erro salvarDadoBinarioNosRecursos(int &id, const QByteArray &data, const QString &caminhoInfo, const QString &info = QString());
  Erro carregarDadosBinariosRecursos(const int id, QByteArray &outData, const QString &caminhoRecurso, QString &outInfo);
};