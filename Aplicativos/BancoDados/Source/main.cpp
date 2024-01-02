#include <QtCore>
#include <QtGui>
#include <QtSql>
#include <MitoR/Log.hpp>
#include <MitoR/Sql/tabelasql.hpp>
#include <MitoR/Sql/tabelactsql.hpp>
#include <windows.h>

void iniciarBancoDados();
void printRecord(QSqlRecord &reg, QTextStream &out);

int main(int nArgs, char *pArgs[])
{
  // Para que as mensagens sejam mostradas corretamente na saída padrão.
  SetConsoleOutputCP(CP_UTF8);
  MitoR::Log::inicializar("bd_log.txt", spdlog::level::debug);

  QApplication app(nArgs, pArgs);
  QTextStream out(stdout);
  QTextStream in(stdin);
  in.setCodec("Latin1"); // para entrar com caracteres não asc-2.

  iniciarBancoDados();
  out << "Estudo do banco de dados da empresa A.M.E.\n";
  out.flush();

  auto bd = QSqlDatabase::database();
  QSqlQuery p(bd);
  if(false) {
    MitoR::Sql::TabelaCtSql tblPartesProjetos("producao.partes_projetos");
    QSqlRecord reg = bd.record("producao.partes_projetos");
    reg.setValue({"id_projeto"}, 2);
    reg.setValue({"numero_parte"}, QString{"5304-Caixa Painel CPG"});
    reg.setValue({"descricao"}, QString{"Painel principal geral"});
    reg.setValue({"material"}, QString{"Aço-1020"});
    reg.setValue({"quantidade"}, 1);
    reg.setValue({"dimensao_acabada"}, QString{"600 x 1000 x 340mm"});
    //reg.setValue({"dimensao_bruta"}, QString{""});
    if (auto err = tblPartesProjetos.inserirRegistroComIndex(reg, p, 0); err == err.Falhou) {
      spdlog::error("Falha ao inserir o registro.\n{}", err.msg.toStdString());
    } else {
      spdlog::info("Registro {} inserido.", reg.value("id").toInt());
    }
  }
  if(false) {
    MitoR::Sql::TabelaSql tblMateriais;
    QSqlRecord reg = bd.record("cadastro.materiais");
    reg.setValue({"descricao"}, QString{"CLP MITSUBISHI FX5UC-32MT/DSS-TS - 16 ENTR. 16 SAIDAS"});
    reg.setValue({"codigo"}, QString("FX5UC-32MT/DSS-TS"));
    reg.setValue({"id_classificacao"}, 57);
    if(auto err = tblMateriais.inserirRegistro("cadastro.materiais", p, reg); err == err.Falhou) {
      spdlog::error("Falha ao inserir o registro.\n{}", err.msg.toStdString());
    }else {
      spdlog::info("Registro {} inserido.", reg.value("id").toInt());
    }
  }
  if(false) {
    MitoR::Sql::TabelaSql tblListaMateriais;
    QSqlRecord reg = bd.record("producao.lista_materiais");
    reg.setValue({"id_parte"}, 4);
    reg.setValue({"id_material"}, 2);
    reg.setValue({"quantidade"}, 1);
    reg.setValue({"id_tipo_material"}, 4);
    reg.setValue({"id_formato_material"}, 4);
    reg.setValue({"d1"}, 42.1);
    reg.setValue({"d2"}, 89);
    reg.setValue({"d3"}, 93.5);
    reg.setValue({"peso"}, 0.28);
    reg.setValue({"data"}, QDate::currentDate());
    if(auto err = tblListaMateriais.inserirRegistroComIndex("producao.lista_materiais", p, reg); err == err.Falhou) {
      spdlog::error("Falha ao inserir o registro.\n{}", err.msg.toStdString());
    }else {
      spdlog::info("Registro {} inserido.", reg.value("id").toInt());
    }
  }


  MitoR::Log::finalizar();
  return 0;
}

void iniciarBancoDados()
{
  QSqlDatabase bd = QSqlDatabase::addDatabase("QPSQL");
  bd.setHostName("localhost");
  bd.setDatabaseName("controle");
  bd.setUserName("postgres");
  // sem senha pois estamos na maquina que hospeda o servidor.
  if(bd.open() == false) {
    spdlog::warn("Não foi possível abrir a conexão com o banco de dados.\n{}", bd.lastError().text().toStdString());
  }else {
    spdlog::info("Conexão com o banco de dados aberta.");
  }
}
void printRecord(QSqlRecord &reg, QTextStream &out)
{
  for(int i=0; i < reg.count(); ++i)
    out << reg.fieldName(i) << " = " << reg.value(i).toString() << ", ";
  out << '\n';
  out.flush();
}