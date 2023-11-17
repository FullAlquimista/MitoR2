#pragma once

#include <MitoR/MitoR.hpp>
#include <qalgorithms.h>
#include <algorithm>
#include <memory>

namespace MitoR::Sql
{
  /**
   * @details A técnica de armazenamento Closure Table é uma maneira eficiente de representar uma hierarquia de dados,
   * como uma árvore, em uma base de dados relacional. Em vez de armazenar a estrutura da árvore como uma série de
   * relações entre os nós, a Closure Table armazena cada relação entre os nós como uma linha na tabela auxiliar.
   * Cada linha na tabela representa uma ligação entre um "nodo" (um nó da árvore) e um de seus "ramos" (os filhos do nodo).
   * A tabela contém duas colunas principais: "descendente" e "ascendente". A coluna "descendente" representa o nodo filho
   * e a coluna "ascendente" representa o nodo pai.
   * Assim, para encontrar todos os ramos de um nodo, você simplesmente procura na tabela todas as linhas em que o nodo em
   * questão é o nodo "ascendente". Da mesma forma, para encontrar o nodo pai de um ramo, você procura na tabela a linha em
   * que o ramo em questão é o nodo "descendente".
   * Além disso, a Closure Table também pode ser usada para encontrar facilmente todos os ancestrais de um nodo ou todos os
   * descendente de um nodo, sem precisar percorrer a árvore inteira.
   * Este conceito se aplica a qualquer tipo de tabela pois o armazenamento dos nodos são da mesma forma e o que
   * varia é a tabela com o registro que serão controlados e que tenha uma coluna index para identificar na tabela auxiliar
   * as relações de descendência e ascendência.
   * Dado uma tabela hipotética teste com as colunas:
   *  teste [id, descricao, valor].
   * A tabela auxiliar seria criada com o seguinte formato:
   *  teste_ct [id, id_ramo, id_no, nivel].
   *
   *
   *
   */
   
  /**
   * @details Está função extrai de um identificador de tabela o esquema e o nome da tabela.
   * @param tabela - identificador completo da tabela.
   * @param esquema - o esquema que será extraido do identificador.
   * @param nomeTabela - o nome da tabela que será extraído do identificador.
   */
  [[maybe_unused]] void EXP_IMP_DECL extrairIdentificadoresTabela(QString &tabela, QStringView &esquema, QStringView &nomeTabela);
   
}// fim do namespace ::Sql.

