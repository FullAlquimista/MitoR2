# Compras.
Setor responsável por comprar os insumos necessários para o funcionamento da
empresa.
No setor de projetos uma lista de material é feita e utilizada para gerar uma 
lista de cotação.
Os materiais podem ser cotados em vários fornecedores e fechado com apenas
um deles, gerando uma ordem de compra. Está ferramenta pode ser utilizada 
para comparar facilmente os preços entre os fornecedores cotados.

## Solicitação avulsa.
É possível solicitar um material de forma avulsa sem estar lincado a um projeto
Para isso a solicitação deve gerar um material na lista de materiais pertecentes
ao projeto mas sem vinculo a uma parte do projeto. E uma tabela de solicitação
deve conter o registro deste material.

PARA FAZER: Criar está tabela.

## Orçamento do material.

###### Tabela: Lista de compra de materiais.
Está tabela cria um vinculo ao material da lista de materiais. A partir deste ponto
o material cotado não pode mais ser apagado.

| id  | id_lista_materiais | data |
|:----|:------------------:|:----:|
| 1   |         1          |      |
| 2   |                    |      |
```
CREATE TABLE producao.lista_compra_materiais (id BIGSERIAL PRIMARY KEY,   
                                id_lista_material BIGINT REFERENCES producao.lista_materiais(id), 
                                data DATE NOT NULL);
```



######