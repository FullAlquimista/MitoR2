//
// Created by Robson on 28/07/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_FormOrcamento.h" resolved

#include "formorcamento.hpp"
#include "ui_formorcamento.h"
#include <spdlog/spdlog.h>
#include <MitoR/Sql/operacao.hpp>
#include <MitoR/Gui/eventfiltermudancafocus.hpp>
#include "MitoR/Gui/dialogpesquisar.hpp"
#include <MitoR/AdaptadorJson.hpp>
#include <QtGui>
#include <QtSql>
#include <QLocale>

class CustomDelegate : public QStyledItemDelegate
{
  int coluna = 0;
public:
  CustomDelegate(const int coluna = 0, QObject *parent = nullptr) : QStyledItemDelegate(parent), coluna{coluna} {}
  ~CustomDelegate() override {}

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override
  {
    Q_UNUSED(option)
    if(index.column() == coluna) {
      // Cria o QSpinBox
      QDoubleSpinBox *editor = new QDoubleSpinBox(parent);

      // Cria o widget que será utilizado como editor para a célula
      editor->setMaximum(1999999999);
      editor->setMinimum(0);
      editor->setDecimals(4);

      return editor;
    }

    // Caso contrário, retorna o editor padrão
    return QStyledItemDelegate::createEditor(parent, option, index);
  }

  QString displayText (const QVariant &value, const QLocale &locale) const override
  {
    if(value.type() == QVariant::Int) {
      return locale.toCurrencyString(value.toInt());
    }else if(value.type() == QVariant::Double) {
      return locale.toCurrencyString(value.toDouble());
    }
    return QStyledItemDelegate::displayText(value, locale);
  }
};

FormOrcamento::FormOrcamento(QTabWidget *tabWidget, QMainWindow *mainWindow,
                             QWidget *parent) : QDialog(
    parent), m_janelaPrincipal(mainWindow), m_tabWidget(tabWidget), ui(new Ui::FormOrcamento)
{
  ui->setupUi(this);
  ui->dateEditOrcamento->setDate(QDate::currentDate());
  ui->dateEditDataProposta->setDate(QDate::currentDate());
  ui->dateEditDataAprovacao->setDate(QDate::currentDate());

  carregarServicos();
  if(!configurarTabelasMappers())
    return;
  conectarAcoesBotoes();
}

FormOrcamento::~FormOrcamento()
{
  delete ui;
}

void FormOrcamento::conectarAcoesBotoes()
{
  // Funcionalidade para minimizar um setor do orçamento.
  QObject::connect(ui->pushButtonTituloInformacoesPrincipais, &QPushButton::clicked, this, [this](bool) {
    static bool estaMinimizado = ui->subFrameInformaoesGerais->isHidden();
    static const QString titulo = ui->pushButtonTituloInformacoesPrincipais->text();
    static const QString tituloMinimizado = "+ " + titulo;
    if(estaMinimizado) {
      estaMinimizado = false;
      ui->pushButtonTituloInformacoesPrincipais->setText(titulo);
      ui->subFrameInformaoesGerais->setHidden(estaMinimizado);
    }else {
      estaMinimizado = true;
      ui->pushButtonTituloInformacoesPrincipais->setText(tituloMinimizado);
      ui->subFrameInformaoesGerais->setHidden(estaMinimizado);
    }
  });
  QObject::connect(ui->pushButtonTituloPropostas, &QPushButton::clicked, this, [this](bool) {
    static bool estaMinimizado = ui->subFramePropostas->isHidden();
    static const QString titulo = ui->pushButtonTituloPropostas->text();
    static const QString tituloMinimizado = "+ " + titulo;
    if(estaMinimizado) {
      estaMinimizado = false;
      ui->pushButtonTituloPropostas->setText(titulo);
      ui->subFramePropostas->setHidden(estaMinimizado);
    }else {
      estaMinimizado = true;
      ui->pushButtonTituloPropostas->setText(tituloMinimizado);
      ui->subFramePropostas->setHidden(estaMinimizado);
    }
  });
  
  // Pesquisa de um fabricante.
  // Quando há uma mudança de foco para este widget: ui->lineEditFabricante, marca-o como selecionado para pesquisar.
  MitoR::Gui::EventFilterMudancaFocus *efLineEditFabricante = new MitoR::Gui::EventFilterMudancaFocus([this](QEvent*) {
    m_filtroSelecionado = ui->lineEditFabricante;
    QFont t = ui->labelFabricante->font();
    t.setBold(true);
    ui->labelFabricante->setFont(t);
    t = ui->labelCliente->font();
    t.setBold(false);
    ui->labelCliente->setFont(t);
    t = ui->labelNumeroOrcamento->font();
    t.setBold(false);
    ui->labelNumeroOrcamento->setFont(t);
  }, {}, ui->lineEditNumeroOrcamento);
  ui->lineEditFabricante->installEventFilter(efLineEditFabricante);
  
  // Pesquisa de um cliente.
  // Quando há uma mudança de foco para este widget: ui->lineEditCliente, marca-o como selecionado para pesquisar.
  MitoR::Gui::EventFilterMudancaFocus *efLineEditCliente = new MitoR::Gui::EventFilterMudancaFocus([this](QEvent*) {
    m_filtroSelecionado = ui->lineEditCliente;
    QFont t = ui->labelCliente->font();
    t.setBold(true);
    ui->labelCliente->setFont(t);
    t = ui->labelFabricante->font();
    t.setBold(false);
    ui->labelFabricante->setFont(t);
    t = ui->labelNumeroOrcamento->font();
    t.setBold(false);
    ui->labelNumeroOrcamento->setFont(t);
  }, {}, ui->lineEditCliente);
  ui->lineEditCliente->installEventFilter(efLineEditCliente);
  
  // Pesquisa de uma proposta.
  // Quando há uma mudança de foco para este widget: ui->lineEditNumeroOrcamento, marca-o como selecionado para pesquisar.
  MitoR::Gui::EventFilterMudancaFocus *efLineEditNumeroOrcamento = new MitoR::Gui::EventFilterMudancaFocus([this](QEvent*) {
    m_filtroSelecionado = ui->lineEditNumeroOrcamento;
    QFont t = ui->labelNumeroOrcamento->font();
    t.setBold(true);
    ui->labelNumeroOrcamento->setFont(t);
    t = ui->labelFabricante->font();
    t.setBold(false);
    ui->labelFabricante->setFont(t);
    t = ui->labelCliente->font();
    t.setBold(false);
    ui->labelCliente->setFont(t);
  }, {}, ui->lineEditCliente);
  ui->lineEditNumeroOrcamento->installEventFilter(efLineEditNumeroOrcamento);
  
  QObject::connect(ui->pushButtonPesquisarFabricante, &QPushButton::clicked, this, [this](bool) {
    if(!procurarFabricante(-1, ui->lineEditFabricante->text())) {
    
    }
  });
  
  QObject::connect(ui->pushButtonPesquisarCliente, &QPushButton::clicked, this, [this](bool) {
    if(!procurarCliente(-1, ui->lineEditCliente->text())) {
    
    }
  });
  
  // Botão para carregar imagem do produto.
  QObject::connect(ui->pushButtonCarregarImagemProduto, &QPushButton::clicked, this, [this](bool) {
    QPixmap img;
    if(procurarImagemProduto(img, infoOrcamento.nomeArquivoImagem)) {
      ui->labelImagemProduto->setPixmap(img);
    }
  });
  
  // Combobox Proposta...
  QObject::connect(ui->comboBoxIdentificacaoProposta, cs_mp_cast<int>(&QComboBox::currentIndexChanged), this, [this](int index) {
    if(infoProposta.map && infoProposta.tbl_propostas && index != infoProposta.map->currentIndex()) {
      infoProposta.map->setCurrentIndex(index);
      const int idProposta = infoProposta.tbl_propostas->index(index, 0).data().toInt();
      if(idProposta > 0) {
        infoProposta.aprovadas.tbl_propostasAprovadas->setFilter(QString("id_proposta = %1").formatArg(idProposta));
        infoProposta.aprovadas.tbl_propostasAprovadas->select();
        infoProposta.aprovadas.map->setCurrentIndex(0);
        if(infoProposta.aprovadas.tbl_propostasAprovadas->rowCount() > 0) {
          ui->pushButtonSalvarProposta->setEnabled(false);
          ui->pushButtonAdicionar->setEnabled(false);
          ui->pushButtonAprovarProposta->setEnabled(false);
          bool res{false};
          int id_proposta_aprovada = infoProposta.aprovadas.tbl_propostasAprovadas->index(0, 2).data().toInt(&res);
          if(!res) spdlog::debug("Ao receber sinal de atualização do comboBoxIdentificacaoProposta, falha ao obter o ID da proposta aprovada.");
          if(id_proposta_aprovada == idProposta)
            ui->pushButtonCancelarAprovacao->setEnabled(true);
        }else {
          ui->pushButtonSalvarProposta->setEnabled(true);
          ui->pushButtonAdicionar->setEnabled(true);
          ui->pushButtonAprovarProposta->setEnabled(true);
          ui->pushButtonCancelarAprovacao->setEnabled(false);
          infoProposta.tbl_itens_propostas->setFilter(QString("id_proposta = %1").formatArg(idProposta));
          infoProposta.tbl_itens_propostas->select();
        }
      }else {
        ui->pushButtonSalvarProposta->setEnabled(true);
        ui->pushButtonAdicionar->setEnabled(true);
        ui->pushButtonAprovarProposta->setEnabled(true);
        ui->pushButtonCancelarAprovacao->setEnabled(false);
      }
      atualizarTiposPropostas(infoProposta.tbl_propostas->index(index, 2).data().toInt());
    }
  });
  
  // Botões do formulário...
  QObject::connect(ui->pushButtonNovo, &QPushButton::clicked, this, &FormOrcamento::novoOrcamento);
  QObject::connect(ui->pushButtonPesquisaRapida, &QPushButton::clicked, this, &FormOrcamento::pesquisaRapida);
  QObject::connect(ui->pushButtonSalvar, &QPushButton::clicked, this, &FormOrcamento::salvarOrcamento);
  QObject::connect(ui->pushButtonLimpar, &QPushButton::clicked, this, &FormOrcamento::limparFormulario);
  QObject::connect(ui->pushButtonRemover, &QPushButton::clicked, this, &FormOrcamento::removerFormulario);
  QObject::connect(ui->pushButtonAdicionarAnexo, &QPushButton::clicked, this, &FormOrcamento::adicionarAnexo);
  QObject::connect(ui->pushButtonBaixarAnexo, &QPushButton::clicked, this, &FormOrcamento::baixarAnexo);
  QObject::connect(ui->pushButtonDeletarAnexo, &QPushButton::clicked, this, &FormOrcamento::deletarAnexo);
  
  // Botões da proposta...
  QObject::connect(ui->pushButtonAdicionar, &QPushButton::clicked, this, &FormOrcamento::adicionarProposta);
  QObject::connect(ui->pushButtonSalvarProposta, &QPushButton::clicked, this, &FormOrcamento::salvarProposta);
  QObject::connect(ui->pushButtonRemoverProposta, &QPushButton::clicked, this, &FormOrcamento::removerProposta);
  QObject::connect(ui->pushButtonAdicionarItem, &QPushButton::clicked, this, &FormOrcamento::adicionarItemProposta);
  QObject::connect(ui->pushButtonRemoverItem, &QPushButton::clicked, this, &FormOrcamento::removerItemProposta);
  QObject::connect(ui->pushButtonAprovarProposta, &QPushButton::clicked, this, &FormOrcamento::aprovarProposta);
  QObject::connect(ui->pushButtonCancelarAprovacao, &QPushButton::clicked, this, &FormOrcamento::cancelarAprovacao);
}

bool FormOrcamento::configurarTabelasMappers()
{
  switch(MitoR::Erro e = [this, &e]() -> MitoR::Erro {
    infoOrcamento.tbl_orcamentos = new QSqlTableModel(this, m_acesso->conexao());
    infoOrcamento.tbl_orcamentos->setTable("producao.orcamentos");
    if(infoOrcamento.tbl_orcamentos->lastError().isValid()) {
      return {e.Falha, QString("Tabela '%1': %2.").formatArg(infoOrcamento.tbl_orcamentos->tableName()).formatArg(infoOrcamento.tbl_orcamentos->lastError().text())};
    }
    infoOrcamento.map = new QDataWidgetMapper(this);
    infoOrcamento.map->setModel(infoOrcamento.tbl_orcamentos);
    infoOrcamento.map->addMapping(ui->lineEditTitulo, 3);
    infoOrcamento.map->addMapping(ui->dateEditOrcamento, 4);
    infoOrcamento.map->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    
    infoOrcamento.infoCliente.tbl_clientes = new QSqlQueryModel(this);
    if(infoOrcamento.infoCliente.tbl_clientes->lastError().isValid()) {
      return MitoR::Erro{e.Falha, QString("Tabela 'tbl_clientes': %1.").formatArg(infoOrcamento.infoCliente.tbl_clientes->lastError().text())};
    }
    nomearColunas(infoOrcamento.infoCliente.tbl_clientes, {"ID", "Razão Social", "ID Pessoa Júridica"});
    infoOrcamento.infoCliente.map = new QDataWidgetMapper(this);
    infoOrcamento.infoCliente.map->setModel(infoOrcamento.infoCliente.tbl_clientes);
    infoOrcamento.infoCliente.map->addMapping(ui->spinBoxIDCliente, 2);
    infoOrcamento.infoCliente.map->addMapping(ui->lineEditCliente, 1);
    
    infoOrcamento.infoFabricante.tbl_fabricantes = new QSqlQueryModel(this);
    if(infoOrcamento.infoFabricante.tbl_fabricantes->lastError().isValid()) {
      return MitoR::Erro{e.Falha, QString("Tabela 'tbl_fabricantes': %1.").formatArg(
          infoOrcamento.infoFabricante.tbl_fabricantes->lastError().text())};
    }
    nomearColunas(infoOrcamento.infoFabricante.tbl_fabricantes, {"ID", "Razão Social", "ID Pessoa Júridica"});
    infoOrcamento.infoFabricante.map = new QDataWidgetMapper(this);
    infoOrcamento.infoFabricante.map->setModel(infoOrcamento.infoFabricante.tbl_fabricantes);
    infoOrcamento.infoFabricante.map->addMapping(ui->spinBoxIDFabricante, 2);
    infoOrcamento.infoFabricante.map->addMapping(ui->lineEditFabricante, 1);
    
    infoOrcamento.anexos.tbl_anexos = new QSqlQueryModel(this);
    ui->tableViewAnexos->setModel(infoOrcamento.anexos.tbl_anexos);
    ui->tableViewAnexos->setSelectionMode(QAbstractItemView::SingleSelection);
    
    infoProposta.tipoProposta.tbl_tiposPropostas = new QSqlTableModel(this, m_acesso->conexao());
    infoProposta.tipoProposta.tbl_tiposPropostas->setTable("producao.tipos_propostas");
    if(infoProposta.tipoProposta.tbl_tiposPropostas->lastError().isValid()) {
      return MitoR::Erro{e.Falha, QString("Tabela '%1': %2.").formatArg(
          infoProposta.tipoProposta.tbl_tiposPropostas->tableName()).formatArg(
          infoProposta.tipoProposta.tbl_tiposPropostas->lastError().text())};
    }
    infoProposta.tipoProposta.tbl_tiposPropostas->select();
    
    ui->comboBoxTipoProposta->setModel(infoProposta.tipoProposta.tbl_tiposPropostas);
    ui->comboBoxTipoProposta->setModelColumn(1);
    
    infoProposta.aprovadas.tbl_propostasAprovadas = new QSqlTableModel(this, m_acesso->conexao());
    infoProposta.aprovadas.tbl_propostasAprovadas->setTable("producao.propostas_aprovadas");
    if(infoProposta.aprovadas.tbl_propostasAprovadas->lastError().isValid()) {
      return MitoR::Erro{e.Falha, QString("Tabela '%1': %2.").formatArg(
          infoProposta.aprovadas.tbl_propostasAprovadas->tableName()).formatArg(
          infoProposta.aprovadas.tbl_propostasAprovadas->lastError().text())};
    }
    infoProposta.aprovadas.map = new QDataWidgetMapper(this);
    infoProposta.aprovadas.map->setModel(infoProposta.aprovadas.tbl_propostasAprovadas);
    infoProposta.aprovadas.map->addMapping(ui->lineEditNumeroPedido, 4);
    infoProposta.aprovadas.map->addMapping(ui->dateEditDataAprovacao, 3);
    
    infoProposta.tbl_propostas = new QSqlTableModel(this, m_acesso->conexao());
    infoProposta.tbl_propostas->setTable("producao.propostas");
    if(infoProposta.tbl_propostas->lastError().isValid()) {
      return MitoR::Erro{e.Falha,
                         QString("Tabela '%1': %2.").formatArg(infoProposta.tbl_propostas->tableName()).formatArg(
                             infoProposta.tbl_propostas->lastError().text())};
    }
    infoProposta.map = new QDataWidgetMapper(this);
    infoProposta.map->setModel(infoProposta.tbl_propostas);
    infoProposta.map->addMapping(ui->lineEditNumeroOrcamento, 3);
    infoProposta.map->addMapping(ui->textEditDescricao, 4);
    infoProposta.map->addMapping(ui->dateEditDataProposta, 5);
    infoProposta.map->addMapping(ui->doubleSpinBoxValorTotal, 6);
    infoProposta.map->addMapping(ui->spinBoxPrazoEntrega, 7);
    infoProposta.map->addMapping(ui->spinBoxProducaoHoraria, 8);
    infoProposta.map->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    
    infoProposta.tbl_itens_propostas = new QSqlTableModel(this, m_acesso->conexao());
    infoProposta.tbl_itens_propostas->setTable("producao.itens_propostas");
    if(infoProposta.tbl_itens_propostas->lastError().isValid()) {
      return {e.Falha, QString("Tabela '%1': %2.").formatArg(infoProposta.tbl_itens_propostas->tableName()).formatArg(infoProposta.tbl_itens_propostas->lastError().text())};
    }
    nomearColunas(infoProposta.tbl_itens_propostas, {"ID", "ID da proposta", "Descrição", "Valor"});
    ui->tableViewItens->setModel(infoProposta.tbl_itens_propostas);
    ui->tableViewItens->setColumnHidden(0, true);
    ui->tableViewItens->setColumnHidden(1, true);
    ui->tableViewItens->setItemDelegateForColumn(3, new CustomDelegate(3, ui->tableViewItens));
    infoProposta.tbl_itens_propostas->setEditStrategy(QSqlTableModel::OnManualSubmit);
    
    ui->comboBoxIdentificacaoProposta->setModel(infoProposta.tbl_propostas);
    ui->comboBoxIdentificacaoProposta->setModelColumn(3);
    
    return {e.Sucesso, ""};
  }()) {
    case e.Falha: {
      QMessageBox::warning(this, "Configuração das tabelas...", QString("%1").formatArg(e.msg));
      return false;
    }break;
    case e.Sucesso: {
      return true;
    }break;
    default:
      return false;
  }
}

bool FormOrcamento::carregarServicos()
{
  auto oSrv1 = QApplication::instance()->findChild<Sessao::IAcesso*>();
  if(!oSrv1) {
    spdlog::error("Falha ao carregar o serviço de acesso.");
    return false;
  }
  m_acesso = dynamic_cast<Sessao::IAcesso*>(oSrv1);
  if(!m_acesso)
    return false;

  return true;
}

void FormOrcamento::novoOrcamento()
{
  if(!validarOrcamento()) {
    return;
  }
  auto bd = m_acesso->conexao();
  QSqlQuery p(bd);
  switch(auto e = [this, &bd, &p]() -> MitoR::Erro {
    bd.transaction();
    // Inseri o novo registro.
    MitoR::Sql::InserirRegistrosComIndex inserirOrcamento(bd, "orcamentos", "producao", this);
    auto reg = inserirOrcamento.registroSemValores();
    reg.setValue("id_fabricante", infoOrcamento.infoFabricante.tbl_fabricantes->index(infoOrcamento.infoFabricante.map->currentIndex(), 0).data().toInt());
    reg.setValue("id_cliente", infoOrcamento.infoCliente.tbl_clientes->index(infoOrcamento.infoCliente.map->currentIndex(), 0).data().toInt());
    reg.setValue("titulo", ui->lineEditTitulo->text());
    reg.setValue("data", ui->dateEditOrcamento->date());
    if(!inserirOrcamento.enviar(reg))
      return {Erro::Falha, QString("Falha ao inserir o registro do orçamento.\n%1").formatArg(p.lastError().text())};
    auto idOrcamento = inserirOrcamento.ultimoRegistroInserido().value(0).toInt();
    // Verifica se há uma imagem carregada.
    int idRecurso = 0;
    if(!ui->labelImagemProduto->pixmap()->isNull()) {
      QByteArray arr;
      QBuffer buf(&arr);
      if(ui->labelImagemProduto->pixmap()->save(&buf, infoOrcamento.tipoArquivoImagem == infoOrcamento.PNG ? QString("PNG") : QString("JPEG"))) {
        if(Erro e = salvarImagemOrcamentoNoRecurso(idRecurso, arr, infoOrcamento.nomeArquivoImagem); e != e.Sucesso)
          return e;
      }
    }
    int idAnexo = 0;
    if(idRecurso > 0) {
      if(Erro e = salvarAnexo(idRecurso, idOrcamento, idAnexo); e != Erro::Sucesso)
        return e;
    }
    // Seleciona o orçamento.
    infoOrcamento.tbl_orcamentos->setFilter(QString("id = %1").formatArg(idOrcamento));
    infoOrcamento.tbl_orcamentos->select();
    infoOrcamento.map->setCurrentIndex(0);
    m_estado = Edicao;
    
    return {MitoR::Erro::Sucesso, "Novo registro inserido."};
  }()) {
    case MitoR::Erro::Sucesso: {
      bd.commit();
      spdlog::debug("Novo orçamento inserido. ID = {}", infoOrcamento.tbl_orcamentos->index(0, 0).data().toInt());
    }
      break;
    case MitoR::Erro::Falha: {
      bd.rollback();
      QMessageBox::warning(this, "Novo orçamento...", e.msg);
    }
      break;
  }
}

void FormOrcamento::pesquisaRapida()
{
  auto bd = m_acesso->conexao();
  QSqlQuery p(bd);
  switch(MitoR::Erro e = [&e, this, &p, &bd]() {
    if(m_filtroSelecionado == ui->lineEditFabricante)
    {
      // Fabricante selecionado...
      if(!procurarFabricante(infoOrcamento.infoFabricante.tbl_fabricantes->index(infoOrcamento.infoFabricante.map->currentIndex(), 0).data().toInt(), ui->lineEditFabricante->text())) {
        return MitoR::Erro{0xFF, ""};
      }
      const int idFabricante = infoOrcamento.infoFabricante.tbl_fabricantes->index(infoOrcamento.infoFabricante.map->currentIndex(), 0).data().toInt();
      {
        // Pesquisar orçamentos...
        infoOrcamento.tbl_orcamentos->setFilter(QString("id_fabricante = %1").formatArg(idFabricante));
        infoOrcamento.tbl_orcamentos->select();
        if(infoOrcamento.tbl_orcamentos->rowCount() > 1) {
          auto dialogPesquisa = new DialogPesquisar(infoOrcamento.tbl_orcamentos, this);
          auto res = dialogPesquisa->exec();
          if(res <= 0)
            return MitoR::Erro{MitoR::Erro::Falha, "Nenhum registro selecionado."};
          auto indexSelecionado = dialogPesquisa->linhaSelecionada();
          infoOrcamento.map->setCurrentIndex(indexSelecionado);
          dialogPesquisa->deleteLater();
        }else {
          if(infoOrcamento.tbl_orcamentos->rowCount() < 1)
            return MitoR::Erro{MitoR::Erro::Falha, "Nenhum orçamento foi encontrado para este fabricante!"};
          infoOrcamento.map->setCurrentIndex(0);
        }
      }
      // Recarregando cliente deste orçamento encontrado.
      if(!procurarCliente(infoOrcamento.tbl_orcamentos->index(infoOrcamento.map->currentIndex(), 2).data().toInt())) {
        return MitoR::Erro{MitoR::Erro::Falha, "ID do cliente não encontrado ?!? Formulário estava inválido."};
      }
      // Seleciona a primeira proposta caso exista.
      infoProposta.tbl_propostas->setFilter(QString("id_orcamento = %1").formatArg(
          infoOrcamento.tbl_orcamentos->index(infoOrcamento.map->currentIndex(), 0).data().toInt()));
      infoProposta.tbl_propostas->select();
      ui->comboBoxIdentificacaoProposta->setCurrentIndex(0);
    }else if(m_filtroSelecionado == ui->lineEditCliente)
    {
      // Cliente selecionado...
      if(!procurarCliente(0, ui->lineEditCliente->text())) {
        return MitoR::Erro{0xFF, ""};
      }
      const int idCliente = infoOrcamento.infoCliente.tbl_clientes->index(infoOrcamento.infoCliente.map->currentIndex(),
                                                                          0).data().toInt();
      {
        // Pesquisar orçamentos...
        infoOrcamento.tbl_orcamentos->setFilter(QString("id_cliente = %1").formatArg(idCliente));
        infoOrcamento.tbl_orcamentos->select();
        if(infoOrcamento.tbl_orcamentos->rowCount() > 1) {
          auto dialogPesquisar = new DialogPesquisar(infoOrcamento.tbl_orcamentos, this);
          auto res = dialogPesquisar->exec();
          if(res <= 0)
            return MitoR::Erro{MitoR::Erro::Falha, "Nenhum registro selecionado."};
          auto indexSelecionado = dialogPesquisar->linhaSelecionada();
          infoOrcamento.map->setCurrentIndex(indexSelecionado);
          dialogPesquisar->deleteLater();
        }else {
          if(infoOrcamento.tbl_orcamentos->rowCount() < 1)
            return MitoR::Erro{MitoR::Erro::Falha, "Nenhum orçamento foi encontrado para este cliente!"};
          infoOrcamento.map->setCurrentIndex(0);
        }
      }
      // Recarregando fabricante deste orçamento encontrado.
      if(!procurarFabricante(
          infoOrcamento.tbl_orcamentos->index(infoOrcamento.map->currentIndex(), 1).data().toInt())) {
        return MitoR::Erro{MitoR::Erro::Falha, "ID do fabricante não encontrado ?!? Formulário estava inválido."};
      }
      // Seleciona a primeira proposta caso exista.
      infoProposta.tbl_propostas->setFilter(QString("id_orcamento = %1").formatArg(
          infoOrcamento.tbl_orcamentos->index(infoOrcamento.map->currentIndex(), 0).data().toInt()));
      infoProposta.tbl_propostas->select();
      ui->comboBoxIdentificacaoProposta->setCurrentIndex(0);
    }else if(m_filtroSelecionado == ui->lineEditNumeroOrcamento)
    {
      // Pesquisando por número do orçamento.
      if(ui->lineEditNumeroOrcamento->text().isEmpty())
        return MitoR::Erro{e.Falha, "Preencha o campo 'Número do orçamento' para efetuar esta pesquisa."};
      QSqlQueryModel pTbl;
      pTbl.setQuery(QString("SELECT o.id, o.titulo, tp.descricao, p.numero_orcamento, p.data_proposta, p.valor_total, p.prazo_entrega, p.producao_horaria FROM producao.propostas AS p INNER JOIN producao.tipos_propostas AS tp ON p.id_tipo_proposta = tp.id INNER JOIN producao.orcamentos AS o ON p.id_orcamento = o.id WHERE p.numero_orcamento LIKE '%1%%';").formatArg(ui->lineEditNumeroOrcamento->text()), m_acesso->conexao());
      if(pTbl.lastError().isValid())
        return MitoR::Erro{e.Falha, QString("Falha no comando.\n%1").formatArg(pTbl.lastError().text())};
      nomearColunas(&pTbl, {"ID do orçamento", "Título", "Tipo da proposta", "Número do orçamento", "Data da proposta", "Valor total", "Prazo de entrega", "Produção horária"});
      if(pTbl.rowCount() > 1) {
        // Varios registros encontrados, selecione um...
        auto dialogPesquisar = new DialogPesquisar(&pTbl, this);
        auto res = dialogPesquisar->exec();
        if(res <= 0)
          return MitoR::Erro{MitoR::Erro::Falha, "Nenhum registro selecionado."};
        auto indexSelecionado = dialogPesquisar->linhaSelecionada();
        const int idOrcamento = pTbl.index(indexSelecionado, 0).data().toInt();
        infoProposta.tbl_propostas->setFilter(QString("id_orcamento = %1").formatArg(idOrcamento));
        infoProposta.tbl_propostas->select();
        for(int r=0; r < infoProposta.tbl_propostas->rowCount(); ++r) {
          auto idx = infoProposta.tbl_propostas->index(r, 0);
          if(idx == infoProposta.tbl_propostas->index(indexSelecionado, 0)) {
            ui->comboBoxIdentificacaoProposta->setCurrentIndex(idx.row());
            break;
          }
        }
        dialogPesquisar->deleteLater();
      }else {
        // Um ou nenhum registro encontrado.
        if(pTbl.rowCount() > 0) {
          ui->comboBoxIdentificacaoProposta->setCurrentIndex(0);
        }else {
          return MitoR::Erro{e.Falha, "Nenhum registro encontrado."};
        }
      }
      // Preenche as informações do orçamento.
      int idOrcamento = infoProposta.tbl_propostas->index(infoProposta.map->currentIndex(), 1).data().toInt();
      infoOrcamento.tbl_orcamentos->setFilter(QString("id = %1").formatArg(idOrcamento));
      infoOrcamento.tbl_orcamentos->select();
      infoOrcamento.map->setCurrentIndex(0);
      // Recarregando fabricante deste orçamento encontrado.
      if(!procurarFabricante(
          infoOrcamento.tbl_orcamentos->index(infoOrcamento.map->currentIndex(), 1).data().toInt())) {
        return MitoR::Erro{MitoR::Erro::Falha, "ID do fabricante não encontrado ?!? Formulário estava inválido."};
      }
      // Recarregando cliente deste orçamento encontrado.
      if(!procurarCliente(infoOrcamento.tbl_orcamentos->index(infoOrcamento.map->currentIndex(), 2).data().toInt())) {
        return MitoR::Erro{MitoR::Erro::Falha, "ID do cliente não encontrado ?!? Formulário estava inválido."};
      }
    }else
    {
      return MitoR::Erro{MitoR::Erro::Falha,
                         "Selecione por favor um dos campos abaixo para efetuar uma pesquisa:\nFabricante.\nCliente.\nNúmero do orçamento."};
    }
    // Carregar imagem do orçamento caso tenha.
    int idRecurso = 0;
    if(MitoR::Erro err = procurarIdRecurso(infoOrcamento.tbl_orcamentos->index(infoOrcamento.map->currentIndex(), 0).data().toInt(), Producao::R_ImagenOrcamento_ID, idRecurso); err != Erro::Sucesso)
      return err;

    if(idRecurso > 0) {
      QByteArray arr;
      QBuffer buf(&arr);
      if(MitoR::Erro err = carregarDadosBinariosRecursos(idRecurso, arr, Producao::R_ImagenOrcamento_ID, infoOrcamento.nomeArquivoImagem); err != Erro::Sucesso)
          return err;
      QFileInfo info(infoOrcamento.nomeArquivoImagem);
      auto ext = info.completeSuffix();
      auto tipo = QString();
      for(int i = ext.size() - 1; i > 0; --i)
        if(ext.at(i) == '.') {
          tipo = ext.substr(i + 1);
          break;
        };
      if(tipo.toUpper() == "PNG") infoOrcamento.tipoArquivoImagem = infoOrcamento.PNG;
      else if(tipo.toUpper() == "JPEG" or tipo.toUpper() == "JPG") infoOrcamento.tipoArquivoImagem = infoOrcamento.JPEG;
      QPixmap img;
      if(!img.loadFromData(arr, infoOrcamento.tipoArquivoImagem == infoOrcamento.PNG ? QString("PNG") : QString("JPEG")))
        return MitoR::Erro{MitoR::Erro::Falha, "Falha ao carregar os dados da imagem."};
      ui->labelImagemProduto->setPixmap(img);
    }
    // Carregar lista de arquivos anexados caso tenha.
    atualizarListaAnexos(infoOrcamento.tbl_orcamentos->index(infoOrcamento.map->currentIndex(), 0).data().toInt());
    
    m_estado = Edicao;
    return MitoR::Erro{MitoR::Erro::Sucesso, ""};
  }()) {
    case MitoR::Erro::Sucesso: {
      //bd.commit();
    }
      break;
    case MitoR::Erro::Falha: {
      //bd.rollback();
      QMessageBox::warning(this, "Pesquisa rápida de um orçamento...", e.msg);
    }
      break;
  }
}

void FormOrcamento::salvarOrcamento()
{
  if(Erro e = [this]() -> Erro {
    infoOrcamento.map->submit();
    // Salvando imagem.
    // Verifica se há uma imagem carregada.
    int idRecurso = 0;
    if(Erro err = procurarIdRecurso(infoOrcamento.tbl_orcamentos->index(infoOrcamento.map->currentIndex(), 0).data().toInt(), Producao::R_ImagenOrcamento_ID, idRecurso); err != Erro::Sucesso)
      return err;
    if(!ui->labelImagemProduto->pixmap()->isNull()) {
      QByteArray arr;
      QBuffer buf(&arr);
      if(ui->labelImagemProduto->pixmap()->save(&buf, infoOrcamento.tipoArquivoImagem == infoOrcamento.PNG ? QString("PNG") : QString("JPEG"))) {
        if(Erro e = salvarDadoBinarioNosRecursos(idRecurso, arr, Producao::R_ImagenOrcamento_ID, infoOrcamento.nomeArquivoImagem); e != e.Sucesso)
          return e;
      }
    }
    return {Erro::Sucesso};
  }(); e == e.Sucesso) {
  }else if(e == e.Falha) {
    spdlog::info("{}", e.msg.toStdString());
  }
}

void FormOrcamento::limparFormulario()
{
  limparOrcamento();
  atualizarListaAnexos(0);
  limparProposta();
  
  m_estado = Limpo;
}

void FormOrcamento::removerFormulario()
{
  if(Erro e = [this]() -> Erro {
    // Inicio da função.
    QModelIndex idxAtual = infoOrcamento.tbl_orcamentos->index(infoOrcamento.map->currentIndex(), 0);
    int idOrcamento = 0;
    bool res{false};
    if(idOrcamento = idxAtual.data().toInt(&res); !res)
      return {Erro::Falha, "Não foi possível obter o ID do orçamento. Não é um número ?!?"};
    m_acesso->conexao().transaction();
    QSqlQuery p(m_acesso->conexao());
    QVector<int> idsRecursos;
    if(!p.prepare(QString(R"(WITH removidos AS (DELETE FROM producao.anexos WHERE id_orcamento = ? RETURNING *) DELETE FROM producao.recursos WHERE id IN (SELECT id_recurso FROM removidos);)")))
      return {Erro::Falha, QString("Falha ao preparar o comando para deletar os anexos deste orçamento.\n%1").formatArg(p.lastError().text())};
    p.bindValue(0, idOrcamento);
    if(!p.exec()) {
      return {Erro::Falha, QString("Falha ao executar o comando para deletar os anexos deste orçamento.\n%1").formatArg(p.lastError().text())};
    }
    infoOrcamento.tbl_orcamentos->removeRow(idxAtual.row(), idxAtual.parent());
    if(infoOrcamento.tbl_orcamentos->lastError().isValid()) {
      return {Erro::Falha, QString("Falha a remover o registro do orçamento com o id '%1'.\n%2").formatArg(idOrcamento).formatArg(infoOrcamento.tbl_orcamentos->lastError().text())};
    }
    return {Erro::Sucesso};
  }(); e == e.Sucesso) {
    m_acesso->conexao().commit();
    infoOrcamento.tbl_orcamentos->submitAll();
    limparFormulario();
  }else if(e == e.Falha) {
    QMessageBox::warning(this, "Removendo um orçamento...", e.msg);
    m_acesso->conexao().rollback();
    infoOrcamento.tbl_orcamentos->revertAll();
  }
}

void FormOrcamento::adicionarAnexo()
{
  int idOrcamento = infoOrcamento.tbl_orcamentos->index(infoOrcamento.map->currentIndex(), 0).data().toInt();
  if(idOrcamento < 1) {
    QMessageBox::warning(this, "Adicionando anexos...", "Selecione um orçamento antes de adicionar um anexo.");
    return;
  }
  auto dialogArquivo = new QFileDialog(this, "Selecione um arquivo...", QString(), "*.*");
  dialogArquivo->exec();
  auto listaArquivos = dialogArquivo->selectedFiles();
  dialogArquivo->deleteLater();
  switch(Erro e = [this, idOrcamento, &listaArquivos]() -> Erro {
    spdlog::info("TESTE");
    for(const auto &caminhoArquivo: listaArquivos) {
      QFileInfo info(caminhoArquivo);
      int idRecurso{0};
      QFile arquivo(info.absoluteFilePath());
      if(!arquivo.open(QFile::ReadOnly)) {
        spdlog::warn("Não foi possível abrir o arquivo '{}'", info.fileName().toStdString());
        continue;
      }
      if(Erro e = salvarDadoBinarioNosRecursos(idRecurso, arquivo.readAll(), Producao::R_Anexo_ID, info.absoluteFilePath()); e != Erro::Sucesso) {
        spdlog::warn("Não foi possível carregar no banco de dados o arquivo '{}'. {}", info.fileName().toStdString(), e.msg.toStdString());
        continue;
      }
      spdlog::debug("Arquivo '{}' recurso criado com sucesso.", info.fileName().toStdString());

      QSqlQuery p(m_acesso->conexao());
      if(!p.prepare(QString("INSERT INTO producao.anexos (id_orcamento, id_recurso) VALUES (?, ?);")))
        return {Erro::Falha, QString("Falha ao preparar o comando para inserir o registro do recurso no anexo deste orçamento.\n%1").formatArg(p.lastError().text())};
      p.bindValue(0, idOrcamento);
      p.bindValue(1, idRecurso);
      if(!p.exec()) {
        return {Erro::Falha, QString("Falha no comando de anexação dos arquivos.\n%1").formatArg(p.lastError().text())};
      }
    }
    return {Erro::Sucesso};
  }()) {
    case e.Sucesso: {
      m_acesso->conexao().commit();
      atualizarListaAnexos(idOrcamento);
    }break;
    case e.Ignorar:
    case e.Falha: {
      m_acesso->conexao().rollback();
    }break;
  }
}

void FormOrcamento::baixarAnexo()
{
  auto idxSelecionado = ui->tableViewAnexos->selectionModel()->currentIndex();
  if(idxSelecionado == QModelIndex()) {
    QMessageBox::warning(this, "Baixando um anexo...", "Nenhum anexo foi selecionado.");
    return;
  }
  bool res{false};
  int idAnexo = 0;
  if(idAnexo = infoOrcamento.anexos.tbl_anexos->index(idxSelecionado.row(), 0).data().toInt(&res); !res) {
    QMessageBox::warning(this, "Baixando anexo...", "Falha ao obter o ID do anexo. É um número ?!?");
    return;
  }
  int idRecurso = 0;
  if(idRecurso = infoOrcamento.anexos.tbl_anexos->index(idxSelecionado.row(), 2).data().toInt(&res); !res) {
    QMessageBox::warning(this, "Baixando anexo...", "Falha ao obter o ID do recurso. É um número ?!?");
    return;
  }
  if(idAnexo > 0) {
    // Obtendo o caminho de destino.
    auto dialogArquivo = new QFileDialog(this, "Selecione um diretório de destino...", QString());
    dialogArquivo->setFileMode(QFileDialog::DirectoryOnly);
    dialogArquivo->exec();
    auto lista = dialogArquivo->selectedFiles();
    dialogArquivo->deleteLater();
    QString caminhoDestino;
    for(auto &dir : lista) { caminhoDestino = dir; break; }
    // Obtendo o arquivo do recurso.
    QByteArray arr;
    QString infoRecurso;
    switch(Erro e = carregarDadosBinariosRecursos(idRecurso, arr, Producao::R_Anexo_ID, infoRecurso)) {
      case e.Ignorar:
      case e.Falha: {
        QMessageBox::warning(this, "Baixando um anexo...", QString("Falha ao baixar o recurso.\n%1").formatArg(e.msg));
        return;
      }
      case e.Sucesso: {
        break;
      }
    }
    QFileInfo infoArquivo(infoRecurso);
    auto dir = QDir(caminhoDestino).absoluteFilePath(infoArquivo.fileName());
    QFile arquivo(dir);
    if(!arquivo.open(QFile::WriteOnly)) {
      QMessageBox::warning(this, "Baixando um anexo...", QString("Não foi possível baixar o arquivo '%1'.\n%2").formatArg(dir).formatArg(arquivo.errorString()));
      return;
    }
    arquivo.write(arr);
  }
}

void FormOrcamento::deletarAnexo()
{
  auto idxSelecionado = ui->tableViewAnexos->selectionModel()->currentIndex();
  if(idxSelecionado == QModelIndex()) {
    QMessageBox::warning(this, "Deletando anexo...", "Nenhum anexo foi selecionado.");
    return;
  }
  bool res{false};
  int idAnexo = 0;
  if(idAnexo = infoOrcamento.anexos.tbl_anexos->index(idxSelecionado.row(), 0).data().toInt(&res); !res){
    QMessageBox::warning(this, "Deletando anexo...", "Falha ao obter o ID do anexo. Não é um número ?!?");
    return;
  }
  QSqlQuery p(m_acesso->conexao());
  //const auto cmdDeletarAnexo = ;
  if(!p.prepare(QString("WITH removidos AS (DELETE FROM producao.anexos WHERE id = ? RETURNING *) DELETE FROM producao.recursos WHERE id IN (SELECT id_recurso FROM removidos);"))) {
    QMessageBox::warning(this, "Deletando anexo...", QString("Falha ao preparar o comando para deletar um anexo.\n%1").formatArg(p.lastError().text()));
    return;
  }
  p.bindValue(0, idAnexo);
  if(!p.exec()) {
    QMessageBox::warning(this, "Deletando anexo...", QString("Falha no comando para deletar um anexo.\n%1").formatArg(p.lastError().text()));
    return;
  }
  atualizarListaAnexos(infoOrcamento.tbl_orcamentos->index(infoOrcamento.map->currentIndex(), 0).data().toInt());
}

void FormOrcamento::adicionarProposta()
{
  if(!validarProposta()) {
    return;
  }
  auto bd = m_acesso->conexao();
  QSqlQuery p(bd);
  switch(auto e = [this, &bd, &p]() {
    bd.transaction();
    // Inseri o novo registro.
    MitoR::Sql::InserirRegistrosComIndex inserirProposta(bd, "propostas", "producao", this);
    auto reg = inserirProposta.registroSemValores();
    reg.setValue("id_orcamento",
                 infoOrcamento.tbl_orcamentos->index(infoOrcamento.map->currentIndex(), 0).data().toInt());
    reg.setValue("id_tipo_proposta",
                 infoProposta.tipoProposta.tbl_tiposPropostas->index(ui->comboBoxTipoProposta->currentIndex(),
                                                                     0).data().toInt());
    reg.setValue("numero_orcamento", ui->lineEditNumeroOrcamento->text());
    reg.setValue("descricao", ui->textEditDescricao->toHtml());
    reg.setValue("data_proposta", ui->dateEditDataProposta->date());
    reg.setValue("valor_total", ui->doubleSpinBoxValorTotal->value());
    reg.setValue("prazo_entrega", ui->spinBoxPrazoEntrega->value());
    reg.setValue("producao_horaria", ui->spinBoxProducaoHoraria->value());
    reg.setValue("aprovado", 0);
    if(!inserirProposta.enviar(reg))
      return MitoR::Erro{MitoR::Erro::Falha, QString("Falha ao inserir o registro da proposta.\n{}").formatArg(
                                                         p.lastError().text())};
    auto id = inserirProposta.ultimoRegistroInserido().value(0).toInt();
    // Seleciona o orçamento.
    infoProposta.tbl_propostas->setFilter(QString("id_orcamento = %1").formatArg(
        infoOrcamento.tbl_orcamentos->index(infoOrcamento.map->currentIndex(), 0).data().toInt()));
    infoProposta.tbl_propostas->select();
    int index = 0;
    for(int l = 0; l < infoProposta.tbl_propostas->rowCount(); ++l)
      if(id == infoProposta.tbl_propostas->index(l, 0).data().toInt()) {
        index = l;
        break;
      }
    ui->comboBoxIdentificacaoProposta->setCurrentIndex(index);
    
    return MitoR::Erro{MitoR::Erro::Sucesso, ""};
  }()) {
    case MitoR::Erro::Sucesso: {
      bd.commit();
    }break;
    case MitoR::Erro::Falha: {
      bd.rollback();
      QMessageBox::warning(this, "Adicionar proposta...", e.msg);
    }break;
  }
}

void FormOrcamento::salvarProposta()
{
  infoProposta.tbl_itens_propostas->submitAll();
  if(infoProposta.tbl_itens_propostas->lastError().isValid()) {
    QMessageBox::warning(this, "Salvando a proposta...", QString("Não foi possível salvar os itens.\n%1").formatArg(infoProposta.tbl_itens_propostas->lastError().text()));
  }
  // Lógica para atualizar o total da proposta.
  double res = 0.0;
  for(int l=0; l < infoProposta.tbl_itens_propostas->rowCount(); ++l) {
    auto valor = infoProposta.tbl_itens_propostas->index(l, 3).data().toDouble();
    res += valor;
  }
  ui->doubleSpinBoxValorTotal->setValue(res);
  infoProposta.map->submit();
  infoProposta.tbl_propostas->submitAll();
  if(infoProposta.tbl_propostas->lastError().isValid()) {
    QMessageBox::warning(this, "Salvando a proposta...", QString("Não foi possível salvar os campos.\n%1").formatArg(infoProposta.tbl_propostas->lastError().text()));
  }
}

void FormOrcamento::removerProposta()
{
  QMessageBox pergunta(this);
  pergunta.setIcon(QMessageBox::Question);
  pergunta.setWindowTitle("Remover proposta...");
  pergunta.setText("Deseja realmente remover está proposta ?");
  auto btSim = pergunta.addButton("Sim", QMessageBox::ButtonRole::YesRole);
  pergunta.addButton("Não", QMessageBox::ButtonRole::NoRole);
  pergunta.exec();
  if(btSim != static_cast<QPushButton*>(pergunta.clickedButton()))
    return;
  auto indexProposta = infoProposta.tbl_propostas->index(infoProposta.map->currentIndex(), 0);
  if(indexProposta.isValid()) {
    auto idx = infoProposta.aprovadas.tbl_propostasAprovadas->index(infoProposta.aprovadas.map->currentIndex(), 0);
    if(idx != QModelIndex()) {
      QMessageBox::warning(this, "Removendo a proposta...", QString("Não é possível remover uma proposta aprovada.\nID da aprovação: '%1'.").formatArg(idx.data().toInt()));
      return;
    }
    infoProposta.tbl_propostas->removeRow(indexProposta.row());
    if(infoProposta.tbl_propostas->lastError().isValid()) {
      QMessageBox::warning(this, "Removendo a proposta...",
                           QString("Falha ao remover a proposta.\n%1").formatArg(infoProposta.tbl_propostas->lastError().text()));
      return;
    }
    infoProposta.tbl_propostas->select();
  }
}

void FormOrcamento::adicionarItemProposta()
{
  const int idProposta = infoProposta.tbl_propostas->index(infoProposta.map->currentIndex(), 0).data().toInt();
  if(idProposta < 1 || m_estado == Limpo) {
    QMessageBox::warning(this, "Adicionando um item a proposta...", "Uma proposta deve ser criada ou carregada antes de adicionar um item.");
    return;
  }
  auto novoRegistro = infoProposta.tbl_itens_propostas->record();
  novoRegistro.setValue(1, idProposta);
  novoRegistro.remove(0);
  infoProposta.tbl_itens_propostas->insertRecord(-1, novoRegistro);
}

void FormOrcamento::removerItemProposta()
{
  auto idxSelecionado = ui->tableViewItens->currentIndex();
  if(idxSelecionado == QModelIndex()) {
    QMessageBox::warning(this, "Removendo um item da proposta...", "Nenhum item foi selecionado.");
    return;
  }
  infoProposta.tbl_itens_propostas->removeRow(idxSelecionado.row());
}

void FormOrcamento::aprovarProposta()
{
  if(!validarAprovacaoProposta()) {
    return;
  }
  QMessageBox pergunta(this);
  pergunta.setIcon(QMessageBox::Question);
  pergunta.setWindowTitle("Aprovar proposta...");
  pergunta.setText("Deseja realmente aprovar está proposta ?");
  auto btSim = pergunta.addButton("Sim", QMessageBox::ButtonRole::YesRole);
  pergunta.addButton("Não", QMessageBox::ButtonRole::NoRole);
  pergunta.exec();
  if(btSim != static_cast<QPushButton*>(pergunta.clickedButton()))
    return;
  auto bd = m_acesso->conexao();
  QSqlQuery p(bd);
  switch(auto e = [this, &bd, &p]() {
    bd.transaction();
    // Inseri o novo registro.
    const QString cmd = R"(WITH ret AS (INSERT INTO "producao"."propostas_aprovadas" ( "id_orcamento", "id_proposta", "data_aprovacao", "numero_pedido" ) VALUES ( ?, ?, ?, ? ) RETURNING "id") SELECT * FROM ret;)";
    p.prepare(cmd);
    p.bindValue(0,
                 infoOrcamento.tbl_orcamentos->index(infoOrcamento.map->currentIndex(), 0).data().toInt());
    p.bindValue(1,
                 infoProposta.tbl_propostas->index(infoProposta.map->currentIndex(), 0).data().toInt());
    p.bindValue(2, ui->dateEditDataAprovacao->date());
    p.bindValue(3, ui->lineEditNumeroPedido->text());
    int id = 0;
    if(!p.exec())
      return MitoR::Erro{MitoR::Erro::Falha, QString("Falha ao inserir o registro da aprovação da proposta.\n{}").formatArg(
                                                         p.lastError().databaseText())};
    else {
      if(p.next())
        id = p.value(0).toInt();
    }
    // Seleciona o orçamento.
    infoProposta.aprovadas.tbl_propostasAprovadas->setFilter(QString("id = %1").formatArg(id));
    infoProposta.aprovadas.tbl_propostasAprovadas->select();
    infoProposta.aprovadas.map->setCurrentIndex(0);
    ui->pushButtonSalvarProposta->setEnabled(false);
    
    return MitoR::Erro{MitoR::Erro::Sucesso, ""};
  }()) {
    case MitoR::Erro::Sucesso: {
      bd.commit();
    }
      break;
    case MitoR::Erro::Falha: {
      bd.rollback();
      QMessageBox::warning(this, "Adicionar proposta...", e.msg);
    }
      break;
  }
}

void FormOrcamento::cancelarAprovacao()
{
  QMessageBox pergunta(this);
  pergunta.setIcon(QMessageBox::Question);
  pergunta.setWindowTitle("Cancelando aprovação...");
  pergunta.setText("Deseja realmente cancelar a aprovação desta proposta ?");
  auto btSim = pergunta.addButton("Sim", QMessageBox::ButtonRole::YesRole);
  pergunta.addButton("Não", QMessageBox::ButtonRole::NoRole);
  pergunta.exec();
  if(btSim != static_cast<QPushButton*>(pergunta.clickedButton()))
    return;
  auto indexAprovacao = infoProposta.aprovadas.tbl_propostasAprovadas->index(infoProposta.aprovadas.map->currentIndex(), 0);
  if(indexAprovacao.isValid()) {
    infoProposta.aprovadas.tbl_propostasAprovadas->removeRow(indexAprovacao.row());
    if(infoProposta.aprovadas.tbl_propostasAprovadas->lastError().isValid()) {
      QMessageBox::warning(this, "Removendo a proposta...",
                           QString("Falha ao remover a proposta.\n%1").formatArg(infoProposta.aprovadas.tbl_propostasAprovadas->lastError().text()));
      return;
    }
    infoProposta.aprovadas.tbl_propostasAprovadas->select();
    ui->pushButtonSalvarProposta->setEnabled(true);
  }
}

bool FormOrcamento::procurarFabricante(const int idFabricante, const QString &razaoSocial)
{
  switch(MitoR::Erro e = [this, &e, &razaoSocial, &idFabricante]() {
    QString cmd = QString(
        "SELECT f.id, p.razao_social, p.id_pessoa FROM cadastro.fabricantes AS f INNER JOIN cadastro.pessoas_juridicas AS p ON f.id_pessoa = p.id_pessoa");
    if(idFabricante > 0) {
      cmd.append(QString(" WHERE f.id = %1").formatArg(idFabricante));
    }else if(!razaoSocial.isEmpty()) {
      cmd.append(QString(" WHERE p.razao_social LIKE '%%1%'").formatArg(razaoSocial.toUpper()));
    }
    infoOrcamento.infoFabricante.tbl_fabricantes->setQuery(cmd, m_acesso->conexao());
    if(infoOrcamento.infoFabricante.tbl_fabricantes->lastError().isValid()) {
      return MitoR::Erro{e.Falha, QString("%1").formatArg(
          infoOrcamento.infoFabricante.tbl_fabricantes->lastError().text())};
    }
    if(infoOrcamento.infoFabricante.tbl_fabricantes->rowCount() > 1) {
      // Multiplos clientes para escolher.
      auto dialogPesquisar = new DialogPesquisar(infoOrcamento.infoFabricante.tbl_fabricantes, this);
      const auto res = dialogPesquisar->exec();
      if(res == dialogPesquisar->Accepted) {
        const auto idx = dialogPesquisar->linhaSelecionada();
        infoOrcamento.infoFabricante.map->setCurrentIndex(idx);
      }else
        return MitoR::Erro{0xFF, ""};
    }else {
      // Um ou cliente não encontrado.
      if(infoOrcamento.infoFabricante.tbl_fabricantes->rowCount() == 1) {
        infoOrcamento.infoFabricante.map->setCurrentIndex(0);
      }else {
        return MitoR::Erro{e.Sucesso, "Cliente não encontrado."};
      }
    }
    
    return MitoR::Erro{e.Sucesso, ""};
  }()) {
    case e.Falha: {
      QMessageBox::warning(this, "Procurar fabricante...", QString("%1").formatArg(e.msg));
      return false;
    }
      break;
    case e.Sucesso: {
      return true;
    }
      break;
    default:
      return false;
  }
}
bool FormOrcamento::procurarCliente(const int idCliente, const QString &razaoSocial)
{
  switch(MitoR::Erro e = [this, &e, &razaoSocial, &idCliente]() {
    QString cmd = QString(
        "SELECT c.id, p.razao_social, p.id_pessoa FROM cadastro.clientes AS c INNER JOIN cadastro.pessoas_juridicas AS p ON c.id_pessoa = p.id_pessoa");
    if(idCliente > 0) {
      cmd.append(QString(" WHERE c.id = %1").formatArg(idCliente));
    }else if(!razaoSocial.isEmpty()) {
      cmd.append(QString(" WHERE p.razao_social LIKE '%%1%'").formatArg(razaoSocial.toUpper()));
    }
    infoOrcamento.infoCliente.tbl_clientes->setQuery(cmd, m_acesso->conexao());
    if(infoOrcamento.infoCliente.tbl_clientes->lastError().isValid()) {
      return MitoR::Erro{e.Falha, QString("%1").formatArg(
          infoOrcamento.infoCliente.tbl_clientes->lastError().text())};
    }
    if(infoOrcamento.infoCliente.tbl_clientes->rowCount() > 1) {
      // Multiplos clientes para escolher.
      auto dialogPesquisar = new DialogPesquisar(infoOrcamento.infoCliente.tbl_clientes, this);
      const auto res = dialogPesquisar->exec();
      if(res == dialogPesquisar->Accepted) {
        const auto idx = dialogPesquisar->linhaSelecionada();
        infoOrcamento.infoCliente.map->setCurrentIndex(idx);
      }else
        return MitoR::Erro{0xFF, ""};
    }else {
      // Um ou cliente não encontrado.
      if(infoOrcamento.infoCliente.tbl_clientes->rowCount() == 1) {
        infoOrcamento.infoCliente.map->setCurrentIndex(0);
      }else {
        return MitoR::Erro{e.Sucesso, "Cliente não encontrado."};
      }
    }
    
    return MitoR::Erro{e.Sucesso, ""};
  }()) {
    case e.Falha: {
      QMessageBox::warning(this, "Procurar cliente...", QString("%1").formatArg(e.msg));
      return false;
    }
      break;
    case e.Sucesso: {
      return true;
    }
      break;
    default:
      return false;
  }
}

bool FormOrcamento::procurarImagemProduto(QPixmap &img, QString &arquivo)
{
  auto dialogArquivo = new QFileDialog(this, "Selecione uma imagem...", QString(), "*.jpeg;*.jpg;*.png");
  dialogArquivo->exec();
  auto listaArquivos = dialogArquivo->selectedFiles();
  dialogArquivo->deleteLater();
  for(const auto &arq: listaArquivos) {
    QFileInfo info(arq);
    auto ext = info.completeSuffix();
    auto tipo = QString();
    for(int i = ext.size() - 1; i > 0; --i)
      if(ext.at(i) == '.') {
        tipo = ext.substr(i + 1);
        break;
      };
    if(tipo.toUpper() == "PNG") infoOrcamento.tipoArquivoImagem = infoOrcamento.PNG;
    else if(tipo.toUpper() == "JPEG" or tipo.toUpper() == "JPG") infoOrcamento.tipoArquivoImagem = infoOrcamento.JPEG;
    if(!img.load(arq)) {
      QMessageBox::warning(this, "Seleção de imagem...",
                           QString("Falha ao carregar o arquivo da imagem.\n%1").formatArg(arq));
      return false;
    }
    QTransform escala;
    auto sl = ui->labelImagemProduto->size().width() / (double) img.size().width();
    auto sa = ui->labelImagemProduto->size().height() / (double) img.size().height();
    if(sl < sa) escala.scale(sl, sl);
    else escala.scale(sa, sa);
    img = img.transformed(escala);
    arquivo = arq;
    return true;
  }
  return false;
}

FormOrcamento::Erro FormOrcamento::procurarIdRecurso(const int &idOrcamento, const QString &caminhoRecurso, int &idRecurso)
{
  (void)idRecurso;
  if(idOrcamento <= 0)
    return {Erro::Falha, "ID do orçamento para procurar um recurso inválido."};
  if(caminhoRecurso.size() <= 1)
    return {Erro::Falha, "O caminho do recurso está vazio."};
  const int iPosRecurso = caminhoRecurso.rfind('/');
  const QString nomeRecurso = QString(caminhoRecurso.substr(iPosRecurso + 1));
  const QString caminho = caminhoRecurso.substr(0, iPosRecurso);
  QStringList listaCaminhos = listarCaminhoRecurso(caminho);
  QString strExtrairObjeto;
  for(const auto&str : listaCaminhos)
    strExtrairObjeto.append(QString("->'%1'").formatArg(str));
  MitoR::AdaptadorJson jParaProcurar;
  jParaProcurar.inserirObjetoVazio(caminho);

  QSqlQuery p(m_acesso->conexao());
  if(!p.prepare(QString("WITH recursos AS (SELECT id, detalhe FROM producao.recursos WHERE id IN (SELECT id_recurso FROM producao.anexos WHERE id_orcamento = ?)) SELECT r.id, r.detalhe %1 FROM recursos AS r WHERE r.detalhe @> ?::jsonb;").formatArg(strExtrairObjeto)))
    return {Erro::Falha, QString("A preparação do comando falhou.\n%1").formatArg(p.lastError().text())};
  p.bindValue(0, idOrcamento);
  p.bindValue(1, jParaProcurar.dump());
  if(!p.exec())
    return {Erro::Falha, QString("Erro ao executar o comando para pesquisar o recurso.\n%1").formatArg(p.lastError().text())};
  if(p.next()) {
    bool res = false;
    if(idRecurso = p.value(0).toInt(&res); !res)
      return {Erro::Falha, QString("Falha ao obter o ID do recurso. Não é um número inteiro ?!?.")};
  }else {
    idRecurso = 0;
  }

  return {Erro::Sucesso};
}

FormOrcamento::Erro FormOrcamento::salvarImagemOrcamentoNoRecurso(int &idRecurso, const QByteArray &data, const QString &nomeArquivoImagem)
{
  if(data.isEmpty()) {
    return {MitoR::Erro::Falha, "Não há dados de uma imagem a ser armazenada!"};
  }
  QSqlQuery p(m_acesso->conexao());
  MitoR::AdaptadorJson j;
  if(!j.inserirDado(Producao::R_ImagenOrcamento_ID, QFileInfo(nomeArquivoImagem).fileName()))
    return {MitoR::Erro::Falha, "Falha ao inserir as informações do nome do arquivo da imagem no registro 'JSON'."};
  if(!p.prepare(QString("WITH inserido AS (INSERT INTO producao.recursos (detalhe, recurso) VALUES (?, ?) RETURNING *) SELECT id FROM inserido;")))
    return {Erro::Ignorar, QString("Falha ao preparar a declaração SQL para inserir o recurso.\n%1").formatArg(p.lastError().text())};
  p.bindValue(0, j.dump());
  p.bindValue(1, data);
  if(!p.exec()) {
    return {MitoR::Erro::Falha, QString("Houve um erro ao inserir o registro na tabela de recursos.\n%1").formatArg(p.lastError().text())};
  }
  if(!p.next())
    return {MitoR::Erro::Falha, QString("Houve uma falha ao obter o id do recurso recém adicionado.\n")};
  bool res{false};
  if(idRecurso = p.value(0).toInt(&res); !res) {
    return {MitoR::Erro::Falha, QString("Houve uma falha ao obter o id como um inteiro do recurso recém adicionado.\n")};
  }

  return {MitoR::Erro::Sucesso, ""};
}

FormOrcamento::Erro FormOrcamento::salvarAnexo(const int &idRecurso, const int &idOrcamento, int &idAnexo)
{
  if(idRecurso <= 0)
    return {Erro::Falha, "O id do recurso não é válido."};
  if(idOrcamento <= 0)
    return {Erro::Falha, "O id do orçamento não é válido."};
  QSqlQuery p(m_acesso->conexao());
//    if(!p.exec(QString("SELECT id_recurso FROM producao.anexos WHERE id_orcamento = %1").formatArg(idOrcamento)))
//      return {Erro::Ignorar, ""};
  if(!p.prepare("WITH inserido AS (INSERT INTO producao.anexos (id_orcamento, id_recurso) VALUES (?, ?) RETURNING *) SELECT id FROM inserido;"))
    return {Erro::Ignorar, QString("Falha ao preparar a declaração SQL para inserir o anexo.\n%1").formatArg(p.lastError().text())};
  p.bindValue(0, idOrcamento);
  p.bindValue(1, idRecurso);
  if(!p.exec())
    return {Erro::Ignorar, QString("Falha ao executar o comando para inserir o registro de um anexo.\n%1").formatArg(p.lastError().text())};
  if(!p.next())
    return {Erro::Falha, QString("Ocorreu um erro ao obter o ID do registro do anexo inserido.\b%1").formatArg(p.lastError().text())};
  bool res{false};
  if(idAnexo = p.value(0).toInt(&res); !res) {
    return {MitoR::Erro::Falha, QString("Houve uma falha ao obter o id como um inteiro do recurso recém adicionado.\n")};
  }

  return {Erro::Sucesso};
}

FormOrcamento::Erro FormOrcamento::salvarDadoBinarioNosRecursos(int &id, const QByteArray &data, const QString &caminhoInfo, const QString &info)
{
  QSqlQuery p(m_acesso->conexao());
  if(!p.prepare(QString("SELECT id, detalhe FROM producao.recursos WHERE id = ?")))
    return {Erro::Falha, QString("Falha ao preparar o comando para salvar um dado binário.\n%1").formatArg(p.lastError().text())};
  p.bindValue(0, id);
  if(!p.exec())
    return {Erro::Falha, QString("Falha no comando.\n%1").formatArg(p.lastError().text())};

  if(p.next()) {
    // Atualizar o registro no banco de dados.
    MitoR::AdaptadorJson j(p.value(1).toString());
    if(!caminhoInfo.empty()) {
      if(!j.inserirDado(caminhoInfo, info)) {
        spdlog::error("Ao salvar os dados binários deste orçamento, um erro foi encontrado na inserção dos dados JSON.!");
      }
    }else {
      j.inserirDado("/NomeArquivo", info);
    }
    if(!p.prepare(QString("UPDATE producao.recursos SET detalhe = ?, recurso = ? WHERE id = ?")))
      return {Erro::Falha, QString("Falha ao preparar o comando para atualizar o registro do recurso.\n%1").formatArg(p.lastError().text())};
    p.bindValue(0, j.dump());
    p.bindValue(1, data);
    p.bindValue(2, id);
    if(!p.exec())
      return {Erro::Falha, QString("Não foi possível atualizar o registro.\n%1").formatArg(p.lastError().text())};
  }else {
    // Salvando no banco de dados.
    MitoR::AdaptadorJson j;
    if(!caminhoInfo.empty()) {
      if(!j.inserirDado(caminhoInfo, info)) {
        spdlog::error("Ao salvar os dados binários deste orçamento, um erro foi encontrado na inserção dos dados JSON.!");
      }
    }else {
      j.inserirDado("/NomeArquivo", info);
    }
    if(!p.prepare("WITH tbl AS (INSERT INTO producao.recursos AS r (detalhe, recurso) VALUES (?, ?) RETURNING *) SELECT * FROM tbl;"))
      return {Erro::Falha, QString{"Não foi possível preparar o comando para inserir um novo recurso."}.formatArg(p.lastError().text())};
    p.bindValue(0, j.dump());
    p.bindValue(1, data);
    if(!p.exec()) {
      return {Erro::Falha, QString("Não foi possível arquivar no banco de dados os dados binários.\n%1").formatArg(p.lastError().text())};
    }
    if(!p.next())
      return {Erro::Falha, QString("Não foi possível obter o ID no banco de dados dos dados binários.")};
    bool res{false};
    if(res = p.value(0).toInt(&res); !res)
      return {Erro::Falha, "Não foi possível obter o valor do identificador. Não é um número !?!"};
    id = p.value(0).toInt();
  }

  return {Erro::Sucesso, ""};
}

FormOrcamento::Erro FormOrcamento::carregarDadosBinariosRecursos(const int id, QByteArray &outData, const QString &caminhoRecurso, QString &outInfo)
{
  if(id <= 0) {
    return {Erro::Falha, "É necessário indicar o ID do recurso."};
  }
  const int iPosRecurso = caminhoRecurso.rfind('/');
  const QString nomeRecurso = QString(caminhoRecurso.substr(iPosRecurso + 1));
  const QString caminho = caminhoRecurso.substr(0, iPosRecurso);

  QStringList listaCaminhos = listarCaminhoRecurso(caminhoRecurso);
  QString strExtrairObjeto;
  for(int i=0; i < listaCaminhos.size(); ++i) {
    const QString &str = listaCaminhos[i];
    if(i < listaCaminhos.size() - 1)
      strExtrairObjeto.append(QString("->'%1'").formatArg(str));
    else
      strExtrairObjeto.append(QString("->>'%1'").formatArg(str));
  }

  QSqlQuery p(m_acesso->conexao());
  if(!p.prepare(QString("SELECT id, detalhe%1, recurso FROM producao.recursos WHERE id = ?").formatArg(strExtrairObjeto)))
    return {Erro::Falha, QString("Falha ao preparar o comando para pesquisar um recurso.\n%1").formatArg(p.lastError().text())};
  p.bindValue(0, id);
  if(!p.exec())
    return {Erro::Falha, QString("Falha no comando.\n%1").formatArg(p.lastError().text())};
  if(p.next()) {
    // Obter um recurso.
    outData = p.value(2).toByteArray();
    outInfo = QFileInfo(p.value(1).toString()).fileName();
  }else {
    return {Erro::Falha, "Nenhum recurso encontrado!"};
  }
  return {MitoR::Erro::Sucesso, ""};
}

void FormOrcamento::nomearColunas(QAbstractTableModel *model, QStringList colunas)
{
  auto it = colunas.begin();
  for(int i = 0; i < model->columnCount() && it != colunas.end(); ++i) {
    model->setHeaderData(i, Qt::Horizontal, *it++);
  }
}

bool FormOrcamento::validarOrcamento()
{
  if(ui->spinBoxIDFabricante->value() <= 0) {
    QMessageBox::warning(this, "Validação do orçamento...",
                         "Por favor antes desta operação, preencha o campo fabricante.");
    return false;
  }
  if(ui->spinBoxIDCliente->value() <= 0) {
    QMessageBox::warning(this, "Validação do orçamento...",
                         "Por favor antes desta operação, preencha o campo cliente.");
    return false;
  }
  if(ui->lineEditTitulo->text().isEmpty()) {
    QMessageBox::warning(this, "Validação do orçamento...", "Por favor antes desta operação, preencha o campo título.");
    return false;
  }
  return true;
}

void FormOrcamento::limparOrcamento()
{
  infoOrcamento.tbl_orcamentos->setFilter("id = 0");
  infoOrcamento.tbl_orcamentos->select();
  ui->lineEditFabricante->clear();
  ui->spinBoxIDFabricante->clear();
  infoOrcamento.infoFabricante.tbl_fabricantes->clear();
  ui->lineEditCliente->clear();
  ui->spinBoxIDCliente->clear();
  infoOrcamento.infoCliente.tbl_clientes->clear();
  ui->lineEditTitulo->clear();
  ui->labelImagemProduto->clear();
}

void FormOrcamento::limparProposta()
{
  infoProposta.tbl_propostas->setFilter("id_orcamento = 0");
  infoProposta.tbl_propostas->select();
  infoProposta.aprovadas.tbl_propostasAprovadas->setFilter("id_proposta = 0");
  infoProposta.aprovadas.tbl_propostasAprovadas->select();
  infoProposta.tbl_itens_propostas->revertAll();
  infoProposta.tbl_itens_propostas->setFilter("id_proposta = 0");
  infoProposta.tbl_itens_propostas->select();
  ui->pushButtonSalvarProposta->setEnabled(true);
  ui->lineEditNumeroOrcamento->clear();
  ui->textEditDescricao->clear();
  ui->spinBoxProducaoHoraria->clear();
  ui->spinBoxPrazoEntrega->clear();
  ui->doubleSpinBoxValorTotal->clear();
  ui->lineEditNumeroPedido->clear();
}

bool FormOrcamento::validarProposta()
{
  if(m_estado != Edicao) {
    QMessageBox::warning(this, "Validação da proposta...", "É necessário que um orçamento esteja carregado.");
    return false;
  }
  if(ui->comboBoxTipoProposta->currentIndex() < 0) {
    QMessageBox::warning(this, "Validação da proposta...", "Por favor escolha um tipo de proposta.");
    return false;
  }
  if(ui->lineEditNumeroOrcamento->text().isEmpty()) {
    QMessageBox::warning(this, "Validação da proposta...", "Preencha o campo 'Número do orçamento'.");
    return false;
  }
  return true;
}

bool FormOrcamento::validarAprovacaoProposta()
{
  if(m_estado != Edicao) {
    QMessageBox::warning(this, "Validação da aprovação da proposta...", "É necessário que um orçamento esteja carregado.");
    return false;
  }
  if(ui->lineEditNumeroPedido->text().isEmpty()) {
    QMessageBox::warning(this, "Validação da aprovação da proposta...", "Por favor preencha o número do pedido do cliente.");
    return false;
  }
  return true;
}

void FormOrcamento::atualizarListaAnexos(const int idOrcamento)
{
  // Atualiza a lista da tabela de anexos...
  QStringList listaCaminhos = listarCaminhoRecurso(Producao::R_Anexo_ID);
  QString strExtrairObjeto;
  for(const auto &str : listaCaminhos) {
    strExtrairObjeto.append(QString("->'%1'").formatArg(str));
  }
  QSqlQuery p(m_acesso->conexao());
  if(!p.prepare(QString("WITH tbl AS (SELECT a.id, r.detalhe%1 AS arquivo, r.id FROM producao.anexos AS a INNER JOIN producao.recursos AS r ON a.id_recurso = r.id WHERE id_orcamento = ?) SELECT * FROM tbl WHERE arquivo IS NOT NULL;").formatArg(strExtrairObjeto))) {
    spdlog::error("Falha ao preparar o comando para atualizar a lista de anexos deste orçamento.\n{}", p.lastError().text().toStdString());
  }
  p.bindValue(0, idOrcamento);
  if(!p.exec())
    spdlog::error("Falha ao executar o comando para atualizar a lista de anexo.");
  infoOrcamento.anexos.tbl_anexos->setQuery(p);
  nomearColunas(infoOrcamento.anexos.tbl_anexos, {"ID", "Nome do arquivo"});
  ui->tableViewAnexos->setColumnHidden(2, true);
  ui->tableViewAnexos->resizeColumnsToContents();
  if(infoOrcamento.anexos.tbl_anexos->lastError().isValid()) {
    spdlog::warn("Falha no comando da tabela tbl_anexos. {}", infoOrcamento.anexos.tbl_anexos->lastError().text().toStdString());
  }
}

void FormOrcamento::atualizarTiposPropostas(const int idTipoProposta)
{
  for(int l=0; l < infoProposta.tipoProposta.tbl_tiposPropostas->rowCount(); ++l) {
    auto id = infoProposta.tipoProposta.tbl_tiposPropostas->index(l, 0).data().toInt();
    if(id == idTipoProposta) {
      ui->comboBoxTipoProposta->setCurrentIndex(l);
      return;
    }
  }
}
QStringList FormOrcamento::listarCaminhoRecurso(const QString &caminho)
{
  QStringList lista;
  for(int i=0, f=0; i < caminho.size(); i = f) {
    f = caminho.find('/', i + 1);
    QString str;
    if(f < 0) {
      f = caminho.size();
      str = QString(caminho.substr(i + 1));
    }else {
      str = QString(caminho.substr(i + 1, (f - i) - 1));
    }
    if (!str.isEmpty())
      lista.append(str);
  }
  return lista;
}
