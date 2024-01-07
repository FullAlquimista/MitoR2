---
tags:
  - projeto
  - tabelas
  - projetos
  - partes_projetos
  - lista_materiais
---
# Projetos.
Setor responsável de criar soluções para produção automática sobre medida para os clientes.
## Criação do projeto.
Todo o projeto é criado e idealizado em 3D, e após estar pronto para a produção, um livro com todos os desenhos para  criar o equipamento é impresso. Para registrar um projeto, as seguintes informações precisam ser armazenadas.
 - Número do Projeto.
 - Nome do projeto.
 - Descrição breve.
 - Data criação.
 - Data final de entrega.
 - Data conclusão.
 - ID do usuário que criou o registro.
##### Tabela: producao.projetos
| id | numero_projeto | nome_projeto | descricao | data_criacao | data_entrega | data_conclusao | oid_usuario |
| :--: | :--- | :--- | :--- | :--- | :--- | ---- | :--: |
| 1 | 5304 | 5304-Máquina de bebida | Montagem de uma tampa de bebida | 19/08/2023 | 12/11/2023 |  |  |
| 2 | 7202 | 7202-Flip Top Frenzy Cap 35 | Montagem da tampa cap. Ø35 | 31/12/2023 | 01/05/2023 |  |  |
###### Comandos:
```Comando
CREATE TABLE producao.projetos (id BIGINT PRIMARY KEY, 
  numero_projeto TEXT NOT NULL, 
  nome TEXT NOT NULL, 
  descricao TEXT, 
  data_criacao DATE CURRENT_TIMESTAMP, 
  data_entrega DATE, 
  data_conclusao DATE
  oid_usuario BIGINT NOT NULL);

ALTER TABLE producao.index ADD COLUMN id_projetos BIGINT DEFAULT 1;

with inserido AS (INSERT INTO producao.projetos (id, numero_projeto, nome) 
values ((SELECT id_projetos FROM producao.index) + 1, 
'5304-00', '5304-Tampa Babidas 5x1') returning *) update producao.index set id_projetos = inserido.id from inserido;

```
### Descritor de um projeto.
Os itens de um projeto, como desenhos, peças são descritos de partes. Uma parte identifica um item do projeto. Um item também pode ser formado por outros itens, um conjunto; logo essa parte terá uma propriedade de hierarquia.
 - Identificação do projeto do qual pertence está parte.
 - Quantidade.
 - Numero da parte.
 - Descrição da parte.
 - Descrição da parte 2.
 - Fornecedor.
 - Material.
 - Peso kg.
 - Dimensão acabada.
 - Dimensão bruta.
 - Posição.
 - Observação. Caso tenha algum tratamento ou modificação a fazer.
 - Data da criação do registro.
 - ID do usuário que criou o registro.
###### Tabela: registros das partes.
| id | [[Projetos#Tabela producao.projetos\|id_projeto]] | quantidade | numero_parte | descricao | descricao2 | fornecedor | material | peso | dimensao_acabada | dimensao_bruta | posicao | observacao | data | oid_usuario |
| :--: | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--: | :--: | :--: |
| 1 | 1 | 1 | 5304-12-00 | 5304-12-Carrossel Entr. Vertedor |  |  |  |  |  |  | 1 |  |  |  |
| 2 | 2 | 1 | 7202-01-01 | Estrutura Principal | Disp. 01-Estrutura Principal | Mirai | Sae-1020 | 400,5 | 1292x1872,8x2160mm |  |  |  | 31/12/2023 |  |
| 3 | 2 | 6 | 7202-01-02 | Base de Fixação | Disp. 01-Estrutura Principal | Mirai | Sae-1020 | 0,61 | 12,7x80x80mm | 12,7x84x84mm |  |  | 31/12/2023 |  |
| 4 | 2 | 2 | 7202-01-03 | Teto inferior | Disp. 01-Estrutura Principal | Mirai | Sae-1020 | 26,91 | #2,5x1074x1280mm | #2,5x1078x1284mm |  |  |  |  |
| 5 | 2 | 1 | 7202-Material Pneumático | SMC |  | SMC |  |  |  |  |  |  | 31/12/2023 |  |
| 6 | 2 | 2 | Atuador SMC CDQ2A16-XXDMZ Compacto Simples | Atuador SMC Ø16x10mm | Mod. CDQ2A16-10DMZ | SMC | Alumínio | 0,07 | Compacto Simples |  |  |  | 31/12/2023 |  |
###### Tabela: Auxiliar das partes.
| id | id_item | id_no | nivel |
| ---- | ---- | ---- | ---- |
| 1 | 2 | 2 | 0 |
| 2 | 3 | 3 | 0 |
| 3 | 3 | 2 | -1 |
| 4 | 4 | 4 | 0 |
| 5 | 4 | 2 | -1 |
| 6 | 5 | 5 | 0 |
| 7 | 6 | 6 | 0 |
| 8 | 6 | 5 | -1 |
###### Comandos:
```Comando
CREATE TABLE producao.partes_projetos (id BIGINT PRIMARY KEY,
                                       id_projeto BIGINT REFERENCES producao.projetos(id),
                                       quantidade INTEGER NOT NULL,
                                       numero_parte TEXT NOT NULL,
                                       descricao TEXT,
                                       descricao2 TEXT,
                                       fornecedor TEXT,
                                       material TEXT,
                                       peso NUMERIC(13,8) DEFAULT 0.0,
                                       dimensao_acabada TEXT,
                                       dimensao_bruta TEXT,
                                       posicao TEXT,
                                       observacao TEXT,
                                       data DATE NOT NULL DEFAULT CURRENT_TIMESTAMP,
                                       oid_usuario BIGINT);

alter table producao.index add column id_partes_projetos bigint default 1;

CREATE TABLE producao.partes_projetos_ct (id BIGSERIAL PRIMARY KEY,
                                          id_item BIGINT REFERENCES producao.partes_projetos(id) NOT NULL,
                                          id_no BIGINT REFERENCES producao.partes_projetos(id) NOT NULL,
                                          nivel INTEGER DEFAULT 0);
```

```
WITH ii0 AS (INSERT INTO producao.partes_projetos (id, id_projeto, numero_parte) VALUES ((SELECT id_partes_projetos FROM producao.index) + 1, 2, '5304-01-01') RETURNING id), ii1 AS (INSERT INTO producao.partes_projetos_ct (id_item, id_no, nivel) (SELECT ii0.id, ii0.id, 0 FROM ii0 UNION ALL SELECT ii0.id, id_no, nivel - 1 FROM producao.partes_projetos_ct, ii0 WHERE id_item = 0) RETURNING *) UPDATE producao.index SET id_partes_projetos = ii0.id FROM ii0;

```
Comando para inserir um novo registro onde $id_no = 0, adiciona o registro na raiz.
```
ROLLBACK; BEGIN; WITH reg_inserido AS ( INSERT INTO producao.partes_projetos (id, id_projeto, numero_parte, quantidade) VALUES ((SELECT id_partes_projetos FROM producao.index)+1, 2, '5304-10-00', 1) RETURNING * ), reg_ct AS (INSERT INTO producao.partes_projetos_ct (id_item, id_no, nivel) (SELECT reg_inserido.id, reg_inserido.id, 0 FROM reg_inserido) UNION ALL SELECT reg_inserido.id, id_no, nivel - 1 FROM producao.partes_projetos_ct, reg_inserido WHERE id_item = 0 RETURNING *), id_at AS (UPDATE producao.index SET id_partes_projetos = reg_inserido.id FROM reg_inserido) SELECT * FROM reg_ct;
```
### Lista de materiais.
Está lista é utilizada para descrever uma parte do projeto ou uma necessidade de material solicitado avulso. Cada registro desta lista identifica um material que compõe uma parte. Por exemplo um eixo flangeado de um rotativo utilizado para girar o disco centrifugo interligando-o ao moto-redutor do conjunto. O eixo flangeado é formado por dois componentes, um eixo e um disco. Nesta lista um pedaço de eixo deve ser cortado e um disco deve ser cortado. 
###### Tabela: producao.lista_materiais
| id | [[Projetos#Tabela registros das partes.\|id_parte]] | [[Compras#Tabela compras.solicitacoes_materiais\|id_solicitacao]] | [[Cadastro#Tabela cadastro.materiais\|id_material]] | quantidade | [[Cadastro#Tabela cadastro.unidades_medidas\|id_unidade_quantidade]] | [[Cadastro#Tabela cadastro.tipos_materiais\|id_tipo_material]] | [[Cadastro#Tabela cadastro.formatos_materiais\|id_formato_material]] | d1 | d2 | d3 | d4 | d5 | [[Cadastro#Tabela cadastro.unidades_medidas\|id_unidade_dimensoes]] | peso | [[Cadastro#Tabela cadastro.unidades_medidas\|id_unidade_peso]] | data | oid_usuario |
| :--- | :--: | :--: | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--: | :--- | :--: |
| 1 | 1 |  |  | 1 | 24 | 2 | 1 | 38,1 | 148 |  |  |  | 4 | 1 |  |  |  |
| 2 | 1 |  |  | 1 | 24 | 1 | 1 | 308 | 12,7 |  |  |  | 4 | 1 |  |  |  |
| 3 |  | 1 | 2 | 4 | 24 | 2 | 4 | 100 | 208 |  |  |  | 4 | 1 |  |  |  |
| 4 | 3 |  |  | 6 | 20 | 2 | 8 | 12,7 | 84 | 84 |  |  | 4 | 0,61 | 9 | 31/12/2023 |  |
| 5 | 4 |  |  | 2 | 20 | 2 | 7 | 2,5 | 1074 | 1280 |  |  | 4 | 26,91 | 9 | 31/12/2023 |  |
| 6 | 5 |  | 3 | 2 | 20 |  |  |  |  |  |  |  |  | 0,07 | 9 | 31/12/2023 |  |
###### Comandos:
```
CREATE TABLE producao.lista_materiais (id BIGINT PRIMARY KEY, 
  id_parte BIGINT REFERENCES producao.partes_projetos(id), 
  id_solicitacao BIGINT REFERENCES compras.solicitacao_materiais(id), 
  id_material BIGINT REFERENCES cadastro.materiais(id), 
  quantidade NUMERIC(13,8) NOT NULL DEFAULT 1.0, 
  id_unidade_quantidade INT NOT NULL REFERENCES cadastro.unidades_materiais(id), 
  id_tipo_material BIGINT REFERENCES cadastro.tipos_materiais(id), 
  id_formato_material BIGINT REFERENCES cadastro.formatos_materiais(id), 
  d1 NUMERIC(13,8) DEFAULT 0.0, 
  d2 NUMERIC(13,8) DEFAULT 0.0, 
  d3 NUMERIC(13,8) DEFAULT 0.0, 
  d4 NUMERIC(13,8) DEFAULT 0.0, 
  d5 NUMERIC(13,8) DEFAULT 0.0, 
  id_unidade_dimensoes INT NOT NULL REFERENCES cadastro.unidades_materiais(id), 
  peso NUMERIC(13,8) DEFAULT 0.0, 
  id_unidade_peso INT NOT NULL REFERENCES cadastro.unidades_materiais(id), 
  data DATE NOT NULL DEFAULT CURRENT_TIMESTAMP
  oid_usuario BIGINT NOT NULL);

alter table producao.index add column id_lista_materiais bigint default 1;
```
