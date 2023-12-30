---
tags:
  - postgres
  - banco_dados
  - tutorial
  - comandos
  - clousure_table
---

# PostgreSQL
É o banco de dados utilizado neste sistema para armazenar as informações.  Anotações de comandos e explicações do banco.

## Conceitos básicos:
 - Tabelas: É uma coleção de linhas onde todas as linhas tem o mesmo número de colunas, cada  coluna com o seu tipo de dado.
 - Banco de dados é uma coleção de tabelas. E um conjunto de banco de dados formam um glomerado de banco de dados (Database Cluster).
 - Um comentário no SQL (PostgreSQL) é seguido pela sequencia de caracteres "--".

## Comandos principais
Fazendo um backup do banco de dados.  
Utilizando o comando pg_dump:  
pg_dumpall -h 192.168.1.100 -U postgres > dumbfile.txt  
  
Para restaurar:  
psql -h 192.168.1.100 -U postgres -f dumbfile.txt postgres

#### Criando um novo tipo de dados

Criando o tipo para sexo.
```
CREATE TYPE sexo AS ENUM ('M', 'F');
```
Modificando uma tabela:
```
ALTER TABLE cliente ALTER COLUMN s TYPE sexo USING s::sexo;
```
Utilizado para liberar o acesso a todas as sequencias das tabelas em um schema
para um usuário.
```
GRANT USAGE, SELECT ON ALL SEQUENCES IN SCHEMA cadastro TO usuarios;
```
#### Criando uma lista lincada (Clousure Table)
Uma tabela fechada ou lista auxiliar lincado oferece para determinados registros de uma tabela a  possibilidade de criar relações de nível hierárquico. Está relação é criada utilizando vínculos de chave estrangeira entre as tabelas.

Para um melhor entendimento criemos uma tabela chamada 'itens'. Contendo as colunas, 'id' e  'descricao'. Para criar as relações entre os registros desta tabela uma segunda tabela auxiliar deve ser criada com o nome de 'itens_ct'. Está contém as colunas 'id', 'id_item',  'id_no', 'nivel'.

Quando um novo registro é criado na tabela 'itens',  mesmo que não tenha relação com nenhum outro 'item', um registro deve ser inserido também na tabela auxiliar onde a coluna 'id_item' indica o 'id' do registro inserido e 'id_no' também deve conter o mesmo 'id' do item inserido com o valor de 'nivel' 0. Indicando que este item é um nó. Todo 'item' é um nó que posteriormente pode ter ramos a outros itens. Este é o significado do valor nível 0.
### Comandos:
Inseri um novo registro e o linca a outro registro identificado pelo id_item = x. Se o valor de x for 0, este registro será apenas um nó e não estará lincado a outro nó. Ex: Cria um novo 'item' '1932-11-01' e o linca ao registro com id = 9.
```
BEGIN; 
WITH item_inserido AS ( 
    INSERT INTO cadastro.planos_contas (descricao) VALUES ('Teste') RETURNING * 
) 
INSERT INTO cadastro.planos_contas_ct (id_item, id_no, nivel) 
    ( SELECT ii.id, ii.id, 0 FROM item_inserido ii UNION ALL 
        SELECT ii.id, lk.id_no, lk.nivel - 1 FROM item_inserido ii, cadastro.planos_contas_ct lk WHERE id_item = 6 
    ) RETURNING *; 
SELECT * FROM cadastro.planos_contas_ct lk, cadastro.planos_contas i WHERE lk.id_item = i.id ORDER BY lk.id_item, lk.nivel; 
ROLLBACK;
```
Adiciona um linque entre dois registros existentes. Lembrando que o linque não deve ter um nó. Ex: Adiciona o 'item' com id = 6 como nó do 'item' com id = 8. 
```
BEGIN; 
WITH item_adicionado AS (
    INSERT INTO itens_lk (id_item, id_no, nivel) (
        SELECT 10, lk.id_no, lk.nivel - 1 FROM itens_lk lk WHERE lk.id_item = 6) RETURNING *
    ) 
SELECT * FROM item_adicionado; 
COMMIT;
-- Adiciona também aos itens que herdam o item com id = 8.
BEGIN; 
INSERT INTO itens_lk (id_item, id_no, nivel) (
    WITH itens_atualizar AS (
        SELECT * FROM itens_lk lk WHERE lk.id_no = 8 AND lk.id_item <> 8 ORDER BY lk.id_item, nivel
    )
    SELECT ia.id_item, lk.id_no, (ia.nivel + lk.nivel) AS nivel FROM itens_atualizar ia, itens_lk lk WHERE lk.id_item = 8 AND lk.id_no <> 8 ORDER BY ia.id_item
); 
SELECT * FROM itens_lk, itens WHERE itens_lk.id_item = itens.id ORDER BY itens_lk.id_item, nivel; 
COMMIT;
```
Remove o nó de um 'item'. Ex: Apaga o nó do 'item' = 10.
```
BEGIN; 
WITH itens_encontrados AS (
    SELECT * FROM itens_lk lk WHERE lk.id_no = 10 ORDER BY lk.id_item
)
DELETE FROM itens_lk lk USING itens_encontrados e 
    WHERE lk.id_item = e.id_item AND lk.nivel < e.nivel; 
SELECT * FROM itens_lk, itens 
    WHERE itens_lk.id_no = itens.id ORDER BY id_item, nivel;
ROLLBACK;
```
Remove um item e seus nós.
```
BEGIN; 
WITH remover AS (
	SELECT * FROM cadastro.planos_contas_ct WHERE id_no = 5 ORDER BY id_item, nivel
), 
ct_deletados AS (DELETE FROM cadastro.planos_contas_ct ct USING remover r WHERE ct.id_item = r.id_item RETURNING ct.id_item
),
deletados AS (DELETE FROM cadastro.planos_contas p USING ct_deletados d WHERE p.id = d.id_item RETURNING *)
SELECT * FROM deletados;
COMMIT;
```
Removendo registros de uma tabela ignorando os registros ainda referenciados:
```
DO $$
DECLARE
    t cadastro.planos_contas%rowtype;
BEGIN
      FOR t IN 
      SELECT * FROM cadastro.planos_contas
      LOOP
        RAISE NOTICE 'Tentando remover id %',t.id;
          BEGIN
              DELETE FROM cadastro.planos_contas WHERE id=t.id;
              RAISE NOTICE 
              'Id deletado: %',t.id;
          EXCEPTION
              WHEN others THEN 
                  -- we ignore the error
              END;
      END LOOP;
END $$;
```
