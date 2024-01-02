# Compras.
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

##### Cotação de materiais.
Para cotar um material, é necessário enviar á um fornecedor uma lista com os materiais desejados para efetuar a cotação. A tabela de orçamento agrupa todas as cotações criadas em um dado momento de alguns itens da lista de materiais da produção. Já a tabela da cotação lista itens de materiais enviados a cada fornecedor linkados a um determinado orçamento segundo o momento da criação.
###### Tabela: compras.orcamentos_materiais
| id | data | oid_usuario |
| :--- | :--: | ---- |
| 1 | 01/01/2024 |  |

```
CREATE TABLE compras.orcamentos_materiais (id BIGSERIAL PRIMARY KEY,
                                data DATE NOT NULL DEFAULT CURRENT_TIMESTAMP,
                                oid_usuario BIGINT);
```
###### Tabela: compras.cotacoes_materiais
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
###### Tabela: compras.lista_materiais_cotados
| id | [[Compras#Tabela compras.cotacoes_materiais\|id_cotacao_material]] | [[Projetos#Tabela producao.lista_materiais\|id_lista_materiais]] | codigo | descricao | unidade | quantidade | valor_unitario | valor_total | valor_icms | valor_ipi | aliquota_icms | aliquota_ipi |
| :--- | :--- | :--- | :--- | :--- | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| 1 | 1 | 4 | 7202-01-02 | SAE-1020 BLOCO 12,7x84x84mm | UN | 6 |  |  |  |  |  |  |
```
CREATE TABLE compras.lista_materiais_cotados (
id BIGSERIAL PRIMARY KEY,
id_pessoa_fornecedor BIGINT NOT NULL REFERENCES cadastro.pessoas(id),
data DATE NOT NULL DEFAULT CURRENT_TIMESTAMP,
oid_usuario BIGINT);
```
