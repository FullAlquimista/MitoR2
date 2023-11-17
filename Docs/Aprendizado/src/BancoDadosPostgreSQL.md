# Banco de dados PostgreSQL

### Comando CREATE:
Este comando é utilizado para definir objetos dentro
do nosso sistema de banco de dados.
- Todos os identificadores devem começar com uma letra (alpha-char)
- Os nomes dos identificadores não podem ultrapassar o limete de 63 caracteres.

Existe uma hierarquia de trabalho definido:
  1. Banco de dados (DBs).
     1. Esquemas (Schema) é opcional no sentido de não precisar defini-lo antes de criar um objeto como uma tabela dentro do banco de dados.
        1. Objetos (Objects like Tables, Functions, Triggers, etc).
  
Nota: Todos os usuários | roles tem acesso CREATE e USAGE no esquema public.
