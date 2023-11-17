#pragma once

#include <mitor/sql/sqlnucleo.hpp>
#include <MitoR/MitoR.hpp>
#include <QString>
#include <QStringView>
#include <QVector>
#include <QVariant>
#include <QPair>
#include <QSqlDatabase>
#include <QSqlField>
#include <QSqlRecord>
#include <QSqlIndex>
#include <qalgorithms.h>
#include <algorithm>
#include <memory>

namespace MitoR::Sql {
    
    /**
     * @brief Está classe cria um modificador de dados programaticos para inserir
     * um novo registro em uma tabela de um banco de dados PostgreSQL.
     * @details  Está classe de alto nível fornece um meio programatico de inserir
     * um novo registro onde o valor de sua chave primária é obtido através de uma
     * segunda tabela que contém uma coluna que armazena a ultima chave primária
     * númerica armazenada que é o proximo identificador vago.
     * Para utilizar está classe é preciso que a tabela que sofrerá a adição de um
     * registro contenha uma segunda tabela no mesmo schema com o nome index.
     * Uma coluna deve ser adicionada com a junção do nome da chaveprimaria e
     * o nome da tabela.
     * Lembrando que a tabela index contém apenas um registro.
     * Sintaxe do comando de inserção:
     *
     * WITH ret AS (INSERT INTO {tabela} ( "{idPrimaryKey}", {colunas} ) VALUES ( (SELECT "{indexPrimaryKey}" FROM {tabelaIndex})+1, {valores} ) RETURNING "{idPrimaryKey}") UPDATE {tabelaIndex} SET "{indexPrimaryKey}"=(ret."{idPrimaryKey}") FROM ret RETURNING "{indexPrimaryKey}";
     *
     * Isto cria um registro em apenas um comando e garante que em nenhuma outra
     * inserção conterá o mesmo número de chave primária e elimina alguns problemas
     * que surgem ao utilizar SERIAL ou BIGSERIAL como geradores de chaves primárias.
     * Um desses problemas é a perca do número em uma inserção quando é necessário
     * retroagir as transações do banco de dados.
     *
     */
    class EXP_IMP_DECL InserirRegistrosComIndex
        : public QObject
    {
    CS_OBJECT(InserirRegistrosComIndex)
        
        struct Impl;
        std::shared_ptr<struct Impl> impl;
    
    public:
        InserirRegistrosComIndex(QSqlDatabase &bd, const QString &tabela, const QString &esquema = "",
                                 QObject *pai = nullptr);
        
        bool valido() const;
        
        bool enviar(const QSqlRecord &registro);
        
        QSqlRecord registroSemValores() const;
        
        QSqlRecord ultimoRegistroInserido() const;
      
    };
    
    
    /**
     * @brief Está classe é capaz de atualizar um registro do banco de dados.
     * @details Está classe de alto nível fornece um meio de atualizar um registro
     * em uma tabela do banco de dados.
     */
    class EXP_IMP_DECL AtualizarRegistros
        : public QObject
    {
    CS_OBJECT(AtualizarRegistros)
        
        struct Impl;
        std::shared_ptr<struct Impl> impl;
    
    public:
        AtualizarRegistros(QSqlDatabase &bd, const QString &tabela, const QString &esquema = "",
                           QObject *pai = nullptr);
        
        bool valido() const;
        
        bool enviar(const QSqlRecord &registro);
        
        QSqlRecord registroSemValores() const;
      
    };
  
  
}//fim do namespace ::Sql.

