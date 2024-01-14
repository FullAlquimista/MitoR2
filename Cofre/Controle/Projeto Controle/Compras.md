# Compra.
Setor responsável por comprar os insumos necessários para o funcionamento da empresa. No setor de projetos uma lista de material é feita e utilizada para gerar uma lista de cotação. Os materiais podem ser cotados em vários fornecedores e fechado com apenas um deles, gerando uma ordem de compra. Está ferramenta pode ser utilizada para comparar facilmente os preços entre os fornecedores cotados.
## Solicitação avulsa.
É possível solicitar um material de forma avulsa sem estar lincado a um projeto. Para isso a solicitação deve gerar um material na lista de materiais mas sem vinculo a uma parte do projeto. Deve incluir um vinculo a está solicitação.
###### Tabela: compras.solicitacoes_materiais
| id | data | oid_usuario |
| :--- | :--: | ---- |
| 1 |  |  |
```
CREATE TABLE compras.solicitacoes_materiais (id BIGSERIAL PRIMARY KEY,   
                                oid_usuario BIGINT NOT NULL, 
                                data DATE NOT NULL DEFAULT CURRENT_TIMESTAMP);
```

## Orçamento do material.
#### Cotação de materiais.
Para cotar um material, é necessário enviar á um fornecedor uma lista com os materiais desejados para efetuar a cotação. A tabela de orçamento agrupa todas as cotações criadas em um dado momento de alguns itens da lista de materiais da produção. Já a tabela da lista de materiais cotados enviados a cada fornecedor segundo o momento da criação.
A ordem de compra é emitida e concretiza uma quantidade determinada de materiais cotados para um fornecedor. Nela uma lista de materiais comprados contém a ordem emitida e o material cotado como referência.

##### Tabela: compras.cotacoes_materiais
| id | [[Cadastro#Tabela *cadastro.pessoas*\|id_pessoa_fornecedor]] | data | oid_usuario |
| :--- | :--: | :--: | ---- |
| 1 | 3 | 01/01/2024 |  |
|  |  |  |  |
```
CREATE TABLE compras.cotacoes_materiais (
id BIGSERIAL PRIMARY KEY,
id_pessoa_fornecedor BIGINT NOT NULL REFERENCES cadastro.pessoas(id),
data DATE NOT NULL DEFAULT CURRENT_TIMESTAMP,
oid_usuario BIGINT);
```
##### Tabela: compras.lista_materiais_cotados
| id | [[Compras#Tabela compras.cotacoes_materiais\|id_cotacao_material]] | [[Projetos#Tabela producao.lista_materiais\|id_lista_materiais]] | codigo | descricao | [[Cadastro#Tabela cadastro.unidades_medidas\|id_unidade_quantidade]] | quantidade | valor_unitario | valor_total | valor_icms | valor_ipi | aliquota_icms | aliquota_ipi | data | oid_usuario |
| :--- | :--- | :--- | :--- | :--- | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| 1 | 1 | 4 | 7202-01-02 | SAE-1020 BLOCO 12,7x84x84mm | UN | 6 |  |  |  |  |  |  | 01/01/2024 |  |
| 2 | 1 | 5 | 7202-01-03 | SAE-1020 CHAPA 2,5x1074x1280mm | UN | 2 |  |  |  |  |  |  | 03/01/2024 |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
```
CREATE TABLE compras.lista_materiais_cotados (
id BIGSERIAL PRIMARY KEY,
id_cotacao_material BIGINT NOT NULL REFERENCES compras.cotacoes_materiais(id),
id_lista_material BIGINT NOT NULL REFERENCES producao.lista_materiais(id),
codigo TEXT,
descricao TEXT NOT NULL,
id_unidade_quantidade INT NOT NULL REFERENCES compras.unidades_medidas(id),
quantidade NUMERIC(13,8) DEFAULT 1.0,
valor_unitario NUMERIC(13,8) DEFAULT 1.0,
valor_total NUMERIC(13,8) DEFAULT 1.0,
valor_icms NUMERIC(13,8) DEFAULT 0.0,
valor_ipi NUMERIC(13,8) DEFAULT 0.0,
aliquota_icms NUMERIC(13,8) DEFAULT 0.0,
aliquota_ipi NUMERIC(13,8) DEFAULT 0.0,
data DATE NOT NULL DEFAULT CURRENT_TIMESTAMP,
oid_usuario BIGINT);
```
##### Tabela: compras.ordens_compras
| id | data | oid_usuario |
| :--- | :--: | ---- |
| 1 | 01/01/2024 |  |

```
CREATE TABLE compras.ordens_compras (id BIGSERIAL PRIMARY KEY,
data DATE NOT NULL DEFAULT CURRENT_TIMESTAMP,
oid_usuario BIGINT);
```
##### Tabela: compras.lista_materiais_comprados
| id | [[Compras#Tabela compras.ordens_compras\|id_ordem_compra]] | [[Compras#Tabela compras.lista_materiais_cotados\|id_lista_material_cotado]] | data_compra | data | oid_usuario |
| :--- | :--: | :--: | :--: | :--: | ---- |
| 1 | 1 | 1 | 01/01/2024 | 01/01/2024 |  |
| 2 | 1 | 2 | 04/01/2024 | 04/01/2024 |  |
|  |  |  |  |  |  |
```
CREATE TABLE compras.lista_materiais_comprados (id BIGSERIAL PRIMARY KEY,
id_ordem_compra BIGINT NOT NULL REFERENCES compra.ordens_compras(id),
id_lista_material_cotado BIGINT NOT NULL UNIQUE REFERENCES compra.lista_materiais_cotados(id),
data_compra DATE NOT NULL DEFAULT CURRENT_TIMESTAMP,
data DATE NOT NULL DEFAULT CURRENT_TIMESTAMP,
oid_usuario BIGINT);
```

## Estoque do material

#### Entrada de estoque
Após a emissão da ordem de compra para um fornecedor, o material será faturado e entregue a fábrica. Este material deve ser controlado por algum meio. Normalmente os materiais são comprados especificamente para um equipamento, e por isso após sua chegada, eles são separados para a parte ou equipamento que o requisitou.
