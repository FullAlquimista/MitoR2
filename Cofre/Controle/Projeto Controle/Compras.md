# Compras.
Setor responsável por comprar os insumos necessários para o funcionamento da empresa. No setor de projetos uma lista de material é feita e utilizada para gerar uma lista de cotação. Os materiais podem ser cotados em vários fornecedores e fechado com apenas um deles, gerando uma ordem de compra. Está ferramenta pode ser utilizada para comparar facilmente os preços entre os fornecedores cotados.
## Solicitação avulsa.
É possível solicitar um material de forma avulsa sem estar lincado a um projeto. Para isso a solicitação deve gerar um material na lista de materiais mas sem vinculo a uma parte do projeto. Deve incluir um vinculo a está solicitação.
###### Tabela: Lista de solicitação avulsa.
| id  | oid_usuario | data |
|:----|:-----------:|:----:|
| 1   |      1      |      |
```
CREATE TABLE compras.solicitacoes_materiais (id BIGSERIAL PRIMARY KEY,   
                                oid_usuario BIGINT NOT NULL, 
                                data DATE NOT NULL DEFAULT CURRENT_TIMESTAMP);
```

## Orçamento do material.

###### Tabela: Cotação de materiais.
Para cotar um material, é necessário enviar á um fornecedor uma lista com os materiais desejados para efetuar a cotação.

| id  | id_lista_materiais | data |
|:----|:------------------:|:----:|
| 1   |         1          |      |
| 2   |                    |      |
```
CREATE TABLE producao.lista_compra_materiais (id BIGSERIAL PRIMARY KEY,   
                                id_lista_material BIGINT REFERENCES producao.lista_materiais(id) NOT NULL, 
                                data DATE NOT NULL DEFAULT CURRENT_TIMESTAMP);
```

```
```
######