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
* A proposta também contém itens que enumeram o que está sendo proposto com detalhes dos cálculos e valores.
* Pode haver um pré projeto da idéia para o produto e forma de construção do equipamento.
* Quando uma peça do projeto fica pronta, seu desenho é impresso. No serviço de manufatura, a matéria prima desta peça é comprada e suas medidas são obtidas pelo desenho.
* Materiais, componentes, partes, etc... Composição do material: 1020, 1045, VND, VC 131, etc.  
* Formato: chapa, barra chata, barra redonda, anel, metalon, cantoneira, tubo mecânico, etc.  
	Grandezas:
	1. A x L x C -- Altura Largura Comprimento.
	2. D x C -- Diâmetro Comprimento.
	3. De x Di x C -- Diâmetro interno Diâmetro externo Comprimento.

### Termos e significados.
- Matéria-prima: são elementos, materiais naturais e semi-processados utilizados na contrução de um bem e serviço e é uma categoria de insumo.
- Insumo: é um termo amplo que engloba todos os recursos utilizados no meio de produção.  Ele pode ser dividido em insumo direto como matéria-prima, um equipamento eletrônico como CLP e outros que são utilizados diretamente no processo de produção de outros bens e serviços. Já o insumo indireto é considerado todo recurso utilizado indiretamenta na produção de bens e serviços como: energia elétrica, trabalhadores, equipamentos de usinagem, etc.

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

```Comando
CREATE TABLE producao.tipos_propostas (
	id SERIAL PRIMARY KEY, 
	descricao TEXT NOT NULL
);
```
Está tabela contém os registros tipos orçamentos que podem ser
gerados: Prestação de serviço, Fabricação, Industrialização e Consultoria.
### Um orçamento
Os campos fabricante e cliente são únicos ao orçamento, assim também:
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

