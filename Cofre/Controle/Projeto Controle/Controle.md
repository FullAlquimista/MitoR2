# Controle

Este aplicativo gerencia os setores de uma empresa.
A empresa utilizada como estudo é a A.M.E.

As bibliotecas utilizadas são: Framework CopperSpice, nlohmann json, spdlog
e PostgreSQL.

O aplicativo principal está contido no sub-projeto CMAKE chamado Desktop.
Neste está toda a inicialização das bibliotecas e também contém todos
os dispositivos principais utilizados na interface gráfica.

Cada setor será dividivo em módulos. Um módulo é um conjunto de arquivos
carregados pelo aplicativo para adicionar novas funcionalidades.  
As funcionalidades estão englobadas em serviços.
Os serviços também podem ser obtidos através do aplicativo principal
utilizando a instância do aplicativo QApplication::instance() em qualquer
parte do sistema, pois é compartilhada em todo o processo através da
própria framework CopperSpice.
Estes serviços se tornam disponíveis através de cabeçalhos que declaram
classes virtuais com as funcionalidades implementadas pelo serviço.
Sendo obtidas por funções da instância do aplicativo.

Um módulo é carregado pelo aplicativo Desktop através da biblioteca Módulos.

## Módulos
Lista de módulos principais do sistema:
- [Cadastro](<Cadastro.md>) é o módulo que integra ao sistema as 
funcionalidades de cadastro.
- [Produção](<Producao.md>) é o módulo que integra todos os serviços
para gerenciar a produção da empresa. Desde o orçamento, até 
a montagem da máquina.
