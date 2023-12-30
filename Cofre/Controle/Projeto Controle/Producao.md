---
tags:
  - orcamentos
  - anexos
  - propostas
  - itens_propostas
  - propostas_aprovadas
---
# Produção
Producao é o módulo que implementa as funcionalidades para os setores: orçamentos, projetos, serviços (manufatura).
### Idéias e anotações...
* O orçamento pode ter uma foto junto com a descrição do produto para posteriormente saber o que foi orçado. Hoje os orçamentos estão saindo com os detalhes e fotos. E para saber estes detalhes utiliza-se arquivos criados manualmente via Excel.
* A proposta também contém itens que enumeram o que está sendo proposto
  com detalhes dos cálculos e valores.
* Pode haver um pré projeto da idéia para o produto e forma de construção
  do equipamento.
* Quando uma peça do projeto fica pronta, seu desenho é impresso.
  No serviço de manufatura, a matéria prima desta peça é comprada e suas
  medidas são obtidas pelo desenho.
* Materiais, componentes, partes, etc...  
  Composição do material: 1020, 1045, VND, VC 131, etc.  
  Formato: chapa, barra chata, barra redonda, anel, metalon, cantoneira, 
tubo mecânico, etc.  
  Grandezas:
1. A x L x C -- Altura Largura Comprimento.
2. D x C -- Diâmetro Comprimento.
3. De x Di x C -- Diâmetro interno Diâmetro externo Comprimento.

# Termos e significados.
- Matéria-prima: são elementos, materiais naturais e semi-processados utilizados
na contrução de um bem e serviço e é uma categoria de insumo.
- Insumo: é um termo amplo que engloba todos os recursos utilizados no meio de produção. 
Ele pode ser dividido em insumo direto como matéria-prima, um equipamento eletrônico 
como CLP e outros que são utilizados diretamente no processo de produção
de outros bens e serviços. Já o insumo indireto é considerado todo recurso
utilizado indiretamenta na produção de bens e serviços como:
energia elétrica, trabalhadores, equipamentos de usinagem, etc.

## Orçamento
Este é o principal setor da empresa, encarregado de emitir um orçamento
de um máquina que poderá desencadear todos demais processos deste sistema.
Este setor prevê um valor para o produto final ou serviço como um equipamento, 
que contém todo o insumo necessário.
Pode ser gerado três tipos orçamentos: de prestação de serviço, de fabricação e
de industrialização (não usado).
###### Formulários e tabelas.
```
CREATE SCHEMA producao AUTHORIZATION administrador;
REVOKE CREATE ON SCHEMA producao FROM public;
REVOKE USAGE ON SCHEMA producao FROM public;
GRANT USAGE ON SCHEMA producao TO usuario;
```
###### Tabela: producao.tipos_propostas
Está tabela contém os registros tipos orçamentos que podem ser
gerados: Prestação de serviço, Fabricação, Industrialização e Consultoria.

```Comando
CREATE TABLE producao.tipos_propostas (
	id SERIAL PRIMARY KEY, 
	descricao TEXT NOT NULL
);
```
### Um orçamento
Os campos fabricante e cliente são unicos ao orçamento, assim também:
título, data do orçamento e recursos.
#### Recursos do orçamento
Armazena um registro que contém os recursos para determinar um orçamento. Por exemplo: a imagem do produto, o arquivo PDF do desenho com as dimensões do produto e outros anexos. Está informação será armazenada em uma tabela com um id, detalhe do recurso, em JSON, usando o tipo 'jsonb' e uma coluna com o recurso salvo no tipo array
binário bytea.
```
```
###### Tabela: producao.orcamentos
Descreve um orçamento.
```
CREATE TABLE producao.index (id INT PRIMARY KEY);

CREATE TABLE producao.recursos (id BIGSERIAL PRIMARY KEY, detalhe jsonb, recurso bytea);
CREATE INDEX producao_recursos_idx ON producao.recursos USING gin (detalhe jsonb_path_ops);

CREATE TABLE producao.orcamentos (id BIGINT PRIMARY KEY,
        id_fabricante BIGINT REFERENCES cadastro.fabricantes(id) NOT NULL,
        id_cliente BIGINT REFERENCES cadastro.clientes(id) NOT NULL,
        titulo TEXT NOT NULL,
        data DATE);

ALTER TABLE producao.index ADD COLUMN id_orcamentos BIGINT DEFAULT 1;
```
###### Tabela auxiliar: producao.anexos
Está tabela linca um recurso a um orçamento como arquivos.
```
CREATE TABLE producao.anexos (id BIGSERIAL PRIMARY KEY,
        id_orcamento BIGINT REFERENCES producao.orcamentos(id) NOT NULL,
        id_recurso BIGINT REFERENCES producao.recursos(id) NOT NULL);
```

### Uma proposta
Contém seu número, o número do orçamento referenciado,
uma descrição breve do que está sendo orçado, os itens, o valor, prazo de entrega,
produção horária, data da proposta e o número do pedido.
Um orçamento é aprovado quando uma das propostas é aceita pelo cliente
e um pedido do cliente é emitido.


###### Tabela: producao.propostas
Uma proposta contém o id da proposta, o id do orçamento referenciado,
uma descrição breve do que está sendo orçado, o valor, prazo de entrega,
produção horária e data da proposta.
```
CREATE TABLE producao.propostas (id BIGINT PRIMARY KEY,
        id_orcamento BIGINT REFERENCES producao.orcamentos(id) NOT NULL,
        id_tipo_proposta INT REFERENCES producao.tipos_propostas(id) NOT NULL,
        numero_orcamento TEXT UNIQUE,
        descricao TEXT,
        data_proposta DATE,
        valor_total NUMERIC(13,8),
        prazo_entrega INT,
        producao_horaria INT,
        aprovado INT);

ALTER TABLE producao.index ADD COLUMN id_propostas BIGINT DEFAULT 1;

// ALTER TABLE producao.orcamentos ADD CONSTRAINT fk_proposta_aprovada FOREIGN KEY(id_proposta_aprovada) REFERENCES producao.propostas(id);
```
###### Tabela auxiliar: producao.itens_propostas
Está tabela contém os itens de uma determinada proposta. Formado
por um id do item, o id da proposta referente, descricao item, valor
do item.
```
CREATE TABLE producao.itens_propostas (id BIGSERIAL PRIMARY KEY,
        id_proposta BIGINT REFERENCES producao.propostas(id) NOT NULL,
        descricao TEXT,
        valor NUMERIC(13,8));
```
###### Tabela auxiliar: producao.propostas_aprovadas
Está tabela aprova as propostas de um orçamento.
```
CREATE TABLE producao.propostas_aprovadas (id BIGSERIAL PRIMARY KEY,
        id_orcamento BIGINT REFERENCES producao.orcamentos(id) NOT NULL,
        id_proposta BIGINT REFERENCES producao.propostas(id) NOT NULL UNIQUE,
        data_aprovacao DATE,
        numero_pedido TEXT);
```

## Projeto
Um projeto pode ser criado através da aprovação da proposta de um orçamento 
por um pedido e também pode ser criado de maneira isolada e posteriormente
lincado a um orçamento. Este descreve na maior parte todos os insumos diretos
que formam o equipamento.

Um projeto contém o número que pode referenciar um orçamento,
o nome da máquina que se inicia pelo número da máquina e normalmente 
o nome do produto da máquina que fará uma industrialização ex: 
1650-Flip-Top D50, data da criação do projeto,
data de aprovação e data da conclusão.

###### Tabela: Projetos
| id  | id_orcamento |      nome_maquina       | data_projeto | data_aprovacao | data_conclusao |
|:---:|:------------:|:-----------------------:|:------------:|:--------------:|:--------------:|
|  1  |              | 1932-Corte Selo Servo 6 |  01/09/2022  |   30/09/2022   |   30/03/2022   |
```
CREATE TABLE producao.projetos (id BIGINT PRIMARY KEY,
        id_orcamento BIGINT REFERENCES producao.orcamentos(id) DEFAULT NULL,
        nome_maquina TEXT NOT NULL,
        data_criacao DATE NOT NULL,
        data_aprovacao DATE,
        data_conclusao DATE);

ALTER TABLE producao.index ADD COLUMN id_projetos BIGINT DEFAULT 1;
```

Ao projetar um equipamento, várias partes são desenhadas e incluídas na montagem
do equipamento. Cada parte é formada por listas de materiais e consequentemente
pode gerar serviços como: compras, usinagens, tratamentos, montagem, etc.

###### Tabela: Partes
| id  | id_projeto | quantidade |      numero_peca       |  descricao   | posicao |  peso  |
|:---:|:----------:|:----------:|:----------------------:|:------------:|:-------:|:------:|
|  1  |     1      |     1      | 1932-12-Base principal |              |   5.1   | 234.41 |
|  2  |     1      |     1      |       1932-12-01       | Guia da mesa |  5.1.1  |  9.98  |
```
CREATE TABLE producao.partes_projetos (id BIGINT PRIMARY KEY,
        id_projeto BIGINT REFERENCES producao.projetos(id) NOT NULL,
        quantidade INT DEFAULT 1,
        numero_peca TEXT NOT NULL,
        descricao TEXT,
        posicao TEXT,
        peso NUMERIC(13,8));

ALTER TABLE producao.index ADD COLUMN id_partes_projetos BIGINT DEFAULT 1;
```
###### Tabela: Auxiliar Closure Table
| id  | id_item | id_no | nivel |
|:---:|:-------:|:-----:|:-----:|
|  1  |    1    |   1   |   0   |
|  2  |    2    |   2   |   0   |
|  3  |    2    |   1   |  -1   |
```
CREATE TABLE producao.partes_projetos_ct (id BIGSERIAL PRIMARY KEY,
    id_item BIGINT REFERENCES producao.partes_projetos(id) NOT NULL,
    id_no BIGINT REFERENCES producao.partes_projetos(id) NOT NULL,
    nivel INT default 0);
```
### Caracteristicas de uma parte:
1. Uma parte é formada por listas de materiais.
Estas listas são:
   1. Lista de materiais:
   - matéria-prima em barras ou chapas grandes.
   - componentes mecânicos
   - elétro-eletrônicos
   - pneumáticos,
   - etc.
   2. Lista de materiais fracionados nas grandezas:
    - A|E X L X C X D4 X D5. 
2. Todos os itens da lista de material não fracionado precisa ser
  cadastrada.
3. Lista de materiais - É formado por uma identificação do material, a descrição do material, 
   valor da grandeza, classificação, plano de contas.
   - O valor da grandeza é utilizada para gerar um fator unitário obtido ao multiplicar
     a quantidade de unidade de um determinado material de uma cotação pelo fator da grandeza.
     Se este fator for multiplicado pelo valor do material obtém-se uma estimativa de quanto
     custaria o material na hora da cotação. 
   - A classificação dos materiais é utilizada na hora de encontrar e pode também ser utilizado
     na hora de descrever um novo material.
   1. Matéria Prima
      1. Barra Chata
      2. Barra Redonda
   2. Fixadores
      1. Parafusos
         1. Cabeça Cilindrica
            1. M6 x 10mm
         2. Cabeça Chata
            1. M6 x 16mm
         3. Cabeça Sextavada
            1. M10 x 25mm
   
     ex: Barra Redonda SAE-1020 Ø10x6000 - 125,00 - 15KG - 6000



###### Tabela classificacoes de materiais
| id  |     descricao     | nomear |
|:---:|:-----------------:|:------:|
|  1  |   Matéria Prima   |   0    |
|  2  |    Barra Chata    |   1    |
|  3  |   Barra Redonda   |   1    |
|  4  |      Fixador      |   0    |
|  5  |     Parafuso      |   1    |
|  6  | Cabeça Cilindrica |   1    |
|  7  |     M6 x 10mm     |   1    |
|  8  |   Cabeça Chata    |   1    |
|  9  |     M6 x 16mm     |   1    |
| 10  | Cabeça Sextavada  |   1    |
| 11  |    M10 x 25mm     |   1    |
```
CREATE TABLE cadastro.classificacoes_materiais (id BIGSERIAL PRIMARY KEY,
    descricao TEXT NOT NULL,
    nomear INT DEFAULT 1);
```
###### Tabela auxiliar classificação material closure table
| id  | id_item | id_no | nivel |
|:---:|:-------:|:-----:|:-----:|
```
CREATE TABLE cadastro.classificacoes_materiais_ct (id BIGSERIAL PRIMARY KEY,
    id_item BIGINT REFERENCES cadastro.classificacoes_materiais(id) NOT NULL,
    id_no BIGINT REFERENCES cadastro.classificacoes_materiais(id) NOT NULL,
    nivel INT default 0);
```
###### Tabela de material
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
###### Tabela do formato de materiais
| id  |    descricao    |                  formula calculo peso                   |
|:---:|:---------------:|:-------------------------------------------------------:|
|  1  |  BARRA REDONDA  |              ((D1/2)\*(D1/2))\*PI\*D2\*PE               |
|  2  | BARRA QUADRADA  |                      D1\*D1\*D2*PE                      |
|  3  | BARRA SEXTAVADA |                   (D1\*D1\*3*PE)/3460                   |
|  4  |   BARRA CHATA   |                      D1\*D2\*D3*PE                      |
|  5  |  TUBO MECÂNICO  | ((((D2/2)\*(D2/2)\*PI)-((D3/2)\*(D3/2)\*PI))\*D1\*PE)/4 |
|  6  |      ANEL       |     ((((D2/2)\*(D2/2)\*PI)-(D3\*D3\*PI))\*D1\*PE)/4     |
|  7  |      CHAPA      |                      D1\*D2\*D3*PE                      |
```
CREATE TABLE cadastro.formatos_materiais (id BIGSERIAL PRIMARY KEY,
    descricao TEXT NOT NULL,
    formula_calculo TEXT NOT NULL);
```
###### Tabela de tipo do material
| id  | descricao | peso especifico | unidade 1 | unidade 2 | plano de conta |
|:---:|:---------:|:---------------:|:---------:|:---------:|:--------------:|
|  1  | Aço Prata |      7850       |    KG     |     M     |       36       |
|  2  | SAE-1020  |      7800       |    KG     |     M     |       36       |
```
CREATE TABLE cadastro.tipos_materiais (id BIGSERIAL PRIMARY KEY,
        descricao TEXT NOT NULL,
        peso_especifico NUMERIC(13, 8) NOT NULL,
        unidade_1 INTEGER NOT NULL REFERENCES cadastro.unidades_medidas(id),
        unidade_2 INTEGER NOT NULL REFERENCES cadastro.unidades_medidas(id),
        id_plano_conta BIGINT REFERENCES cadastro.planos_contas(id) NOT NULL);
```
###### Tabela de material fracionavel
| id  | id_material | id_tipo_material | id_formato_material |  D1  |  D2  | D3  | D4  | D5  | unidade_peso |
|:---:|:-----------:|:----------------:|:-------------------:|:----:|:----:|:---:|:---:|:---:|:------------:|
|  1  |      4      |        2         |          1          | 50,8 | 6000 |     |     |     |      KG      |
```
CREATE TABLE cadastro.materiais_fracionaveis (id BIGSERIAL PRIMARY KEY,
    id_material BIGINT REFERENCES cadastro.materiais(id) UNIQUE NOT NULL,
    id_tipo_material BIGINT REFERENCES cadastro.tipos_materiais(id) NOT NULL,
    id_formato_material BIGINT REFERENCES cadastro.formatos_materiais(id) NOT NULL,
    D1 NUMERIC(13,8) DEFAULT 0.0,
    D2 NUMERIC(13,8) DEFAULT 0.0,
    D3 NUMERIC(13,8) DEFAULT 0.0,
    D4 NUMERIC(13,8) DEFAULT 0.0,
    D5 NUMERIC(13,8) DEFAULT 0.0,
    peso NUMERIC(13, 8) DEFAULT 1.0,
    unidade_peso INTEGER NOT NULL REFERENCES cadastro.unidades_medidas(id));
```
###### Tabela lista de material fracionado
| id  | id_parte | id_formato_material |  id_tipo_material  | D1  |  D2  | D3  | D4  | D5  | quantidade | unidade_compra | peso | unidade_peso |
|:---:|:--------:|:-------------------:|:------------------:|:---:|:----:|:---:|:---:|:---:|:----------:|:--------------:|:----:|:------------:|
|  1  |    1     |          1          |         1          | 12  | 6000 |     |     |     |     1      |       MM       |      |      KG      |
```
CREATE TABLE producao.lista_materiais_fracionados (id BIGINT PRIMARY KEY,
    id_parte_projeto BIGINT REFERENCES producao.partes_projetos(id),
    id_formato_material BIGINT REFERENCES cadastro.formatos_materiais(id) NOT NULL,
    id_tipo_material BIGINT REFERENCES cadastro.tipos_materiais(id) NOT NULL,
    D1 NUMERIC(13,8) DEFAULT 0.0,
    D2 NUMERIC(13,8) DEFAULT 0.0,
    D3 NUMERIC(13,8) DEFAULT 0.0,
    D4 NUMERIC(13,8) DEFAULT 0.0,
    D5 NUMERIC(13,8) DEFAULT 0.0,
    quantidade INT NOT NULL DEFAULT 1,
    unidade_compra TEXT NOT NULL,
    peso NUMERIC(13,8) DEFAULT 1.0,
    unidade_peso TEXT NOT NULL); 
        
ALTER TABLE producao.index ADD COLUMN id_materiais_fracionados_partes BIGINT DEFAULT 1;
```
###### Tabela lista de material
| id  | id_parte | id_material | quantidade | unidade_compra |
|:---:|:--------:|:-----------:|:----------:|:--------------:|
|  1  |    1     |      1      |     3      |       UN       |
```
CREATE TABLE producao.lista_materiais (id BIGINT PRIMARY KEY,
        id_parte_projeto BIGINT REFERENCES producao.partes_projetos(id),
        id_material BIGINT REFERENCES cadastro.materiais(id) NOT NULL,
        quantidade INT DEFAULT 1,
        unidade_compra TEXT NOT NULL);
        
ALTER TABLE producao.index ADD COLUMN id_materiais_partes BIGINT DEFAULT 1;
```