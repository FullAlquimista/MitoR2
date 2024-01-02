---
tags:
  - pessoas
  - pessoa_fisicas
  - pessoas_juridicas
---

# Diretivas
Neste namespace a tabela de segurança é utilizada para assegurar que um usuário somente acesse o sistema com permissão.
E está tabela descreve todos os dispositivos que o sistema tem cadastrado e o nível de acesso a esses dispositivos.

# Cadastro

Este módulo gerencia o cadastro das entidades no sistema. Uma pessoa é a principal entidade utilizada para identificar
funcionários, pessoas jurídicas (empresas), pessoas físicas.

Este módulo começa implementando o cadastro das pessoas que interage com o sistema como: pessoas físicas, pessoas jurídicas. A maioria das tabelas não tem em sua chave primaria o auto incremento e ao inserir alguma informação na tabela, utiliza a tabela auxiliar *cadastro.index*.
##### Tabela: index
| id  | id_pessoas | id_pessoas_fisicas | id_pessoas_juridicas | id_clientes | id_fabricantes | id_fornecedores | id_enderecos | id_contatos |
|:---:|:----------:|:------------------:|:--------------------:|:-----------:|:--------------:|:---------------:|:------------:|:-----------:|
|  1  |     2      |         1          |          1           |      0      |       1        |                 |              |             |

###### Comandos:
```Comandos:
-- object: cadastro.index | type: TABLE --
-- DROP TABLE IF EXISTS cadastro.index CASCADE;
CREATE TABLE cadastro.index (
id integer NOT NULL,
id_pessoas bigint DEFAULT 1,
id_pessoas_fisicas bigint DEFAULT 1,
id_pessoas_juridicas bigint DEFAULT 1,
id_clientes bigint DEFAULT 1,
id_fabricantes bigint DEFAULT 1,
id_fornecedores bigint DEFAULT 1,
id_enderecos bigint DEFAULT 1,
id_contatos bigint DEFAULT 1,
CONSTRAINT index_pkey PRIMARY KEY (id)
);
-- ddl-end --
ALTER TABLE cadastro.index OWNER TO administradores;
-- ddl-end --
```
Tanto um como o outro são identificados por um único ID.

##### Tabela: *cadastro.pessoas*

| id | nome |
| :--: | :--: |
| 1 | A.M.E. |
| 2 | Robson |
| 3 | Mirai |
###### Comandos:
```Comandos:
SET check_function_bodies = false;
-- ddl-end --

-- object: cadastro | type: SCHEMA --
-- DROP SCHEMA IF EXISTS cadastro CASCADE;
CREATE SCHEMA cadastro;
-- ddl-end --
ALTER SCHEMA cadastro OWNER TO administradores;
-- ddl-end --

-- object: cadastro.pessoas | type: TABLE --
-- DROP TABLE IF EXISTS cadastro.pessoas CASCADE;
CREATE TABLE cadastro.pessoas (
id bigint NOT NULL,
nome text NOT NULL,
CONSTRAINT pessoas_pkey PRIMARY KEY (id)
);
-- ddl-end --
ALTER TABLE cadastro.pessoas OWNER TO administradores;
-- ddl-end --
```

A classificação destas pessoas é feita por outra tabela.  
##### Tabela: *cadastro.pessoas_fisicas*

|  id  | id_pessoa |    sobrenome    |     cpf     |    rg     | data_emissao | id_cidade_nascimento | id_estado_nascimento | id_pais_nascimento | data_nascimento  |          pai          |               mae               |
|:----:|:---------:|:---------------:|:-----------:|:---------:|:------------:|:--------------------:|:--------------------:|:------------------:|:----------------:|:---------------------:|:-------------------------------:|
|  1   |     2     | Teodoro Calixto | 33726070826 | 343532074 |  04/08/1986  |          0           |          0           |         0          |    04/08/1986    | Edmo Teodoro da Silva | Terezinha Calixto da Cruz Silva |
###### Comandos:
```Comandos:
-- object: cadastro.pessoas_fisicas | type: TABLE --
-- DROP TABLE IF EXISTS cadastro.pessoas_fisicas CASCADE;
CREATE TABLE cadastro.pessoas_fisicas (
	id bigint NOT NULL,
	id_pessoa bigint NOT NULL,
	sobrenome text,
	cpf text NOT NULL,
	rg text NOT NULL,
	data_emissao date,
	id_cidade_nascimento integer,
	id_estado_nascimento integer,
	id_pais_nascimento integer,
	data_nascimento date,
	pai text,
	mae text,
	CONSTRAINT pessoas_fisicas_cpf_key UNIQUE (cpf),
	CONSTRAINT pessoas_fisicas_id_pessoa_key UNIQUE (id_pessoa),
	CONSTRAINT pessoas_fisicas_pkey PRIMARY KEY (id)
);
-- ddl-end --
ALTER TABLE cadastro.pessoas_fisicas OWNER TO administradores;
-- ddl-end --
```

##### Tabela: *cadastro.pessoas_juridicas*

| id | id_pessoa | razao_social | cnpj | ie | data_fundacao |
| :--: | :--: | :--: | :--: | :--: | :--: |
| 1 | 1 | A.M.E. Automação de Maquinas e Equipamentos LTDA. | 60579216000185 | 297005500110 | 01/01/1989 |
|  |  |  |  |  |  |
|  |  |  |  |  |  |
###### Comando:
```Comandos:
-- object: cadastro.pessoas_juridicas | type: TABLE --
-- DROP TABLE IF EXISTS cadastro.pessoas_juridicas CASCADE;
CREATE TABLE cadastro.pessoas_juridicas (
	id bigint NOT NULL,
	id_pessoa bigint NOT NULL,
	razao_social text,
	cnpj text NOT NULL,
	ie text,
	data_fundacao date,
	CONSTRAINT pessoas_juridicas_cnpj_key UNIQUE (cnpj),
	CONSTRAINT pessoas_juridicas_id_pessoa_key UNIQUE (id_pessoa),
	CONSTRAINT pessoas_juridicas_pkey PRIMARY KEY (id)
);
-- ddl-end --
ALTER TABLE cadastro.pessoas_juridicas OWNER TO administradores;
-- ddl-end --
```

A pessoa jurídica também é classificada por: fabricante, cliente, 
fornecedor.  

##### Tabela: *cadastro.fabricantes*

| id | id_pessoa | id_pessoa_juridica |
| :--: | :--: | :--: |
| 1 | 1 | 1 |
###### Comandos:
```Comandos:
-- object: cadastro.fabricantes | type: TABLE --
-- DROP TABLE IF EXISTS cadastro.fabricantes CASCADE;
CREATE TABLE cadastro.fabricantes (
	id bigint NOT NULL,
	id_pessoa bigint,
	id_pessoa_juridica bigint,
	CONSTRAINT fabricantes_id_pessoa_key UNIQUE (id_pessoa),
	CONSTRAINT fabricantes_pkey PRIMARY KEY (id)
);
-- ddl-end --
ALTER TABLE cadastro.fabricantes OWNER TO administradores;
-- ddl-end --
```

##### Tabela: *cadastro.cliente*

|  id  | id_pessoa | id_pessoa_juridica |
|:----:|:---------:|:------------------:|
|      |           |                    |
###### Comandos:
```Comandos:
-- object: cadastro.clientes | type: TABLE --
-- DROP TABLE IF EXISTS cadastro.clientes CASCADE;
CREATE TABLE cadastro.clientes (
	id bigint NOT NULL,
	id_pessoa bigint,
	id_pessoa_juridica bigint,
	CONSTRAINT clientes_id_pessoa_key UNIQUE (id_pessoa),
	CONSTRAINT clientes_pkey PRIMARY KEY (id)
);
-- ddl-end --
ALTER TABLE cadastro.clientes OWNER TO administradores;
-- ddl-end --
```

##### Tabela: *cadastro.tipos_fornecedores*

|  id  | descricao |
|:----:|:---------:|
|      |           |
###### Comandos:
```Comandos:
-- object: cadastro.tipos_fornecedores | type: TABLE --
-- DROP TABLE IF EXISTS cadastro.tipos_fornecedores CASCADE;
CREATE TABLE cadastro.tipos_fornecedores (
	id integer NOT NULL,
	descricao text NOT NULL,
	CONSTRAINT tipos_fornecedores_descricao_key UNIQUE (descricao),
	CONSTRAINT tipos_fornecedores_pkey PRIMARY KEY (id)
);
-- ddl-end --
ALTER TABLE cadastro.tipos_fornecedores OWNER TO administradores;
-- ddl-end --
```

##### Tabela: *cadastro.fornecedores*

|  id  | id_pessoa | id_pessoa_juridica | id_tipo_fornecedor |
|:----:|:---------:|:------------------:|:------------------:|
|      |           |                    |                    |
###### Comandos:
```Comandos:
-- object: cadastro.fornecedores | type: TABLE --
-- DROP TABLE IF EXISTS cadastro.fornecedores CASCADE;
CREATE TABLE cadastro.fornecedores (
	id bigint NOT NULL,
	id_pessoa bigint,
	id_pessoa_juridica bigint,
	id_tipo_fornecedor integer DEFAULT 1,
	CONSTRAINT fornecedores_id_pessoa_key UNIQUE (id_pessoa),
	CONSTRAINT fornecedores_pkey PRIMARY KEY (id)
);
-- ddl-end --
ALTER TABLE cadastro.fornecedores OWNER TO administradores;
-- ddl-end --
```
## Tabelas auxiliares do sistema

Este módulo também pode cadastrar outros objetos importantes para o sistema como planos de conta que servem para classificar e agrupar as contas dos possíveis fornecimentos e compras de materiais e serviços.

##### Tabela: *cadastro.planos_contas*
| id  |       nome        |
|:---:|:-----------------:|
|  1  |      Ativos       |
|  2  |     Passivos      |
|  3  |      Custos       |
|  4  |     Despesas      |
|  5  |     Receitas      |
|  6  |      Bancos       |
|  7  |       Fixos       |
|  8  | Salário produtivo |
|  9  |     Variáveis     |
| 10  |    Fabricação     |
| 11  |   Matéria Prima   |
| 12  |        Aço        |
###### Tabela auxiliar: *cadastro.planos_conta_ct*
| id | id_item | id_no | nivel |
| :--: | :--: | :--: | :--: |
| 1 | 1 | 1 | 0 |
| 2 | 2 | 2 | 0 |
| 3 | 3 | 3 | 0 |
| 4 | 4 | 4 | 0 |
| 5 | 5 | 5 | 0 |
| 6 | 6 | 6 | 0 |
| 7 | 6 | 1 | -1 |
| 8 | 7 | 7 | 0 |
| 9 | 7 | 3 | -1 |
| 10 | 8 | 8 | 0 |
| 11 | 8 | 7 | -1 |
| 12 | 8 | 3 | -2 |
|  |  |  |  |
###### Comandos:
```Comando:
CREATE TABLE cadastro.planos_contas (
    id BIGSERIAL PRIMARY KEY, 
    descricao TEXT NOT NULL
);

CREATE TABLE cadastro.planos_contas_ct (
    id BIGSERIAL PRIMARY KEY,
    id_item BIGINT REFERENCES cadastro.planos_conta(id) NOT NULL,
    id_no BIGINT REFERENCES cadastro.planos_conta(id) NOT NULL,
    nivel INTEGER DEFAULT 0
);
```
Comando para inserir um novo plano de conta.
```Comando
BEGIN; 
WITH item_inserido AS (
    INSERT INTO cadastro.planos_contas (descricao) VALUES (:descricao) RETURNING *
)
INSERT INTO cadastro.planos_contas_ct (id_item, id_no, nivel)
    ( SELECT ii.id, ii.id, 0 FROM item_inserido ii UNION ALL
        SELECT ii.id, lk.id_no, lk.nivel - 1 FROM item_inserido ii, cadastro.planos_contas_ct lk WHERE id_item = :idNo
    ) RETURNING *; 
COMMIT;
```
Comando para alterar um registro de plano de conta.
```Comando
BEGIN;
UPDATE cadastro.planos_contas pc SET descricao = :descricao WHERE id = :id;
COMMIT;
```
Comando para apagar um plano de conta e seus ramos.
```Comando
BEGIN;
WITH remover AS (
    SELECT * FROM cadastro.planos_contas_ct WHERE id_no = :idItem ORDER BY id_item, nivel
),
ct_deletados AS (
    DELETE FROM cadastro.planos_contas_ct ct USING remover r 
        WHERE ct.id_item = r.id_item RETURNING ct.id_item
),
deletados AS (
    DELETE FROM cadastro.planos_contas p USING ct_deletados d WHERE p.id = d.id_item RETURNING *
)
SELECT * FROM deletados;
COMMIT;
```
###### Plano de conta:
1. Ativo
    1. Bancos
2. Passivo
3. Custos
    1. Fixos 
       1. Salário produtivo.
    2. Variaveis
        1. Fabricação
            1. Matéria prima
               1. Aço.
               2. Não ferrosos.
            2. Insumo
               1. Elétrico.
               2. Mecânico.
               3. Eletro-mecânico.
               4. Pneumático.
               5. Eletro-pneumático.
               6. Comissão sobre vendas.
        3. Transporte
           1. Frete.
4. Despesas
    1. Fixas
        1. Administrativas
           1. Salário administrativo.
        2. Comerciais
           1. Salário comercial.
        3. Financeiras
           1. Salário financeiro.
        4. Conta
           1. Água e esgoto.
           2. Energia.
           3. Telefonia.
           4. Internet.
    2. Variaveis
       1. Sálario
       2. Imposto.
       3. Taxas bancárias.
5. Receitas
    1. Vendas
       1. Prestação de serviço.
       2. Fabricação.
       3. Sucata.
##### Tabela: cadastro.unidades_medidas
| id | descricao | abreviacao |  |
| :--: | :--: | :--: | ---- |
| 1 | Metro | m |  |
| 2 | Decímetro | dm |  |
| 3 | Centímetro | cm |  |
| 4 | Milímetro | mm |  |
| 5 | Micrômetro | µm |  |
| 6 | Nanômetro | nm |  |
| 7 | Litro | L |  |
| 8 | Mililitro | mL |  |
| 9 | Quilograma | kg |  |
| 10 | Grama | g |  |
| 11 | Miligrama | mg |  |
| 12 | Tonelada | t |  |
| 13 | Ano | a |  |
| 14 | Dia | d |  |
| 15 | Hora | h |  |
| 16 | Minuto | min |  |
| 17 | Segundo | s |  |
| 18 | Milissegundo | ms |  |
| 19 | Microssegundo | µs |  |
| 20 | Unidade | UN |  |
| 21 | Dezena | DZ |  |
| 22 | Cento | CT |  |
| 23 | Milhar | ML |  |
| 24 | Peça | PC |  |
###### Comandos:
```Comando
CREATE TABLE cadastro.unidades_medidas (
	id SERIAL PRIMARY KEY,
	descricao TEXT NOT NULL,
	abreviacao TEXT NOT NULL
);
```

Está tabela cadastra um padrão de medidas e abreviações utilizada pelo sistema.
###### Informações das medidas padrões no SI.
As medidas de quantidade e suas abreviações:
- Metro (m) - mede comprimentos, áreas e volumes.
- Decímetro (dm) - é um décimo de um metro, é uma unidade de comprimento.
- Centímetro (cm) - é um centésimo de um metro, é uma unidade de comprimento.
- Milímetro (mm) - é um milésimo de um metro, é uma unidade de comprimento.
- Micrômetro (µm) - é um milionésimo de um metro, é uma unidade de comprimento.
- Nanômetro (nm) - é um bilhão de vezes menor que um metro, é uma unidade de comprimento.
- Litro (L) - mede volume, equivalente a um decímetro cúbico (dm³).
- Decilitro (dL) - é um décimo de um litro.
- Centilitro (cL) - é um centésimo de um litro.
- Mililitro (mL) - é um milésimo de um litro.
- Microlitro (µL) - é um milionésimo de um litro.
- Nanolitro (nL) - é um bilhão de vezes menor que um litro.
- Mol (mol) - mede a quantidade de matéria, é a quantidade de entidades elementares (como átomos ou moléculas) em uma substância.

As medidas de peso e suas abreviações:
- Quilograma (kg) - é a unidade básica de massa no SI.
- Hectograma (hg) - é um centésimo de um quilograma.
- Decagrama (dag) - é um décimo de um quilograma.
- Grama (g) - é um milésimo de um quilograma.
- Decigrama (dg) - é um décimo de um grama.
- Centigrama (cg) - é um centésimo de um grama.
- Miligrama (mg) - é um milionésimo de um quilograma.
- Micrograma (µg) - é um milionésimo de um grama.
- Nanograma (ng) - é um bilhão de vezes menor que um grama.
- Tonelada (t) - é uma unidade de massa equivalente a 1000 kg.
- Tonelada de peso (t) - é uma unidade de massa equivalente a 907,185 kg.

As medidas de tempo:
- Século (c) - é cem anos.
- Década (da) - é dez anos.
- Ano (a) - é trezentos e sessenta e cinco dias (ou trezentos e sessenta e seis nos anos bissextos)
- Semana (week) - é sete dias.
- Dia (d) - é vinte e quatro horas.
- Hora (h) - é sessenta minutos.
- Minuto (min) - é sessenta segundos.
- Segundo (s) - é a unidade básica de tempo no SI.
- Milissegundo (ms) - é um milésimo de um segundo.
- Microssegundo (µs) - é um milionésimo de um segundo.
- Nanossegundo (ns) - é um bilhão de vezes menor que um segundo.
- Picossegundo (ps) - é um trilhão de vezes menor que um segundo.
- Femtossegundo (fs) - é um quadrilhão de vezes menor que um segundo.
- Attossegundo (as) - é um quintilhão de vezes menor que um segundo.

##### Tabela: cadastro.conversao_medidas
| id | descricao | unidade_1 | unidade_2 | fator |
| :--: | :--: | :--: | :--: | :--: |
| 1 | Milimetro | mm | m | 1000 |
| 2 | Metros | m | mm | 0.001 |
| 3 | Unidade | UN | CT | 100 |
| 4 | Unidade | UN | ML | 1000 |
| 5 | Centena | CT | UN | 0.01 |
| 6 | Centena | CT | ML | 10 |
| 7 | Milhar | ML | UN | 0.001 |
| 8 | Milhar | ML | CT | 0.1 |
| 9 | Grama | g | kg | 1000 |
| 10 | Kilograma | kg | g | 0.001 |
|  |  |  |  |  |
###### Comandos:
```Comando
CREATE TABLE cadastro.conversao_medidas (
	id BIGSERIAL PRIMARY KEY,
	descricao TEXT NOT NULL,
	unidade_1 INTEGER NOT NULL REFERENCES cadastro.unidades_medidas(id),
	unidade_2 INTEGER NOT NULL REFERENCES cadastro.unidades_medidas(id),
	fator NUMERIC(13, 8) DEFAULT 1.0
);
```
## Material
Um material é um insumo direto utilizado na construção do equipamento que pode ser instalado sem modificação ou precisar ser industrializado. Também pode ser uma ferramenta utilizada pelas maquinas na industrialização de uma matéria prima. 
Como um material pode ser estocado ?
- Uma matéria prima pode vir em uma variedade de formatos: barra chata, bloco, chapa, barra redonda, anel, etc e vários  estes formatos compartilham similaridades entre suas dimensões.
- O formato dita quantas dimensões existem para medir um certo material.
- Para estocar um certo material seu formato é importante e o que é fisicamente levado ao estoque. Um material de  alumínio está disponível em vários formatos. Por exemplo: Chapa de 12,7mm de expessura cortado em um quadrado de 1000mm, ou uma barra redonda de 3" ou 76,2mm por 6000mm de comprimento.
##### Tabela: cadastro.classificacoes_materiais
| id  |     descricao     | nomear |
|:---:|:-----------------:|:------:|
|49|Insumos|0
|50|Matéria Prima|0
|51|Fixador|0
|52|Parafuso|1
|53|Cabeça Cilindrica|1
|56|Material Eletrônico|0
|57|CLP|1
|58|Material Pneumático|0
|59|Atuador|1
|60|M6|1

###### Tabela auxiliar.
| id  | id_item | id_no | nivel |
|:---:|:-------:|:-----:|:-----:|
###### Comandos:
```Comando
CREATE TABLE cadastro.classificacoes_materiais (
	id BIGSERIAL PRIMARY KEY,
    descricao TEXT NOT NULL,
    nomear INT DEFAULT 1
);
    
CREATE TABLE cadastro.classificacoes_materiais_ct (
	id BIGSERIAL PRIMARY KEY,
	id_item BIGINT REFERENCES cadastro.classificacoes_materiais(id) NOT NULL,
	id_no BIGINT REFERENCES cadastro.classificacoes_materiais(id) NOT NULL,
	nivel INTEGER DEFAULT 0
);
```

##### Tabela: cadastro.formatos_materiais
| id | descricao | formula calculo peso |
| :--: | :--: | :--: |
| 1 | BARRA REDONDA | ((D1/2)\*(D1/2))\*PI\*D2\*PE |
| 2 | BARRA QUADRADA | (D1\*D1\*D2*PE) |
| 3 | BARRA SEXTAVADA | (D1\*D1\*3*PE)/3460 |
| 4 | BARRA CHATA | D1\*D2\*D3*PE |
| 5 | TUBO MECÂNICO | ((((D2/2)\*(D2/2)\*PI)-((D3/2)\*(D3/2)\*PI))\*D1\*PE)/4 |
| 6 | ANEL | ((((D2/2)\*(D2/2)\*PI)-(D3\*D3\*PI))\*D1\*PE)/4 |
| 7 | CHAPA | D1\*D2\*D3*PE |
| 8 | BLOCO | D1\*D2\*D3*PE |
###### Comandos:
```Comando
CREATE TABLE cadastro.formatos_materiais (
	id BIGSERIAL PRIMARY KEY,
    descricao TEXT NOT NULL,
    formula_calculo TEXT NOT NULL
);
```
##### Tabela: cadastro.tipos_materiais
| id  | descricao | peso especifico | [[Cadastro#Tabela Unidade de medidas.\|unidade_1]] | [[Cadastro#Tabela Unidade de medidas.\|unidade_2]] | plano de conta |
|:---:|:---------:|:---------------:|:---------:|:---------:|:--------------:|
|  1  | Aço Prata |      7850       |     6     |     1     |       36       |
|  2  | SAE-1020  |      7800       |     6     |     1     |       36       |
###### Comandos:
```Comando
CREATE TABLE cadastro.tipos_materiais (
	id BIGSERIAL PRIMARY KEY,
	descricao TEXT NOT NULL,
	peso_especifico NUMERIC(13, 8) NOT NULL,
	unidade_1 INTEGER NOT NULL REFERENCES cadastro.unidades_medidas(id),
	unidade_2 INTEGER NOT NULL REFERENCES cadastro.unidades_medidas(id),
	id_plano_conta BIGINT REFERENCES cadastro.planos_contas(id) NOT NULL
);
```
##### Tabela: cadastro.materiais
| id | descricao | codigo | [[Cadastro#Tabela cadastro.classificacoes_materiais\|id_classificacao_material]] | [[Cadastro#Tabela *cadastro.planos_contas*\|id_plano_conta]] |
| :--- | :--: | :--- | :--: | ---- |
| 1 | Disjuntor 10A Tripolar | DKP-10 | 56 | 11 |
| 2 | CLP Mitsubishi 16/16 | FX5UC | 57 | 11 |
| 3 | Atuador SMC Ø16 x 10mm | CDQ2A16-10DMZ | 59 | 11 |
|  |  |  |  |  |
Comando:
```Comando
CREATE TABLE cadastro.materiais (
	id BIGSERIAL PRIMARY KEY, 
	descricao TEXT NOT NULL, 
	codigo TEXT, 
	id_classificacao BIGINT REFERENCES cadastro.classificacoes_materiais(id)
);
```

###### Tabela Rascunho
| id  |         descricao         | unidade_estoque | unidade_comercial | id_classificacao_material | id_plano_conta |
|:---:|:-------------------------:|:---------------:|:-----------------:|:-------------------------:|:--------------:|
|  1  |   CLP Mitsubishi FX5UC    |       UN        |        UN         |                           |       38       |
|  2  | CABO MANGA 26 vias AWG-24 |        M        |         M         |                           |       38       |
|  3  |        ILIOS 0,5mm        |       UN        |        CT         |                           |       38       |
|  4  |    Barra Tarugo Ø50,8     |       MM        |        MM         |             2             |       38       |
```
CREATE TABLE cadastro.materiais (id BIGSERIAL PRIMARY KEY,
    descricao TEXT NOT NULL,
    unidade_estoque INTEGER NOT NULL REFERENCES cadastro.unidades_medidas(id),
    unidade_comercial INTEGER NOT NULL REFERENCES cadastro.unidades_medidas(id),
    id_classificacao_material BIGINT REFERENCES cadastro.classificacoes_materiais(id),
    id_plano_conta BIGINT REFERENCES cadastro.planos_contas(id) NOT NULL);
```