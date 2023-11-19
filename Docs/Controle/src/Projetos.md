# Projetos.
Setor responsável de criar soluções para produção automática sobre medida para
os clientes.

## Criação do projeto.
Todo o projeto é criado e idealizado em 3D, e após estar pronto para a
produção, um livro com todos os desenhos para criar o equipamento é impresso.
Para registrar um projeto, as seguintes informações precisam ser armazenadas.
 - Número do Projeto.
 - Nome do projeto.
 - Descrição breve.
 - Data criação.
 - Data final de entrega.
 - Data conclusão.

###### Tabela: Registros dos projetos.
| id  | numero_projeto | nome_projeto           | descricao                       | data_criacao | data_entrega | data_conclusao |
|:---:|:---------------|:-----------------------|:--------------------------------|:-------------|:-------------|----------------|
|  1  | 5304           | 5304-Máquina de bebida | Montagem de uma tampa de bebida | 19/08/2023   | 12/11/2023   |                |
Comando:
```
CREATE TABLE producao.projetos (id BIGINT PRIMARY KEY, 
                                numero_projeto TEXT NOT NULL, 
                                nome TEXT NOT NULL, 
                                descricao TEXT, 
                                data_criacao DATE CURRENT_TIMESTAMP, 
                                data_entrega DATE, 
                                data_conclusao DATE);

ALTER TABLE producao.index ADD COLUMN id_projetos BIGINT DEFAULT 1;

with inserido AS (INSERT INTO producao.projetos (id, numero_projeto, nome) 
values ((SELECT id_projetos FROM producao.index) + 1, 
'5304-00', '5304-Tampa Babidas 5x1') returning *) update producao.index set id_projetos = inserido.id from inserido;

```
### Descritor de um projeto.
Os itens de um projeto, como desenhos, peças são descritos de partes.
Uma parte identifica um item do projeto.
Um item também pode ser formado por outros itens, um conjunto; logo 
essa parte terá uma propriedade de hierarquia.
A parte pode ter itens na lista de materiais para a descrever.
 - Identificação do projeto do qual pertence está parte.
 - Numero da parte.
 - Descrição da parte.
 - Quantidade.
 - Posição.
 - Dimensão acabada.
 - Dimensão bruta.
 - Observação. Caso tenha algum tratamento ou modificação a fazer.
 - 
###### Tabela: registros das partes.
| id  | id_projeto | numero_parte | descricao                        | posicao | quantidade | dimensao_acabada | dimensao_bruta | observacao |
|:---:|:-----------|:-------------|:---------------------------------|:--------|:-----------|:-----------------|:---------------|:----------:|
|  1  | 1          | 5304-12-00   | 5304-12-Carrossel Entr. Vertedor | 1       | 1          |                  |                |            |
Comando:
```
CREATE TABLE producao.partes_projetos (id BIGINT PRIMARY KEY,
                                       id_projeto BIGINT REFERENCES producao.projetos(id),
                                       numero_parte TEXT NOT NULL,
                                       descricao TEXT,
                                       posicao TEXT,
                                       quantidade INTEGER NOT NULL,
                                       dimensao_acabada TEXT,
                                       dimensao_bruta TEXT
                                       observacao TEXT);

alter table producao.index add column id_partes_projetos bigint default 1;

CREATE TABLE producao.partes_projetos_ct (id BIGSERIAL PRIMARY KEY,
                                          id_item BIGINT REFERENCES producao.partes_projetos(id) NOT NULL,
                                          id_no BIGINT REFERENCES producao.partes_projetos(id) NOT NULL,
                                          nivel INTEGER DEFAULT 0);

WITH ii0 AS (INSERT INTO producao.partes_projetos (id, id_projeto, numero_parte) VALUES ((SELECT id_partes_projetos FROM producao.index) + 1, 2, '5304-01-01') RETURNING id), ii1 AS (INSERT INTO producao.partes_projetos_ct (id_item, id_no, nivel) (SELECT ii0.id, ii0.id, 0 FROM ii0 UNION ALL SELECT ii0.id, id_no, nivel - 1 FROM producao.partes_projetos_ct, ii0 WHERE id_item = 0) RETURNING *) UPDATE producao.index SET id_partes_projetos = ii0.id FROM ii0;

```
Comando para inserir um novo registro onde $id_no = 0, adiciona o registro na raiz.
```
ROLLBACK; BEGIN; WITH reg_inserido AS ( INSERT INTO producao.partes_projetos (id, id_projeto, numero_parte, quantidade) VALUES ((SELECT id_partes_projetos FROM producao.index)+1, 2, '5304-10-00', 1) RETURNING * ), reg_ct AS (INSERT INTO producao.partes_projetos_ct (id_item, id_no, nivel) (SELECT reg_inserido.id, reg_inserido.id, 0 FROM reg_inserido) UNION ALL SELECT reg_inserido.id, id_no, nivel - 1 FROM producao.partes_projetos_ct, reg_inserido WHERE id_item = 0 RETURNING *), id_at AS (UPDATE producao.index SET id_partes_projetos = reg_inserido.id FROM reg_inserido) SELECT * FROM reg_ct;
```
### Lista de materiais.
Está lista é utilizada para descrever uma parte do projeto ou um
necessidade de material solicitado avulso.
Cada registro desta lista identifica um material que compõe uma parte.
Por exemplo um eixo flangeado de um rotativo utilizado para girar
o disco centrifugo interligando-o ao moto-redutor do conjunto. O eixo
flangeado é formado por dois componentes, um eixo e um disco.
Nesta lista um peçado de eixo deve ser cortado e um disco deve ser
cortado. 
Está lista, poderá formar uma nova lista de compra de materiais lincando está 
parte aos itens de compra.

###### Tabela: Lista de materiais.
| id  | id_parte | id_material | quantidade | id_tipo_material | id_formato_material | d1   | d2   | d3  | d4  | d5  | peso  | data |
|:----|:--------:|:------------|:-----------|:-----------------|:--------------------|:-----|:-----|:----|:----|:----|:------|:----:|
| 1   |    1     |             | 1          | 2                | 1                   | 38,1 | 148  |     |     |     | 2,35  |      |
| 2   |    1     |             | 1          | 1                | 1                   | 308  | 12,7 |     |     |     | 2,35  |      |
| 3   |          | 2           | 4          | 2                | 1                   | 100  | 208  |     |     |     | 2,35  |      |
```
CREATE TABLE producao.lista_materiais (id BIGINT PRIMARY KEY, 
                                id_parte BIGINT NULL REFERENCES producao.partes_projetos(id),  
                                id_material BIGINT NULL REFERENCES cadastro.materiais(id), 
                                quantidade NUMERIC(13,8) NOT NULL DEFAULT 1.0, 
                                id_tipo_material BIGINT NOT NULL REFERENCES  cadastro.tipos_materiais(id), 
                                id_formato_material BIGINT NOT NULL REFERENCES  cadastro.formatos_materiais(id), 
                                d1 NUMERIC(13,8) DEFAULT 0.0,
                                d2 NUMERIC(13,8) DEFAULT 0.0,
                                d3 NUMERIC(13,8) DEFAULT 0.0,
                                d4 NUMERIC(13,8) DEFAULT 0.0,
                                d5 NUMERIC(13,8) DEFAULT 0.0,
                                peso NUMERIC(13,8) DEFAULT 0.0,
                                data DATE NOT NULL DEFAULT CURRENT_TIMESTAMP);

alter table producao.index add column id_lista_materiais bigint default 1;
```
###### 