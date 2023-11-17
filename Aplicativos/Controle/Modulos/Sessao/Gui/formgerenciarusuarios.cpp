//
// Created by Robson on 27/05/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_FormGerenciarUsuarios.h" resolved

#include "formgerenciarusuarios.hpp"
#include "ui_formgerenciarusuarios.h"
#include <MitoR/Gui/dialogpesquisar.hpp>
#include <QRegularExpression>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardItem>
#include <QTreeView>
#include <QFlatMap>
#include <nlohmann/json.hpp>

FormGerenciarUsuarios::FormGerenciarUsuarios(QWidget *parent) : QWidget(parent), ui(new Ui::FormGerenciarUsuarios)
{
  ui->setupUi(this);

  _acesso = QApplication::instance()->findChild<Sessao::Acesso *>();
  if (!_acesso) {
    QMessageBox::warning(this, "Formulário: Gerenciador de usuários", "Falha ao carregar o componente 'Acesso'.");
    return;
  }

  _modelo.invisibleRootItem()->setColumnCount(3);
  _modelo.setHeaderData(0, Qt::Horizontal, QString("Identificação"));
  _modelo.setHeaderData(1, Qt::Horizontal, QString("Descrição"));
  _modelo.setHeaderData(2, Qt::Horizontal, QString("Acesso"));

  ui->treeViewDiretivas->setModel(&_modelo);
  ui->treeViewDiretivas->setSelectionMode(QTreeView::SelectionMode::SingleSelection);

  // Conexões...
  QObject::connect(ui->pushButtonPesquisar, &QPushButton::clicked, this, &FormGerenciarUsuarios::pesquisar);
  QObject::connect(ui->pushButtonAtualizar, &QPushButton::clicked, this, &FormGerenciarUsuarios::atualizarDiretivas);
  QObject::connect(ui->pushButtonSalvar, &QPushButton::clicked, this, &FormGerenciarUsuarios::salvar);
  QObject::connect(ui->pushButtonNovo, &QPushButton::clicked, this, &FormGerenciarUsuarios::novo);
  QObject::connect(ui->pushButtonLimpar, &QPushButton::clicked, this, &FormGerenciarUsuarios::limpar);
  QObject::connect(ui->pushButtonRemover, &QPushButton::clicked, this, &FormGerenciarUsuarios::remover);
}

FormGerenciarUsuarios::~FormGerenciarUsuarios()
{
  delete ui;
}
void FormGerenciarUsuarios::novo()
{
  switch(Erro e = [this]() -> Erro {
    if (ui->lineEditUsuario->text().isEmpty()) {
      return Erro{Erro::Falha, "Preencha o nome para o usuário."};
    }
    _registro.usuario = ui->lineEditUsuario->text();
    if (ui->lineEditSenha->text().isEmpty()) {
      return Erro{Erro::Falha, "Preencha uma senha para o usuário."};
    }
    if (ui->lineEditSenha->text() != ui->lineEditConfirmarSenha->text()) {
      return Erro{Erro::Falha, "A senha digitada não confere. Verifique a confirmação da senha."};
    }
    if (ui->comboBoxPrevilegio->currentText() == "Administrador") {
      _registro.nomePrevilegio = "administradores";
    } else if (ui->comboBoxPrevilegio->currentText() == "Usuário") {
      _registro.nomePrevilegio = "usuarios";
    } else {
      return Erro{Erro::Falha, "Previlégio não selecionado ou grupo não tratado pelo programa."};
    }
    QSqlQuery p(_acesso->conexao());
    if (!p.exec(QString("SELECT u.rolname, g.groname, u.oid, g.grolist FROM pg_catalog.pg_roles u INNER JOIN pg_group g ON u.oid = ANY(g.grolist) WHERE u.rolcanlogin = TRUE AND u.rolname LIKE '%1';").formatArg(_registro.usuario))) {
      return Erro{Erro::Falha, QString("Falha ao executar o pedido da procura do novo usuário.\n%1").formatArg(p.lastError().text())};
    }
    _acesso->conexao().transaction();
    if(!p.next()) {
      if (!p.exec(QString("CREATE ROLE %1 WITH LOGIN INHERIT ENCRYPTED PASSWORD '%2' IN GROUP %3;").formatArg(_registro.usuario).formatArg(ui->lineEditSenha->text()).formatArg(_registro.nomePrevilegio))) {
        return Erro{Erro::ErroComando, QString("Ocorreu uma falha ao executar o comando para criar um usuário.\n%1").formatArg(p.lastError().text())};
      }
      ui->lineEditSenha->clear();
      ui->lineEditConfirmarSenha->clear();
      if (!p.exec(QString("SELECT u.rolname, g.groname, u.oid, g.grolist FROM pg_catalog.pg_roles u INNER JOIN pg_group g ON u.oid = ANY(g.grolist) WHERE u.rolcanlogin = TRUE AND u.rolname LIKE '%1';").formatArg(_registro.usuario))) {
        return Erro{Erro::ErroComando, QString("Falha ao executar o pedido da procura do novo usuário.\n%1").formatArg(p.lastError().text())};
      }
      if(!p.next()) {
        return {Erro::ErroComando, "Não foi encontrado o usuário recém criado!!!"};
      }
    }else {
      return Erro{Erro::Falha, QString("Este usuário já existe no sistema.")};
    }
    auto reg = p.record();
    _registro.id = reg.value(2).toInt();

    if (!p.exec(QString("INSERT INTO seguranca.diretivas (id, nome, acesso) VALUES (%1, '%2', '{}'::jsonb);").formatArg(_registro.id).formatArg(_registro.usuario))) {
      return Erro{Erro::ErroComando, QString{"Falha ao executar o comando que adiciona o seguinte usuário a tabela de diretivas de segurança.\n%1"}.formatArg(p.lastError().text())};
    }

    return {Erro::Sucesso};
  }()) {
    case Erro::Sucesso: {
      _acesso->conexao().commit();
    }break;
    case Erro::Falha: {
      QMessageBox::warning(this, "Novo...", e.msg);
      _acesso->conexao().rollback();
    }break;
    case Erro::ErroComando: {
      QMessageBox::warning(this, "Novo...", e.msg);
      _acesso->conexao().rollback();
    }break;
  }
}
void FormGerenciarUsuarios::pesquisar()
{
  switch(Erro e = [this]() -> Erro {
    // Pesquisando roles no sistema.
    QSqlQueryModel modelo;
    QSqlQuery p(_acesso->conexao());
    if (!p.exec(QString("select u.rolname, g.groname, u.oid, g.grolist FROM pg_roles u INNER JOIN pg_group g ON u.oid = ANY(g.grolist) WHERE u.rolcanlogin = true AND u.rolname LIKE '%%1%';").formatArg(ui->lineEditUsuario->text()))) {
      return {Erro::Falha, QString("Falha ao executar o pedido:\n%1").formatArg(p.lastError().text())};
    }
    modelo.setQuery(p);
    QSqlRecord reg;
    if (modelo.rowCount() > 1) {
      modelo.setHeaderData(0, Qt::Horizontal, QString("Nome do usuário"));
      modelo.setHeaderData(1, Qt::Horizontal, QString("Previlégio"));
      modelo.setHeaderData(2, Qt::Horizontal, QString("ID do usuário"));
      auto dialog = DialogPesquisar(&modelo, this);
      auto view = dialog.visualizacao();
      view->setColumnHidden(2, true);
      view->setColumnHidden(3, true);
      int res = dialog.exec();
      if (res > 0) {
        reg = modelo.record(dialog.linhaSelecionada());
      }else {
        return {Erro::Sucesso};
      }
    } else if (modelo.rowCount() == 1) {
      reg = modelo.record(0);
    } else {
      return {Erro::Falha, QString("Não foi possível encontrar o usuário descrito pelo campo 'Usuário' no sistema.")};
    }

    // Carregando registro encontrado.
    const QString previlegio = reg.value(1).toString();
    for (auto i = 0; i < ui->comboBoxPrevilegio->count(); i++) {
      if (ui->comboBoxPrevilegio->itemText(i) == "Administrador" && (previlegio == "administradores")) {
        ui->comboBoxPrevilegio->setCurrentIndex(i);
        break;
      } else if (ui->comboBoxPrevilegio->itemText(i) == "Usuário" && (previlegio == "usuarios")) {
        ui->comboBoxPrevilegio->setCurrentIndex(i);
        break;
      }
    }
    ui->lineEditUsuario->setText(reg.value(0).toString());
    _registro.id = reg.value(2).toInt();
    _registro.usuario = reg.value(0).toString();
    _registro.nomePrevilegio = reg.value(1).toString();
    _registro.jDiretiva.clear();

    // Carregando as diretivas do registro.
    if (!p.exec(QString("SELECT acesso FROM seguranca.diretivas WHERE nome LIKE '%1'").formatArg(ui->lineEditUsuario->text()))) {
      return Erro{Erro::Falha, QString("Falha ao executar o pedido de carregamento das diretivas de segurança do usuário '%1'.\n%2").formatArg(ui->lineEditUsuario->text()).formatArg(p.lastError().text())};
    }
    if (p.next()) {
      QString data = p.value(0).toString().toUtf8();
      try {
        _registro.jDiretiva = Json::parse(data.toStdString());
      } catch (std::exception &e) {
        return Erro{Erro::Falha, QString("Falha ao interpretar a diretiva de segurança do usuário '%1'.\n%2").formatArg(ui->lineEditUsuario->text()).formatArg(QString::fromStdString(e.what()))};
      }
    }
    preencherModelo();

    return {Erro::Sucesso};
  }()) {
    case Erro::Sucesso: {

    }break;
    case Erro::ErroComando: {
      QMessageBox::warning(this, "Pesquisar...", e.msg);
    }break;
    case Erro::Falha: {
      QMessageBox::warning(this, "Pesquisar...", e.msg);
    }break;
  }
}
void FormGerenciarUsuarios::salvar()
{
  switch (Erro e = [this]() {
    auto res = QMessageBox::question(this, QString("Salvando..."), QString("Deseja realmente salvar as alterações das diretivas de segurança deste usuário ?"), QString("Sim"), QString("Não"));
    if (res != 0)
      return Erro{Erro::Sucesso};

    QSqlQuery p(_acesso->conexao());
    if (!ui->lineEditSenha->text().isEmpty()) {
      if (ui->lineEditSenha->text() == ui->lineEditConfirmarSenha->text()) {
        return Erro{Erro::Falha, "A senha não confere. Verifique a senha e sua confirmação."};
      }
      if (!p.exec(QString("ALTER ROLE %1 WITH ENCRYPTED PASSWORD '%2';").formatArg(_registro.usuario).formatArg(ui->lineEditSenha->text()))) {
        return Erro{Erro::Falha, QString("Falha ao tentar alterar a senha deste usuário.\n%1").formatArg(p.lastError().text())};
      }
    }

    // Salva as informações do modelo na memória JSON.
    QVector<QModelIndex> listaLeitura;
    listaLeitura.push_back(QModelIndex()); // Model index que referencia a raiz do modelo.
    for(int i=0; i < listaLeitura.size(); ++i)
    {
      auto parentIndex = listaLeitura[i];
      for(int row=0; row < _modelo.rowCount(parentIndex); ++row)
      {
        listaLeitura.push_back(_modelo.index(row, 0, parentIndex));
        for(int column=0; column < _modelo.columnCount(parentIndex); ++column) {
          auto index = _modelo.index(row, column, parentIndex);
          if(index.data(JsonPathRole).isValid()) {
            const auto Chave = Json::json_pointer(index.data(JsonPathRole).toString().toStdString());
            bool ok{false};
            int valor = index.data(Qt::DisplayRole).toInt(&ok);
            if(ok)
              _registro.jDiretiva[Chave] = valor;
          }
        }
      }
    }

    if (!p.exec(QString("SELECT * FROM seguranca.diretivas WHERE id = %1").formatArg(_registro.id))) {
      return Erro{Erro::Falha, QString{"Falha ao executar o comando pesquisar o usuário.\n%1"}.formatArg(p.lastError().text())};
    }
    if (!p.next()) {
      if (!p.exec(QString("INSERT INTO seguranca.diretivas (id, nome, acesso) VALUES (%1, '%2', '{}'::jsonb);").formatArg(_registro.id).formatArg(_registro.usuario))) {
        return Erro{Erro::Falha, QString{"Falha ao executar o comando que adiciona o seguinte usuário a tabela de diretivas de segurança.\n%1"}.formatArg(p.lastError().text())};
      }
    }

    if (!p.exec(QString("UPDATE seguranca.diretivas SET acesso = '%1'::jsonb WHERE id = %2;").formatArg(QString::fromUtf8(_registro.jDiretiva.dump().c_str())).formatArg(_registro.id))) {
      return Erro{Erro::Falha, QString{"Falha ao executar o comando para salvar as diretivas deste usuário.\n%1"}.formatArg(p.lastError().text())};
    }
    return Erro{Erro::Sucesso};
  }()) {
    case Erro::Sucesso: {
    } break;
    case Erro::Falha: {
      QMessageBox::warning(this, "Salvar...", e.msg);
    } break;
  }
}
bool FormGerenciarUsuarios::limpar()
{
  _modelo.removeRows(0, _modelo.rowCount());

  ui->lineEditUsuario->clear();
  ui->lineEditSenha->clear();
  ui->lineEditConfirmarSenha->clear();
  _registro.usuario = "";
  _registro.id = 0;
  _registro.jDiretiva.clear();

  return true;
}
void FormGerenciarUsuarios::remover()
{
  switch (Erro e = [this]() -> Erro {
    int res = QMessageBox::question(this, "Removendo...", "Tem certeza que deseja remover as informações da diretiva de acesso deste usuário ?", "Sim", "Não");
    if (res != 0)
      return Erro{Erro::Sucesso};
    if(_registro.id == 0)
      return {Erro::Sucesso, "Nenhum registro de usuário foi carregado para ser removido.\n registro.id = 0."};
    if(_registro.usuario.isEmpty())
      return {Erro::Sucesso, "O formulário se encontra invalido"};
    QSqlQuery p(_acesso->conexao());
    if (!p.exec(QString("DELETE FROM seguranca.diretivas WHERE id = %1").formatArg(_registro.id))) {
      return Erro{Erro::Falha, QString("Falha ao tentar demover as diretivas de segurança deste usuário.\n%1").formatArg(p.lastError().text())};
    }
    _modelo.clear();
    _registro.jDiretiva.clear();
    res = QMessageBox::question(this, "Removendo...", "Tem certeza que deseja remover este usuário ?", "Sim", "Não");
    if (res != 0)
      return Erro{Erro::Sucesso};
    if (!p.exec(QString("DROP ROLE %1;").formatArg(_registro.usuario))) {
      return Erro{Erro::Falha, QString("Falha ao tentar remover este usuário.\n%1").formatArg(p.lastError().text())};
    }

    return Erro{Erro::Sucesso};
  }()) {
    case Erro::Sucesso: {
    } break;
    case Erro::Falha: {
      QMessageBox::warning(this, "Salvar...", e.msg);
    } break;
  }
}
void FormGerenciarUsuarios::atualizarDiretivas()
{
  if (_acesso) {
    auto pDiretivasAtualizadas = _acesso->obterDiretivas();
    auto jFlat = pDiretivasAtualizadas->flatten();
    for (auto itJ: jFlat.items()) {
      auto ptr_json = Json::json_pointer(itJ.key());
      if (!_registro.jDiretiva.contains(ptr_json))
        _registro.jDiretiva.operator[](ptr_json) = itJ.value();
    }
    preencherModelo();
  }
}
void FormGerenciarUsuarios::preencherModelo()
{
  // Apaga o modelo sem apagar as colunas e cabeçalhos.
  _modelo.removeRows(0, _modelo.rowCount());

  struct Registro {
    Json *pJson{nullptr};
    QString path{};
    QStandardItem *itemPai{nullptr};
    QFlatMap<QString, QStandardItem*> itens{};
  };
  QVector<Registro*> listaLeitura;
  listaLeitura.push_back(new Registro{&_registro.jDiretiva, QString() });
  for(int r=0; r < listaLeitura.size(); ++r)
  {
    auto reg = listaLeitura[r];
    QVector<int> idxFilhosAdicionados;
    for(auto itJson : reg->pJson->items())
    {
      if(itJson.value().is_object()) {
        listaLeitura.push_back(new Registro{&itJson.value(), QString("%1/%2").formatArg(reg->path).formatArg(QString::fromStdString(itJson.key()))});
        idxFilhosAdicionados.push_back(listaLeitura.size() - 1);
      }else {
        if(itJson.key() == Sessao::IAcesso::iNome) {
          reg->itens[QString::fromStdString(Sessao::IAcesso::iNome)] = new QStandardItem(QString::fromUtf8(itJson.value().get<std::string>().c_str()));
          reg->itens[QString::fromStdString(Sessao::IAcesso::iNome)]->setEditable(false);
        }else if(itJson.key() == Sessao::IAcesso::iDescricao) {
          reg->itens[QString::fromStdString(Sessao::IAcesso::iDescricao)] = new QStandardItem(QString::fromUtf8(itJson.value().get<std::string>().c_str()));
          reg->itens[QString::fromStdString(Sessao::IAcesso::iDescricao)]->setEditable(false);
        }else if(itJson.key() == Sessao::IAcesso::iAcesso) {
          reg->itens[QString::fromStdString(Sessao::IAcesso::iAcesso)] = new QStandardItem(QString("%1").formatArg(itJson.value().get<int>()));
          reg->itens[QString::fromStdString(Sessao::IAcesso::iAcesso)]->setData(QString("%1/%2").formatArg(reg->path).formatArg(QString::fromStdString(Sessao::IAcesso::iAcesso)), JsonPathRole);
        }
      }
    }
    if(!reg->itemPai) {
      reg->itemPai = _modelo.invisibleRootItem();
    }
    for(auto idx : idxFilhosAdicionados) {
      auto regFilho = listaLeitura[idx];
      if (reg->itens.contains(QString::fromStdString(Sessao::IAcesso::iNome)))
        regFilho->itemPai = reg->itens[QString::fromStdString(Sessao::IAcesso::iNome)];
      else
        regFilho->itemPai = reg->itemPai;
    }
    int linha = reg->itemPai->rowCount();
    if(reg->itens.contains(QString::fromStdString(Sessao::IAcesso::iNome))) {
      reg->itemPai->setChild(linha, 0, reg->itens[QString::fromStdString(Sessao::IAcesso::iNome)]);
      // Somente tenta adicionar a descrição e acesso caso a linha seja adicionada pois depende do dispositivo nome existir.
      if(reg->itens.contains(QString::fromStdString(Sessao::IAcesso::iDescricao))) {
        reg->itemPai->setChild(linha, 1, reg->itens[QString::fromStdString(Sessao::IAcesso::iDescricao)]);
      }else {
        reg->itemPai->setChild(linha, 1, new QStandardItem);
        reg->itemPai->child(linha, 1)->setEditable(false);
      }
      if(reg->itens.contains(QString::fromStdString(Sessao::IAcesso::iAcesso))) {
        reg->itemPai->setChild(linha, 2, reg->itens[QString::fromStdString(Sessao::IAcesso::iAcesso)]);
      }else {
        reg->itemPai->setChild(linha, 2, new QStandardItem);
        reg->itemPai->child(linha, 2)->setEditable(false);
      }
    }
  }
  ui->treeViewDiretivas->expandAll();
  ui->treeViewDiretivas->resizeColumnToContents(0);
  ui->treeViewDiretivas->resizeColumnToContents(1);
  ui->treeViewDiretivas->resizeColumnToContents(2);
}
void FormGerenciarUsuarios::alterarEstadoFormulario(int)
{
}

/*
void FormGerenciarUsuarios::novo()
{
}
void FormGerenciarUsuarios::salvar()
{
}
bool FormGerenciarUsuarios::limpar()
{
}
void FormGerenciarUsuarios::atualizarDiretivas()
{
}
void FormGerenciarUsuarios::estruturarDiretivaUsuario()
{
  _raizDiretiva.reset();
  _raizDiretiva = std::make_shared<EstruturaItem>();
  _raizDiretiva->pJ = &_registro.diretivaJson;
  QVector<std::shared_ptr<EstruturaItem>> listaLeitura;
  listaLeitura.push_front(_raizDiretiva);
  while (!listaLeitura.isEmpty()) {
    auto pItem = listaLeitura.back();
    for (auto itJ: pItem->pJ->items()) {
      auto pItemFilho = std::make_shared<EstruturaItem>();
      if (itJ.value().is_object()) {
        pItemFilho->id.emplace(fmt::format("{}/{}", pItem->id.value_or(""), itJ.key()));
        pItemFilho->pJ = &itJ.value();
        pItemFilho->pai = pItem;
        listaLeitura.push_front(pItemFilho);
        pItem->filhos.push_back(pItemFilho);
      } else {
        if (itJ.key() == Sessao::IAcesso::iNome) {
          pItem->nome.emplace(itJ.value().get<std::string>());
        } else if (itJ.key() == Sessao::IAcesso::iDescricao) {
          pItem->descricao.emplace(itJ.value().get<std::string>());
        } else if (itJ.key() == Sessao::IAcesso::iAcesso) {
          pItem->acesso.emplace(itJ.value().get<int>());
        }
      }
    }
    listaLeitura.pop_back();
  }
}
void FormGerenciarUsuarios::preencherModelo()
{
  _modelo.clear();
  _modelo.setColumnCount(3);
  _modelo.setHeaderData(0, Qt::Horizontal, QString("Nome Dispositivo"));
  _modelo.setHeaderData(1, Qt::Horizontal, QString("Descrição"));
  _modelo.setHeaderData(2, Qt::Horizontal, QString("Acesso"));

  QVector<std::shared_ptr<EstruturaItem>> listaLeitura;
  listaLeitura.push_front(_raizDiretiva);
  _raizDiretiva->itens.push_back(_modelo.invisibleRootItem());
  //spdlog::info("\n{}", _registro.diretivaJson.dump(2));
  while (!listaLeitura.isEmpty()) {
    auto pItem = listaLeitura.back();
    auto itemPai = pItem->itens.front();
    for (auto item: pItem->filhos) {
      listaLeitura.push_front(item);
      if (item->nome) {
        int numeroColunas = 1;
        QStandardItem *itemNome = new QStandardItem(QString::fromUtf8((*item->nome).c_str()));
        itemNome->setData(QString::fromStdString(*item->id), Qt::UserRole + 1);
        item->itens.push_back(itemNome);
        QStandardItem *itemDescricao{nullptr};
        if (item->descricao) {
          itemDescricao = new QStandardItem(QString::fromUtf8((*item->descricao).c_str()));
          item->itens.push_back(itemDescricao);
          ++numeroColunas;
        }
        QStandardItem *itemAcesso{nullptr};
        if (item->acesso) {
          itemAcesso = new QStandardItem(QString("%1").formatArg(*item->acesso));
          item->itens.push_back(itemAcesso);
          ++numeroColunas;
        }
        if (itemPai->columnCount() < numeroColunas)
          itemPai->setColumnCount(numeroColunas);

        int linhaDisponivel = itemPai->rowCount();
        itemPai->setChild(linhaDisponivel, 0, itemNome);
        if (itemDescricao)
          itemPai->setChild(linhaDisponivel, 1, itemDescricao);
        if (itemAcesso)
          itemPai->setChild(linhaDisponivel, 2, itemAcesso);
      } else {
        item->itens.push_back(itemPai);
      }
    }

    listaLeitura.pop_back();
  }
}
void FormGerenciarUsuarios::alterarEstadoFormulario(int novoEstado)
{
  _estado = novoEstado;
  if (_estado == Vazio) {
    ui->lineEditUsuario->setEnabled(true);
    ui->pushButtonNovo->setEnabled(true);
    ui->pushButtonSalvar->setEnabled(false);
    ui->pushButtonAtualizar->setEnabled(false);
    ui->pushButtonPesquisar->setEnabled(true);
    ui->pushButtonRemover->setEnabled(false);
  }
  if ((_estado & Editado) > 0 || ((_estado & Carregado) > 0)) {
    ui->lineEditUsuario->setEnabled(false);
    ui->pushButtonNovo->setEnabled(false);
    ui->pushButtonSalvar->setEnabled(true);
    ui->pushButtonRemover->setEnabled(true);
    ui->pushButtonAtualizar->setEnabled(true);
  }
}
void FormGerenciarUsuarios::remover()
{
}
*/